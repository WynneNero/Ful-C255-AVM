/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD NJ   									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date         Name               Changes and comments
* ----------------------------------------------------------------------
* 0.1    July 25 ,2016      ShangQiuju       Init version:Spi not use fifo mode ,but tranmist/receive data format is
                                                                             8 byte fifo frame
* ----------------------------------------------------------------------
* 0.2    Aug 29,2016       ShangQiuju       Use Dual buffer mode for spi communication;Use Software fifo mode.
* ----------------------------------------------------------------------
* 0.3    Dec 26,2016       ShangQiuju       Remove gpio config to gpio_cfg.h,add include file "gpio_cfg.h"
* ----------------------------------------------------------------------
* 0.4    Jan 1,2017         ShangQiuju        Remove unused parameter.
*=====================================================================*/
#include "csi_if.h"
#include "socdriver.h"
#include "socdriver_if.h"

#include "bl_typedefs.h"
//#include "bl_adapter.h"
#include "bl_rte.h"
#include "gpio_cfg.h"

U8 in_buffer[FIFO_DEPTH], out_buffer[FIFO_DEPTH]; //buffer for 8byte data exchange with SPI
BOOL spi_tx_trigger_firstPacket;	//flag new cmd to be sent from fifotx_task, 1st packet to be sent at fiforx_proc
BOOL spi_tx_ack, spi_tx_cmd; //trigger ack cmd or 1st pack of normal cmd to send
U8 out_packet[FIFO_DEPTH];
BOOL power_on_wait, tx_late_ack;
BOOL spi_navi2up_resync_on;
BOOL spi_resync_required;
BOOL rx_buffer_space_status;
U16 spi_cs_starting_time;

//HQ(with Ack), LQ(no ack)
U8 tx_hqbuffer[SPI_NAVI_OUT_HQBUF_SIZE];
U8 tx_lqbuffer[SPI_NAVI_OUT_LQBUF_SIZE];
U8 rx_hqbuffer[SPI_NAVI_INP_HQBUF_SIZE];
U8 rx_lqbuffer[SPI_NAVI_INP_LQBUF_SIZE];

SPI_NAVI_RX_STATUS rx_status; //command receiving status, rx_q[TOTAL_RXQ] is in
SPI_NAVI_TX_STATUS tx_status; //command tranmitting statsu, tx_q[TOTAL_TXQ] is in
U8 tx_frame[SPI_FRAME_MAXLENGTH]; //tx command parsing buffer
U16 rx_cmd_processed[TOTAL_RXQ];
U16 tx_cmd_processed[TOTAL_TXQ];
U8 rx_byte_in_last_packet;
U8 rx_cmdid_processed[TOTAL_RXQ];
U8 tx_frameid[TOTAL_TXQ];
U8 spi_tx_continuous_cmd_count;

U8 spi_ove_counter; //request master to use slower clock (mainly for dev debugging purpose)
U8 cserror_counter; //request master to use slower clock (mainly for dev debugging purpose)
U8 reset_counter; //SPI reset for ove, timeout errors
U8 spi_tx_sending_timeout_counter; //counting SPI sending timeout, reset system if hit limit
U8 spi_tx_ack_timeout_counter; //counting ack timeout when sending hq cmd, reset system if hit limit
U8 rx_error_log;	//record of SPI Rx errors, to be stored in E2PROM or print out to trace!
U8 tx_error_log; 	//record of SPI Tx errors, to be stored in E2PROM or print out to trace!


SPI_NAVI_FIFO_TYPE spi_navi_in_fifo,spi_navi_out_fifo;
SPI_NAVI_FRAME_TYPE spi_navi_in_frame,spi_navi_out_frame;

SPI_NAVI_RX_INFO_TYPE spi_navi_rx_info;
SPI_NAVI_TX_INFO_TYPE spi_navi_tx_info;

SPI_NAVI_TIMER_TYPE spi_navi_req_send_timer,spi_navi_tx_timer,spi_navi_ack_timer,spi_navi_rx_timer;


U8 csStatus;
U8 csStatusPre;
U8 dataRetySendCnt;
U16 uReceiveTimeCnt = 0;
U16 uSendTimeCnt = 0;
RECV_BUF_STRUCT RecMsgBuf[RECV_BUF_SIZE];


E_SOCDRIVER_STATE eSocDriverState;
E_DRIVER_CONTROL_STATE eSocDriverControlState;
E_DEV_POWERS eSocPowerState;
BOOL bResyncDataSent;

BOOL bDataSent;

void spi_navi_fiforx_task(void);
void spi_navi_fifotx_task(void);
void spi_navi_tx_on(void);
void spi_navi_tx_off(void);
void spi_navi_trigger_sending(void);
void spi_navi_fifo_reset(void);
void spi_navi_reset_cmdfifotail(SPI_NAVI_CMD_FIFO *cmd_fifo);
void spi_navi_reset_cmdfifohead(SPI_NAVI_CMD_FIFO *cmd_fifo);
void spi_navi_update_cmdfifosize(SPI_NAVI_CMD_FIFO *cmd_fifo);
//#define TEST_INT
#define TEST_CYCLIC
#ifdef TEST_CYCLIC
BOOL bOpen;
#endif
/***********************************************************************
*  Name        : SocDriver_Open
*  Description : Open driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
	U8 SocDriver_Open(void)
	{
		init_var();
    #ifdef TEST_INT
		GPIO_SetOutMode (GPIO_PORT_0,GPIO_PIN_4, E_PUSH_PULL, E_HIGH_40MHZ);//CRQ OUTPUT
		GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,FALSE);
    #endif
    #ifdef TEST_CYCLIC
		GPIO_SetOutMode (GPIO_PORT_0,GPIO_PIN_4, E_PUSH_PULL, E_HIGH_40MHZ);//CRQ OUTPUT
		GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,FALSE);
		bOpen = FALSE;
    #endif
		GPIO_SetOutMode (GPIO_PORT_0,GPIO_PIN_4, E_PUSH_PULL, E_HIGH_40MHZ);//CRQ OUTPUT
		GPIO_SetInMode(GPIO_PORT_0,GPIO_PIN_0, E_NO_MODE, TRUE) ;//CS INPUT
	
		CSI_InitFIFO(SOC_SPI,SPI_BAUD1M,FALSE,NO_CSS,FALSE);	
		__EI();  
		GPIO_Out_Write(GPIO_PORT_0,GPIO_PIN_4,TRUE);
		CSI_StartFifo(SOC_SPI, 8,FALSE);
		eSocDriverControlState = E_REQ_START_WORK;
		return ERR_OK;	
	}


/***********************************************************************
*  Name        : SocDriver_Close
*  Description : Close driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
U8 SocDriver_Close(void)
{
    CSI_Stop(SOC_SPI);///TODO:stop fifo
    eSocDriverControlState = E_REQ_STOP_WORK;
  return ERR_OK;	
}

/***********************************************************************
*  Name        : SocDriver_Init
*  Description : Init driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocDriver_Init(void)
{
        U8 i;
        for(i=0;i<RECV_BUF_SIZE;i++)
        {
            RecMsgBuf[i].len = 0;
        }
        eSocPowerState = E_DEV_SPOWEROFF;
        eSocDriverState = E_DRIVER_IDLE;
        csStatus = 0;
        csStatusPre = 0;
}

/***********************************************************************
*  Name        : SocDriver_DeInit
*  Description : DeInit driver        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocDriver_DeInit(void)
{
}

/***********************************************************************
*  Name        : SocDriver_powercontrol
*  Description : control power        
*  Parameter   : None
*  Returns     : type
***********************************************************************/
void SocDriver_powercontrol(E_DEV_POWER type)
{
    switch(type)
    {
        case E_DEV_POWERON:
            OPEN_SOC_POWER();
            eSocPowerState = E_DEV_SPOWERON;
        break;
        case E_DEV_POWEROFF:
            CLOSE_SOC_POWER();
            eSocPowerState = E_DEV_SPOWEROFF;
        break;
        case E_DEV_WAKEUP:
        break;
        case E_DEV_SLEEP:
        default:
        break;
    }
}

/***********************************************************************
*  Name        : SocDriver_GetpowerStatus
*  Description : get power status        
*  Parameter   : type
*  Returns     : BOOL
***********************************************************************/
BOOL SocDriver_GetpowerStatus(E_DEV_POWERS type)
{
    BOOL bRet = FALSE;
    switch(type)
    {
        case E_DEV_SPOWERON:
        case E_DEV_SPOWEROFF:
        case E_DEV_SWAKEUP:
        case E_DEV_SSLEEP:
            if(eSocPowerState == type )
                bRet = TRUE;
        break;
        default:
        break;
    }
    return bRet;
}

/***********************************************************************
*  Name        : SocDriver_Cyclic_Entry
*  Description : 10 ms entry        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void SocDriver_Cyclic_Entry(void)
{	
   switch(eSocDriverState)
    {
        case E_DRIVER_IDLE:
        if(eSocDriverControlState == E_REQ_START_WORK)
        {
            eSocDriverState = E_DRIVER_TRANSMIT;
        }
        else if(eSocDriverControlState == E_REQ_STOP_WORK)
        {
            eSocDriverState = E_DRIVER_STOP;
        }
        break;
        
        case E_DRIVER_TRANSMIT:        
            if(eSocDriverControlState == E_REQ_STOP_WORK)
            {
                eSocDriverState = E_DRIVER_STOP;
                break;
            }
            if(eSocPowerState == E_DEV_SPOWERON)
            {            
                MonitorResynReq();
                spi_navi_fifotx_task();
                spi_navi_fiforx_task();
            }
        break;

        case E_DRIVER_STOP:
            if(eSocDriverControlState == E_REQ_START_WORK)
            {
                eSocDriverState = E_DRIVER_TRANSMIT;
                break;
            }
        break;

        default:break;
    }

}


/***********************************************************************
*  Name        : SocDriver_Write
*  Description : send request        
*  Parameter   : buffer,len
*  Returns     : U8
***********************************************************************/
U8 SocDriver_Write( U8* buffer, U16 Len)
{
    ERR_TYPE eReturnVal;
        
    if((eSocDriverState != E_DRIVER_TRANSMIT)||(eSocPowerState != E_DEV_SPOWERON))
    {
        eReturnVal = ERR_DISABLED;
    }
    else if (Len>SPI_FRAME_MAXLENGTH)
    {
        eReturnVal = ERR_RANGE;
    }
    else
    {
        //BOOL spi_navi_fifo_send_frame(U8 q_type,U8 cmd_type,U16 service,U8 nArgs,U8 * pArg)
          U8 q_type;
          U8 cmd_type;
          U16 service;
          U8 nArgs;
          U8 * pArg = NULL;
          BOOL ret_val = FALSE;  
            /* length: app command payload size (from cmd type to end of parameters) */
          U8 length;
            U8 frame_id, total_packet_size, cs =0, counter, p_counter;


          q_type = buffer[0];
          cmd_type = buffer[1];
          service = buffer[2]*0x100+buffer[3];
          nArgs = buffer[4];
          pArg = buffer+5;
          length = nArgs + NAVI_BASE_LEN;
            if (q_type >= TOTAL_TXQ) //invalid parameter
                q_type = TX_HQ; //force to use HQ which has ack for every command (backwards competible)
            total_packet_size = length + SPI_FRAME_OVERHEAD;
            total_packet_size += ((total_packet_size/6)+1)*2+8; //estimated required size in tx buffer
            ret_val = fifo_has_enough_space(&tx_status.tx_q[q_type].buffer, (total_packet_size + FIFO_DEPTH*tx_status.total_packet)); //in case sending cmd backstep for resending
            if (ret_val != TRUE)
                eReturnVal = ERR_BUSY;
            else
            {
                frame_id = tx_frameid[q_type]; //load frame id (1-63 running number)
                if (((frame_id++) & RUNNING_NUMBER_MAX) == 0x00) //if running number wrap to 0
                    frame_id = 0x01; //to skip 0x00 (which is for idle byte)
                frame_id |= FRAMEID_MS_BIT; //mark bit6 with slave bit
                if (q_type == TX_HQ)
                    frame_id |= FRAMEID_Q_BIT; //mark bit7 with Q type bit
                tx_frameid[q_type] = frame_id & RUNNING_NUMBER_MAX; //store frame id
                tx_frame[0] = 0xff;
                tx_frame[1] = 0xa5;
                tx_frame[2] = 0x5a;
                tx_frame[SPI_FRAME_IDBYTE]=frame_id;
                tx_frame[SPI_FRAME_LENGTHBYTE] = length;
                tx_frame[SPI_FRAME_CMDTYPEBYTE] = cmd_type;
                tx_frame[SPI_FRAME_CMDIDBYTE_H] = (U8)(service>>8);
                tx_frame[SPI_FRAME_CMDIDBYTE_L] = (U8)service;
                tx_frame[SPI_FRAME_CMDDATASIZEBYTE] = 1+nArgs; /**  the flag byte + param len  **/
                tx_frame[SPI_FRAME_CMDFLAGBYTE] = 0;
                for (counter =0; counter<nArgs; counter++) //load all command bytes starting from cmd type byte
                    tx_frame[SPI_FRAME_CMDPARABYTE+counter] = pArg[counter];
                for (counter=SPI_FRAME_IDBYTE; counter<(length+SPI_FRAME_OVERHEAD-1); counter++)
                    cs ^= tx_frame[counter]; //calculate cs till last byte of parameters
                tx_frame[length+SPI_FRAME_OVERHEAD-1] = cs;
                out_packet[0] = frame_id;
                for (counter=0; counter<(length+SPI_FRAME_OVERHEAD); ) //stop when all bytes in the frame are copied to buffer
                {
                    cs = 0; //starting value for cs calculation
                    for (p_counter = 1; p_counter<(FIFO_DEPTH-1); p_counter++, counter++) //copy bytes from byte2 to byte7
                    {
                        if (counter < (length + SPI_FRAME_OVERHEAD))
                            out_packet[p_counter] = tx_frame[counter];
                        else
                            out_packet[p_counter] = 0x00; //for last packet with less than 8 bytes, fill in 0x00
                        cs ^= out_packet[p_counter];
                    }
                    out_packet[FIFO_DEPTH-1] = cs;
                    ret_val = fifo_input_block(&tx_status.tx_q[q_type].buffer, out_packet, FIFO_DEPTH);
                    if (ret_val == FALSE)
                    {
                        spi_navi_reset_cmdfifotail(&tx_status.tx_q[q_type]);
                        continue;
                    }
                }
                if( FALSE == ret_val)
                {
                    eReturnVal = ERR_FAULT;
                }
                else
                {
                    tx_status.tx_q[q_type].cmd_tail = tx_status.tx_q[q_type].buffer.mFIFOTail;
                    spi_navi_update_cmdfifosize(&tx_status.tx_q[q_type]);
                    eReturnVal = ERR_OK;
                }
            }
    }
    return eReturnVal;
}


/***********************************************************************
*  Name        : SocDriver_Read
*  Description :  read data from driver
*  Parameter   : buffer,len
*  Returns     : U16
***********************************************************************/
U16 SocDriver_Read( U8* buffer, U16 Len)
{
    U16 bRetLen = 0;
    U8 index = 0;

    for(index = 0;index<RECV_BUF_SIZE;index++)
    {
        if(RecMsgBuf[index].len)
        {
            bRetLen = RecMsgBuf[index].len;
            memcpy(buffer,RecMsgBuf[index].buf,RecMsgBuf[index].len);
            RecMsgBuf[index].len = 0;
            return bRetLen;
        }
    }
    return bRetLen;  
}

/***********************************************************************
*  Name        : spi_navi_fifotx_nextcmd
*  Description :  send commad when receive data
*  Parameter   : none
*  Returns     : none
***********************************************************************/
void spi_navi_fifotx_nextcmd(void)
{
    U16 length;
    //int counter = 0;

    if ((FALSE == spi_tx_trigger_firstPacket) && (spi_tx_continuous_cmd_count < MAX_CONTINUOUS_SEND))
    {
        if ((tx_status.q_id == TX_HQ) && (ACKOK == tx_status.tx_state))//work as in ACKON
        {
            tx_status.tx_q[TX_HQ].cmd_head = tx_status.tx_q[TX_HQ].buffer.mFIFOHead; //pointing to next hq command location
            spi_navi_update_cmdfifosize(&tx_status.tx_q[TX_HQ]);
            tx_cmd_processed[TX_HQ]++; //counting #cmd sent
            tx_status.tx_state = TX_IDLE;
            tx_status.retry_counter = 0;
        }

        if (tx_status.tx_q[TX_HQ].cmd_head == tx_status.tx_q[TX_HQ].cmd_tail) //work as in IDLE
        {
            /*888phase2 no error found
            tx_status.tx_q[TX_HQ].buffer.mFIFOLength = 0;	//flush hq buffer in case it is full
            tx_status.tx_q[TX_HQ].buffer.mFIFOHead = tx_status.tx_q[TX_HQ].cmd_head;
            tx_status.tx_q[TX_HQ].buffer.mFIFOTail = tx_status.tx_q[TX_HQ].cmd_head;
            888phase2*/
            if (tx_status.tx_q[TX_LQ].cmd_head == tx_status.tx_q[TX_LQ].cmd_tail) //check tx lq buffer
            {
                /*888phase2 no error found
                tx_status.tx_q[TX_LQ].buffer.mFIFOLength = 0;	//flush lq buffer in case it is full
                tx_status.tx_q[TX_LQ].buffer.mFIFOHead = tx_status.tx_q[TX_LQ].cmd_head;
                tx_status.tx_q[TX_LQ].buffer.mFIFOTail = tx_status.tx_q[TX_LQ].cmd_head;
                888phase2*/
                tx_status.tx_state = TX_IDLE; //2. remain idle
                //reset flag: spi_tx_asap;    //no more command to send
                return;
            }
            else
                tx_status.q_id = TX_LQ; //next sending lq queue
        }
        else
            tx_status.q_id = TX_HQ; //next sending hq queue

        //fetch the 1st packet of next command from tx buffer
        if (fifo_output_block(&tx_status.tx_q[tx_status.q_id].buffer,out_buffer, FIFO_DEPTH))
        {
            /* frame head check */
            if ((0xFF == out_buffer[1]) && (0xA5 == out_buffer[2]) && (0x5A == out_buffer[3]))
            {
                tx_status.frame_id = out_buffer[0];
                length = out_buffer[5]+6;
                tx_status.total_packet = length/(FIFO_DEPTH-2); //total number of packets to be sent
                if (length%(FIFO_DEPTH-2))
                    tx_status.total_packet++;
                tx_status.packet_transmitted = 0;
                tx_status.retry_counter++;
                uSendTimeCnt = 0;
                spi_tx_trigger_firstPacket = TRUE;
                spi_tx_cmd = TRUE;
                spi_tx_continuous_cmd_count++;
                SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master if case it if off
            }
        }

    }
}

/***********************************************************************
*  Name        : GetRecBufEmptyIndex
*  Description :  
*  Parameter   : none
*  Returns     : U8
***********************************************************************/
U8 GetRecBufEmptyIndex(void)
{
    U8 index = 0;
    for(index = 0;index<RECV_BUF_SIZE;index++)
    {
        if(RecMsgBuf[index].len==0)
        {
            return index;
        }
    }
    return index;
}

/***********************************************************************
*  Name        : spi_navi_fiforx_task
*  Description :  
*  Parameter   : none
*  Returns     : none
***********************************************************************/
void spi_navi_fiforx_task(void)
{
    U8 cmd_size, q_id = 0xff, counter, cmd_cs = 0, length=0;
    BOOL ret_val = TRUE;
    U8 index = 0;

    index = GetRecBufEmptyIndex();
    if(index>=RECV_BUF_SIZE) return;

    if (rx_status.rx_q[RX_HQ].cmd_head != rx_status.rx_q[RX_HQ].cmd_tail)
        q_id = RX_HQ; //HQ has command received
    else if (rx_status.rx_q[RX_LQ].cmd_head != rx_status.rx_q[RX_LQ].cmd_tail)
        q_id = RX_LQ; //LQ has command received
    if (q_id != 0xff) //have command to handle
    {
        ret_val = fifo_output_block(&rx_status.rx_q[q_id].buffer, RecMsgBuf[index].buf, SPI_FRAME_LENGTHBYTE+1); //read out till length byte(5th byte)
        if (ret_val == FALSE)
        {
            trap_log_spi_error(SPI_RX_BUFFERALIGN_ERROR, 0xFF, "buffer misaligned!"); //if caught, must resolve in dev phase!!!
            //888 production, to flush the receiving buffer
            if (rx_status.rx_state == RX_IDLE)
            {
                rx_status.rx_q[q_id].cmd_head = 0;
                rx_status.rx_q[q_id].cmd_tail = 0;
                rx_status.rx_q[q_id].buffer.mFIFOHead = 0;
                rx_status.rx_q[q_id].buffer.mFIFOTail = 0;
                rx_status.rx_q[q_id].buffer.mFIFOLength = 0;
            }
            //888 production
            ///TODO:  FAIL HANDLER
            return;
        }
        cmd_size = RecMsgBuf[index].buf[SPI_FRAME_LENGTHBYTE];
        length = cmd_size + 1; //rest of bytes in the command frame
        ret_val = fifo_output_block(&rx_status.rx_q[q_id].buffer, &RecMsgBuf[index].buf[SPI_FRAME_LENGTHBYTE+1], length); //read rest of command + cs byte
        if (ret_val == FALSE)
        {
            trap_log_spi_error(SPI_RX_BUFFERALIGN_ERROR, 0xFF, "buffer misaligned!"); //if caught, must resolve in dev phase!!!
            //888 production, to flush the receiving buffer
            if (rx_status.rx_state == RX_IDLE)
            {
                rx_status.rx_q[q_id].cmd_head = 0;
                rx_status.rx_q[q_id].cmd_tail = 0;
                rx_status.rx_q[q_id].buffer.mFIFOHead = 0;
                rx_status.rx_q[q_id].buffer.mFIFOTail = 0;
                rx_status.rx_q[q_id].buffer.mFIFOLength = 0;
            }
            //888 production
            ///TODO:  FAIL HANDLER
            return;
        }
        rx_status.rx_q[q_id].cmd_head = rx_status.rx_q[q_id].buffer.mFIFOHead; //update command pointer to next command in buffer
        for (counter = 0; counter < (cmd_size+2); counter++)
            cmd_cs ^= RecMsgBuf[index].buf[SPI_FRAME_IDBYTE + counter]; //cs for id byte,length byte and command bytes
        if (cmd_cs == RecMsgBuf[index].buf[cmd_size + SPI_FRAME_OVERHEAD -1]) //if cmd cs correct
        {
            rx_cmd_processed[q_id]++;
            if (RecMsgBuf[index].buf[SPI_FRAME_IDBYTE] != rx_cmdid_processed[q_id]) //not a repeated command, repeated cmd not to process
            {
                rx_cmdid_processed[q_id] = RecMsgBuf[index].buf[SPI_FRAME_IDBYTE]; //record command processed
                //to pass the cmd to existing command processing
                //spi_navi_handle_frame(&rx_frame[SPI_FRAME_CMDTYPEBYTE]); //starting of command
                //index = GetRecBufEmptyIndex();
                RecMsgBuf[index].len = RecMsgBuf[index].buf[SPI_FRAME_LENGTHBYTE];
                memcpy(RecMsgBuf[index].buf, (RecMsgBuf[index].buf+SPI_FRAME_CMDTYPEBYTE),RecMsgBuf[index].len);
            }
        }
        else
        {
            trap_log_spi_error(SPI_RX_COMMANDCS_ERROR, 0xFF, "found cmd cs error"); //log an error and ignore cmd with cs error //888 production
            //application level should have explicit ack for critical commands
        }
        rx_status.rx_q[q_id].cmd_head = rx_status.rx_q[q_id].buffer.mFIFOHead; //move to next command in the buffer
        spi_navi_update_cmdfifosize(&rx_status.rx_q[q_id]);
    }
    //888 production
    if (rx_status.rx_state == RECEIVING)
    {
        if(uReceiveTimeCnt++>SPI_RX_TIMEOUT)//check for cmd receiving timeout
        {
            if (0 == rx_status.repeat_counter) /* allowe navi resend data is not integrated */
            {
                trap_log_spi_error(SPI_RX_TIMEOUT_ERROR, 0xFF, "spi receiving timeout, master not sending"); //888 production
                trap_restart_system(); //system restart
                ///TODO:
            }
        }
    }
    else
    {
        uReceiveTimeCnt = 0;
    }
    //888 production
    //888 production spi_navi_healthcheck(); //system reset if error or reset too many times!!!
}

/***********************************************************************
*  Name         : spi_navi_is_tx_idle
*  Description : is tx idle ?
*  Parameter  : None
*  Returns      : None
***********************************************************************/
BOOL socDriver_is_tx_idle(void)
{
	return (TX_IDLE == spi_navi_tx_info.status);
}


/***********************************************************************
*  Name         : spi_navi_fifotx_task
*  Description : 
*  Parameter  : None
*  Returns      : None
***********************************************************************/
void spi_navi_fifotx_task(void) //transmission task
{
    U8 counter;
    U16 length;

    if (spi_resync_required == TRUE)	//trigger resync if requested (cs pin pulled low by Navi)
        tx_status.tx_state = TX_RESYNC;

    switch (tx_status.tx_state)
    {
        case ACKOK: //tx channel ready to send
            tx_status.tx_q[TX_HQ].cmd_head = tx_status.tx_q[TX_HQ].buffer.mFIFOHead; //pointing to next hq command location
            spi_navi_update_cmdfifosize(&tx_status.tx_q[TX_HQ]);
            tx_cmd_processed[TX_HQ]++; //counting #cmd sent
            tx_status.tx_state = TX_IDLE;
            tx_status.retry_counter = 0;
            //no break, continue to TX_IDLE state handling
        case TX_IDLE:
            if (spi_tx_trigger_firstPacket != TRUE)
            {
                if (tx_status.hq_ack_request == TRUE) //1. need to send ack command
                {
                    for (counter =0; counter < FIFO_DEPTH; counter++)
                        out_buffer[counter] = 0;
                    out_buffer[ACK_FRAMEID_BYTE] = rx_status.frame_id; //frame id by sender (navi), even in re-sending, the id remains
                    out_buffer[ACK_STATUS_BYTE] = COMMAND_OK;
                    for (counter =1; counter < (FIFO_DEPTH-1); counter++) //calculate cs
                        out_buffer[ACK_CS_BYTE] ^= out_buffer[counter];
                    //only prepare the ack packet here, TDR pushing to be done in fiforx_proc
        #if 1
                    spi_tx_trigger_firstPacket = TRUE;
                    spi_tx_ack = TRUE;
                    SET_REQ_PIN_FOR_DATA_SENDING();
       #else             
                    spi_navi_tx_on();
                    CSI_FIFO_Send(SOC_SPI, out_buffer, FIFO_DEPTH);
                    tx_status.hq_ack_request = FALSE;
                    spi_tx_ack = FALSE;
                    SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master, TIE not on yet, it is done in fiforx_proc
                    spi_tx_trigger_firstPacket = FALSE;
       #endif
                    break;
                }
                if (tx_status.tx_q[TX_HQ].cmd_head == tx_status.tx_q[TX_HQ].cmd_tail) //check tx hq buffer
                {
                    /*888phase2 no error found
                    tx_status.tx_q[TX_HQ].buffer.mFIFOLength = 0;	//flush hq buffer in case it is full
                    tx_status.tx_q[TX_HQ].buffer.mFIFOHead = tx_status.tx_q[TX_HQ].cmd_head;
                    tx_status.tx_q[TX_HQ].buffer.mFIFOTail = tx_status.tx_q[TX_HQ].cmd_head;
                    888phase2*/
                    if (tx_status.tx_q[TX_LQ].cmd_head == tx_status.tx_q[TX_LQ].cmd_tail) //check tx lq buffer
                    {
                        /*888phase2 no error found
                        tx_status.tx_q[TX_LQ].buffer.mFIFOLength = 0;	//flush lq buffer in case it is full
                        tx_status.tx_q[TX_LQ].buffer.mFIFOHead = tx_status.tx_q[TX_LQ].cmd_head;
                        tx_status.tx_q[TX_LQ].buffer.mFIFOTail = tx_status.tx_q[TX_LQ].cmd_head;
                        888phase2*/
                        tx_status.tx_state = TX_IDLE; //2. remain idle
                        break;
                    }
                    else
                        tx_status.q_id = TX_LQ; //next sending lq queue
                }
                else
                    tx_status.q_id = TX_HQ; //next sending hq queue

                //3. have new data command in buffer to send
                if (fifo_output_block(&tx_status.tx_q[tx_status.q_id].buffer,out_buffer, FIFO_DEPTH)) //fetch the 1st packet of next command from tx buffer
                {
                    //when command is pushed to tx buffer, frameID and CS are generated and in 8byte packet format
                    tx_status.frame_id = out_buffer[0];
                    /* frame head check */
                    if ((0xFF == out_buffer[1]) && (0xA5 == out_buffer[2]) && (0x5A == out_buffer[3]))
                    {
                        length = out_buffer[5]+6;
                        tx_status.total_packet = length/(FIFO_DEPTH-2); //total number of packets to be sent
                        if (length%(FIFO_DEPTH-2))
                            tx_status.total_packet++;
                        tx_status.packet_transmitted = 0;
                        tx_status.retry_counter = 0;
                        //update cmd_tail in tx_isr (only after last pack of the command is successfully sent
                        uSendTimeCnt = 1;
                        tx_status.retry_counter++;
                        //only prepare the 1st packet and cmd sending settings here, TDR pushing to be done in fiforx_proc
                        //tx status change to SENDING done in fiforx_proc
#if 1
                        spi_tx_trigger_firstPacket = TRUE;
                        spi_tx_cmd = TRUE;
                        spi_tx_continuous_cmd_count = 0;
                        SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master, TIE not on yet, it is done in fiforx_proc
#else
                        spi_tx_continuous_cmd_count = 0;
                        spi_navi_tx_on();
                        CSI_FIFO_Send(SOC_SPI, out_buffer, FIFO_DEPTH);
                        tx_status.tx_state = SENDING;
                        spi_tx_cmd = FALSE;
                        SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master, TIE not on yet, it is done in fiforx_proc
                        spi_tx_trigger_firstPacket = FALSE;
#endif
                    }
                }
                /*888phase2, no error found */
                else
                {
                    if (tx_status.tx_q[tx_status.q_id].buffer.mFIFOHead != tx_status.tx_q[tx_status.q_id].cmd_head)
                    {
                        tx_status.tx_q[tx_status.q_id].buffer.mFIFOHead = tx_status.tx_q[tx_status.q_id].cmd_head;
                    }
                    /*tx_status.tx_q[tx_status.q_id].buffer.mFIFOLength = fifo_current_length(&tx_status.tx_q[tx_status.q_id].buffer);*/
                }
            }
            break;
        case SENDING: //check spi tx timeout in sending packets of a command
            if(power_on_wait)
                uSendTimeCnt++;
            if (uSendTimeCnt>=SPI_SEND_TIMEOUT) //check for cmd sending timeout
            {
                tx_status.tx_state = TX_TIMEOUT; //sending time out, to reset spi and fifo
                spi_tx_sending_timeout_counter++; //888 production
                CSI_FIFO_SendEmpty(SOC_SPI);
                spi_navi_tx_off(); //disable tx int and clear CRQ to master
            }
            break;
        case WAITING_ACK: //check timeout of an expected ack command
            if (tx_status.hq_ack_request == TRUE) //waiting for ack from master, but also need to send ack command to master
            {
                if (spi_tx_trigger_firstPacket != TRUE)
                {
                    for (counter =0; counter < FIFO_DEPTH; counter++)
                        out_buffer[counter] = 0;
                    out_buffer[ACK_FRAMEID_BYTE] = rx_status.frame_id; //frame id by sender (navi), even in re-sending, the id remains
                    out_buffer[ACK_STATUS_BYTE] = COMMAND_OK;
                    for (counter =1; counter < (FIFO_DEPTH-1); counter++) //calculate cs
                        out_buffer[ACK_CS_BYTE] ^= out_buffer[counter];
                    //only prepare the ack packet here, TDR pushing to be done in fiforx_proc
               #if 1
                    spi_tx_trigger_firstPacket = TRUE;
                    spi_tx_ack = TRUE;
                    SET_REQ_PIN_FOR_DATA_SENDING();
               #else
                    spi_navi_tx_on();
                    CSI_FIFO_Send(SOC_SPI, out_buffer, FIFO_DEPTH);
                    tx_status.hq_ack_request = FALSE;
                    spi_tx_ack = FALSE;
                    SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master, TIE not on yet, it is done in fiforx_proc
                    spi_tx_trigger_firstPacket = FALSE;
                #endif
                    break;
                }
            }
            if (tx_late_ack) //late ack received during retry
            {
                tx_status.tx_state = ACKOK;
                tx_late_ack = FALSE;
                break;
            }
            if (uSendTimeCnt++>=SPI_ACK_TIMEOUT)  //check for timeout
            {
                if (tx_status.retry_counter < MAX_RETRY) //ack timeout, retry from start of the command
                {
                    if (spi_tx_trigger_firstPacket != TRUE)
                    {
                        spi_navi_reset_cmdfifohead(&tx_status.tx_q[tx_status.q_id]); //reset tx buffer head to start of the command, prepare for resend
                        fifo_output_block(&tx_status.tx_q[tx_status.q_id].buffer,out_buffer, FIFO_DEPTH); //fetch the  first packet
                        tx_status.packet_transmitted = 0; //first packet
                        uSendTimeCnt = 1;
                        tx_status.retry_counter++;
                        //only prepare the 1st packet and cmd sending settings here, TDR pushing to be done in fiforx_proc
                        //tx status change to SENDING done in fiforx_proc
              #if 1
                        spi_tx_trigger_firstPacket = TRUE;
                        spi_tx_cmd = TRUE;
                        SET_REQ_PIN_FOR_DATA_SENDING(); 
              #else          
                        spi_navi_tx_on();
                        CSI_FIFO_Send(SOC_SPI, out_buffer, FIFO_DEPTH);
                        tx_status.tx_state = SENDING;
                        spi_tx_cmd = FALSE;
                        SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master, TIE not on yet, it is done in fiforx_proc
                        spi_tx_trigger_firstPacket = FALSE;
               #endif
                    }
                }
                else //exceed max of retry
                {
                    spi_tx_ack_timeout_counter++; //888 production
                    if (spi_tx_ack_timeout_counter < SPI_ACK_TIMEOUT_LIMIT) //let go if ack timeout not to limit yet
                        tx_status.tx_state = ACKOK;
                    else
                    {
                        trap_log_spi_error(0xFF, SPI_TX_ACKTIMEOUT_ERROR, "master failed to ack hq cmd repeatly");
                        trap_restart_system(); //too many ack timeout, restart system
                    }
                }
            }
            break;
        case TX_TIMEOUT:
            if (spi_tx_sending_timeout_counter < SPI_SEND_TIMEOUT_LIMIT) //888 production
            {
                spi_navi_fifo_reset(); //spi reset, tx back to idle mode
                //txtask_fifo_reset++;
            }
            else
            {
                trap_log_spi_error(0xFF, SPI_TX_TIMEOUT_ERROR, "master failed to read cmd repeatly");
                trap_restart_system(); //too many sending timeout, restart system
            }
            break;
        case TX_RESYNC:
            if (spi_resync_required) //need to send SPI_SLAVE_READY packet to navi
            {
                spi_navi_fifo_reset(); //spi reset
                spi_navi_tx_on();
                spi_resync_required = FALSE; //reset only for 1st run, later only wait at this state
                tx_status.tx_state = TX_RESYNC; //and stay in resync state
                #if 0
                for (counter =0; counter < FIFO_DEPTH; counter++)
                    out_buffer[counter] = 0;
                tx_status.frame_id = 0x41; //reset tx frame id
                tx_frameid[TX_LQ] = 0x41;
                out_buffer[ACK_FRAMEID_BYTE] = tx_status.frame_id;
                out_buffer[ACK_STATUS_BYTE] = SPI_SLAVE_READY;
                out_buffer[ACK_DEBUG_INFO_BYTE1] = tx_status.tx_state;
                out_buffer[ACK_DEBUG_INFO_BYTE2] = rx_status.rx_state;
                out_buffer[ACK_DEBUG_INFO_BYTE3] = rx_error_log; //888 production, to send error log to navi(must stored in radio EEPROM)
                out_buffer[ACK_DEBUG_INFO_BYTE4] = tx_error_log;
                for (counter =1; counter < (FIFO_DEPTH-1); counter++) //calculate cs
                    out_buffer[ACK_CS_BYTE] ^= out_buffer[counter];
                CSI_FIFO_Send(SOC_SPI, out_buffer,FIFO_DEPTH);
                #endif
                spi_cs_starting_time =1;
                bResyncDataSent = FALSE;
            }
            if (spi_navi2up_resync_on == FALSE) //navi has released cs pin (after SPI_SlAVE_READY packet is received)
            {
                tx_status.tx_state = TX_IDLE; //go back to idle state for normal tx
                spi_tx_trigger_firstPacket = FALSE;
           //     CSI_FIFO_SendEmpty(SOC_SPI);
           //     spi_navi_tx_off();
            }
            else
            {
                if (spi_cs_starting_time++> SPI_RESYNC_TIMEOUT) //888 production code
                {
                    trap_log_spi_error(0xFF, SPI_TX_RESYNC_ERROR, "master failed to finish resync");

                    ///TODO:
                    trap_restart_system(); //Navi has problem to do resync, restart system
                }
            }
            break;

        default:
            break;
    }
}


/***********************************************************************
*  Name         : spi_navi_tx_on
*  Description : 
*  Parameter  : None
*  Returns      : None
***********************************************************************/
void spi_navi_tx_on(void)
{
    CSI_EnableTxInterrupt(SOC_SPI);
    SET_REQ_PIN_FOR_DATA_SENDING(); //assert CRQ to master
}

/***********************************************************************
*  Name         : spi_navi_tx_off
*  Description : 
*  Parameter  : None
*  Returns      : None
***********************************************************************/
void spi_navi_tx_off(void)
{
    CLEAR_REQ_PIN_FOR_DATA_SENDING(); //clear CRQ
    CSI_DisableTxInterrupt(SOC_SPI);
}


/***********************************************************************
*  Name         : SocDriver_ReceiveIsr
*  Description : 
*  Parameter  : data
*  Returns      : None
***********************************************************************/
//ISR for spi Rx_FIFO
void SocDriver_ReceiveIsr(U8* data)
{
    U8 counter;
    U8 checksum=0;
    U8 bytes_to_receive;
///TODO:SQJ
    #ifdef TEST_INT
        GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,TRUE);
     #endif
    if (0)// (SPI_ORECheck(spi))	//interrupt trigerred by overrun error
    {
     //   SPI_CLRRxError(spi);
        //rx fifo is disabled automatically when OVE happens
        spi_ove_counter++;
        rx_status.rx_state = OVE; //only new data command or ack command can be processed in this state
        //888 production
        trap_log_spi_error(SPI_RX_OVE_ERROR, 0xFF, "overrun error");
        //888 production
        spi_navi_fifo_reset();
        //rxisr_fifo_reset++;
        return;
    }
    else
    {
        memcpy(in_buffer, data, FIFO_DEPTH);
        //if there is timing loading issue with rx_isr, below packet parsing will be moved out to tasks!!!!
        if (in_buffer[0] != 0x00) //master dummy sending (providing clock to receive data from M3)
        {
            for (counter=1; counter<(FIFO_DEPTH-1); counter++)
                checksum ^= in_buffer[counter]; //compute CS
            if (checksum == in_buffer[FIFO_DEPTH-1]) //packet is perfect
            {
                if (in_buffer[ACK_FRAMEID_BYTE]==tx_status.frame_id) //1. ack command
                {
                    if (tx_status.tx_state == WAITING_ACK) //tx sent hq cmd and waiting for ack packet
                    {
                        tx_status.tx_state = ACKOK; //atttention!!! for resending cmd, ack may come at retry sending state!!! this will abort current sending!!!
                        //tail_debug_fix rx_status.rx_state = RX_IDLE; //rx channel waiting for next command
                        //!!! hq, move to next command is done in fifotx_task under ACKOK state!!!

                        //Navi ack'ed last HQ command from Radio
                        //trigger next command send in this rx interrrupt
                        spi_navi_fifotx_nextcmd();

                        spi_navi_trigger_sending();
                    }
                    else if ((tx_status.tx_state == SENDING)&&(tx_status.retry_counter > 1)) //1.1 tx already resending hq cmd
                        tx_late_ack = TRUE;
                        
                    if(!bDataSent)
                    {
                       CSI_FIFO_SendEmpty(SOC_SPI);
                       spi_navi_tx_off(); //clear CRQ to navi (spi master)
                    }
                    else
                    {
                        bDataSent = FALSE;
                    }
                    #ifdef TEST_INT
                    GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,FALSE);
                    #endif
                    return;
                }
                else if ((in_buffer[1]==0xff)&&(in_buffer[2]==0xa5)&&(in_buffer[3]==0x5a)&&(in_buffer[4]==in_buffer[0])) //2. new data command
                {
                    if (rx_status.rx_state == RECEIVING) //still in the midst of receiving previous command
                        spi_navi_reset_cmdfifotail(&rx_status.rx_q[rx_status.q_id]); //drop the imcomplete previous command
                    if (tx_status.hq_ack_request == TRUE)
                        trap_log_spi_error(0xFF, 0xFF, "master resendinging already???"); //for debugging on master's ack timeout before resending
                    //but continue receiving, this may result in repeated command (will be discarded in rx_task)
                    if (rx_status.frame_id == in_buffer[0]) //check for repeated command (for debugging purpose, to remove b4 production release)
                        rx_status.repeat_counter++;
                    else
                        rx_status.repeat_counter = 0;
                    rx_status.frame_id = in_buffer[0]; //new frameid
                    if (in_buffer[0]&FRAMEID_Q_BIT)
                        rx_status.q_id = RX_HQ;
                    else
                        rx_status.q_id = RX_LQ;
                    rx_status.packet_received = 0; //to increase after copy to buffer
                    rx_status.total_packet = (in_buffer[5]+6)/(FIFO_DEPTH-2); //number of packets expected
                    rx_byte_in_last_packet = (in_buffer[5]+6)%(FIFO_DEPTH-2);
                    if (rx_byte_in_last_packet != 0)
                        rx_status.total_packet++; //has remainder last packet
                    else
                        rx_byte_in_last_packet = FIFO_DEPTH - 2; //no remainder, last packet is full
                    if (fifo_has_enough_space(&rx_status.rx_q[rx_status.q_id].buffer, rx_status.total_packet*6))
                    {
                        rx_buffer_space_status = TRUE;	//buffer has space for the whole command
                        rx_status.rx_state = RECEIVING;
                        uReceiveTimeCnt = 0; //get timestamp, for timeout check in rx_process
                    }
                    else
                        rx_buffer_space_status = FALSE;    //888phase2, KIV: to add system restart here!!!
                }
                if (rx_status.rx_state == RECEIVING) //3. or (subsequent) packets of a command
                {
                    if (rx_status.frame_id == in_buffer[0]) //packet really for this frame! and buffer has space
                    {
                        bytes_to_receive = FIFO_DEPTH - 2;
                        if ((rx_status.packet_received+1) == rx_status.total_packet) //receiving last packet of the command
                            bytes_to_receive = rx_byte_in_last_packet;
                        if (fifo_input_block(&rx_status.rx_q[rx_status.q_id].buffer, &in_buffer[1], bytes_to_receive)) //copy payload into rx buffer
                        {
                            rx_status.packet_received++; //successfully received packets
                            if (rx_status.packet_received == rx_status.total_packet) //all packets of the command received
                            {
                                rx_status.rx_q[rx_status.q_id].cmd_tail = rx_status.rx_q[rx_status.q_id].buffer.mFIFOTail; //cmd completed, move cmd pointer
                                spi_navi_update_cmdfifosize(&rx_status.rx_q[rx_status.q_id]);
                                if (rx_status.q_id == RX_HQ)
                                {
                                    tx_status.hq_ack_request = TRUE; //tx should send ack command immediately after current cmd
                                    //trigger ack sending in this round of Rx interrupt if no tx already triggerred yet
                                    if ((spi_tx_trigger_firstPacket != TRUE)&&(tx_status.tx_state != SENDING))
                                    {
                                        for (counter =0; counter < FIFO_DEPTH; counter++)
                                            out_buffer[counter] = 0;
                                        out_buffer[ACK_FRAMEID_BYTE] = rx_status.frame_id; //frame id by sender (navi), even in re-sending, the id remains
                                        out_buffer[ACK_STATUS_BYTE] = COMMAND_OK;
                                        for (counter =1; counter < (FIFO_DEPTH-1); counter++) //calculate cs
                                            out_buffer[ACK_CS_BYTE] ^= out_buffer[counter];
                                        spi_tx_trigger_firstPacket = TRUE;
                                        spi_tx_ack = TRUE;
                                        SET_REQ_PIN_FOR_DATA_SENDING();
                                    }
                                }
                                rx_status.rx_state = RX_IDLE; //a command is completed, rx channel is ready for next command
                            }
                        }
                        else //rx buffer full
                        {
                            //888 production
                            trap_log_spi_error(SPI_RX_BUFFERFULL_ERROR, 0xFF, "receiving buffer is full"); //do handling for buffer full, issue to be fixed in development phase
                            trap_restart_system();
                            //888 production
                        }
                    }
                    else //junk packet, not for this frame (case found in integration phase), if caught reject the whole command
                    {
                        spi_navi_reset_cmdfifotail(&rx_status.rx_q[rx_status.q_id]); //reset rx buffer tail, flush packets received so far for this command (drop the command)
                        rx_status.rx_state = RX_IDLE; //exit RECEIVING mode, to receive new command (new cmd or ack cmd)
                    }
                }
                else
                    trap_log_spi_error(0xFF, 0xFF, "a wild packet received"); //not new cmd, not ack cmd, rx_int not in the middle of receiving a cmd
            }
            else //packet corrupted
            {
                if (tx_status.tx_state != TX_RESYNC) //don't count CS error in resync mode
                {
                    cserror_counter++;
                    rx_status.rx_state = CS_ERROR; //exit RECEIVING mode if in, only new data command or ack command can be processed in this state
                    //888 production
                    trap_log_spi_error(SPI_RX_PACKETCS_ERROR, 0xFF, "corrupted packet");
                    //888 production
                    spi_navi_reset_cmdfifotail(&rx_status.rx_q[rx_status.q_id]); //reset rx buffer tail, flush packets received so far for this command (drop the command)
                }
            }
        }
    }
    spi_navi_trigger_sending();
    if(!bDataSent)
    {
       CSI_FIFO_SendEmpty(SOC_SPI);
       spi_navi_tx_off(); //clear CRQ to navi (spi master)
    }
    else
    {
        bDataSent = FALSE;
    }
    #ifdef TEST_INT
    GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,FALSE);
    #endif
}

/***********************************************************************
*  Name         : spi_navi_trigger_sending
*  Description : 
*  Parameter  : data
*  Returns      : None
***********************************************************************/
void spi_navi_trigger_sending(void)
{
    U8 counter = 0;

    if (TRUE == spi_tx_trigger_firstPacket)
    {
        if ((TX_IDLE == tx_status.tx_state)||(WAITING_ACK == tx_status.tx_state) ||(ACKOK == tx_status.tx_state))//if need to send 1st tx packet or an ack packet
        {
            spi_navi_tx_on();
            if (spi_tx_ack == TRUE)
            {
                CSI_FIFO_Send(SOC_SPI, out_buffer, FIFO_DEPTH);
                bDataSent = TRUE;
                tx_status.hq_ack_request = FALSE;
                spi_tx_ack = FALSE;
            }
            else if (spi_tx_cmd == TRUE)
            {
                CSI_FIFO_Send(SOC_SPI, out_buffer, FIFO_DEPTH);
                bDataSent = TRUE;
                tx_status.tx_state = SENDING;
                spi_tx_cmd = FALSE;
            }
            spi_tx_trigger_firstPacket = FALSE;
          ///TODO:SQJ
        }
    }

}


/***********************************************************************
*  Name         : SocDriver_SentIsr
*  Description : iSR for spi
*  Parameter  : data
*  Returns      : None
***********************************************************************/
void SocDriver_SentIsr(void)
{
    U8 counter;
    bDataSent = FALSE;
    
    #ifdef TEST_INT
    GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,TRUE);
    #endif

    if (tx_status.tx_state == SENDING) //was sending packet of a data command
    {
        power_on_wait = FALSE; //master started spi transaction, no more wait
        tx_status.packet_transmitted++; //previously filled tx fifo is successfully transmitted
        if (tx_status.packet_transmitted == tx_status.total_packet) //last packet of the command was transmitted
        {
            if (tx_status.hq_ack_request == TRUE) //need to ack a received hq command? also checked in fifotx_task
            {
                for (counter =0; counter < FIFO_DEPTH; counter++)
                    out_buffer[counter] = 0;
                out_buffer[ACK_FRAMEID_BYTE] = rx_status.frame_id; //frame id as put by sender (navi)
                out_buffer[ACK_STATUS_BYTE] = COMMAND_OK;
                for (counter =1; counter < (FIFO_DEPTH-1); counter++)
                    out_buffer[ACK_CS_BYTE] ^= out_buffer[counter];
                CSI_FIFO_Send(SOC_SPI, out_buffer,FIFO_DEPTH);
                bDataSent = TRUE;
                //tx_status.tx_state = TX_IDLE; //tx channel ready for next command
                //rx_status.rx_state = RX_IDLE; //rx channel ready for next command
                tx_status.hq_ack_request = FALSE;
                tx_status.total_packet++; //trick! just to make the next tx interrupt come back to last cmd condition
            }
            else
            {
                if (tx_status.q_id == TX_HQ)
                    tx_status.tx_state = WAITING_ACK; //hq waiting for an ack
                else
                {
                    tx_cmd_processed[TX_LQ]++; //counting #cmd sent, to remove in product code
                    tx_status.tx_state = TX_IDLE; //if lq, tx channel ready to send next command
                    tx_status.retry_counter = 0;
                    //update head of tx buffer after a complete is tranmitted, hq command only do it after ack is received!!!
                    tx_status.tx_q[tx_status.q_id].cmd_head = tx_status.tx_q[tx_status.q_id].buffer.mFIFOHead;

                    spi_navi_update_cmdfifosize(&tx_status.tx_q[tx_status.q_id]);

                    //trigger next command send in this tx interrrupt
                    spi_navi_fifotx_nextcmd();
                }
               // if (spi_tx_trigger_firstPacket == FALSE)
                {                    
                    //CSI_FIFO_SendEmpty(SOC_SPI);
                    //spi_navi_tx_off(); //clear CRQ to navi (spi master)
                }
            }
        }
        else //not last packet in the command, to continue sending
        {
            fifo_output_block(&tx_status.tx_q[tx_status.q_id].buffer, out_buffer, FIFO_DEPTH);
            {                    
            CSI_FIFO_Send(SOC_SPI, out_buffer,FIFO_DEPTH);
                            bDataSent = TRUE;
            }
        }
    }
    else //not normal tx transaction
    {
        if (tx_status.tx_state == TX_RESYNC) //in resync state, fill in SPI_SLAVE_READY packet
        {
            U8 outdata[FIFO_DEPTH];           
            if(GET_CS_STATUS()==1)
            {
                CSI_FIFO_SendEmpty(SOC_SPI);
                
                bDataSent = TRUE;
                spi_navi_tx_off();
            }
            else
            {
                if(!bResyncDataSent)
                {
                    bResyncDataSent = TRUE;
                    SET_REQ_PIN_FOR_DATA_SENDING(); //don't use CRQ in resync mode, master try to read up to 10times
                    for (counter=0; counter < FIFO_DEPTH; counter++)
                        outdata[counter] = in_buffer[FIFO_DEPTH-1-counter]; //send the reverse of the received
                    CSI_FIFO_Send(SOC_SPI, outdata,FIFO_DEPTH);
                    
                bDataSent = TRUE;
                }
            }
        }
        else
        {
        //    if (spi_tx_trigger_firstPacket == FALSE)
            {
            #if 0
                U8 outdata[FIFO_DEPTH];
               _memset(outdata,0,FIFO_DEPTH);
                CSI_FIFO_Send(SOC_SPI, outdata,FIFO_DEPTH);
            #else
            //    CSI_FIFO_SendEmpty(SOC_SPI);
            #endif
             //  spi_navi_tx_off(); //switch off tx while no data transmission going on
            }
        }
    }    

    #ifdef TEST_INT
    GPIO_Out_Write (GPIO_PORT_0,GPIO_PIN_4,FALSE);
    #endif
}


/***********************************************************************
*  Name         : spi_navi_fifo_reset
*  Description : 
*  Parameter  : none
*  Returns      : None
***********************************************************************/
void spi_navi_fifo_reset(void)
{
    //U8 counter;
    //SPI_ResetFIFO(SPI_NAVFIFO);
   CSI_StopFIFO(SOC_SPI);
    ///TODO:SQJ
    reset_counter++;
    rx_status.rx_state = RX_IDLE;
    tx_status.tx_state = TX_IDLE;
    spi_tx_trigger_firstPacket = FALSE;		//reset trigger, allow 1st cmd sending to trigger
    //for (counter =0; counter < TOTAL_RXQ; counter++)
    spi_navi_reset_cmdfifotail(&rx_status.rx_q[rx_status.q_id]); //flush incomplete command
    //for (counter =0; counter < TOTAL_TXQ; counter++)
    spi_navi_reset_cmdfifohead(&tx_status.tx_q[tx_status.q_id]); //flush incomplete command
    //SPI_EnableFIFO(SPI_NAVFIFO);
   // SPI_InitFIFOMode(SPI_NAVFIFO);
   CSI_StartFifo(SOC_SPI, 8,FALSE);
   ///TODO:SQJ
}

/***********************************************************************
*  Name         : spi_navi_reset_cmdfifotail
*  Description : 
*  Parameter  : cmd_fifo
*  Returns      : None
***********************************************************************/
void spi_navi_reset_cmdfifotail(SPI_NAVI_CMD_FIFO *cmd_fifo)
{
    /*U16 offset;

    if (cmd_fifo->buffer.mFIFOTail >= cmd_fifo->cmd_tail)
        offset = cmd_fifo->buffer.mFIFOTail - cmd_fifo->cmd_tail;
    else
        offset = cmd_fifo->buffer.mFIFOTail + (cmd_fifo->buffer.mFIFOSize - cmd_fifo->cmd_tail);
    cmd_fifo->buffer.mFIFOLength -= offset;*/
    cmd_fifo->buffer.mFIFOTail = cmd_fifo->cmd_tail; //reset tail to flush cmd being received
}


/***********************************************************************
*  Name         : spi_navi_reset_cmdfifohead
*  Description : 
*  Parameter  : cmd_fifo
*  Returns      : None
***********************************************************************/
void spi_navi_reset_cmdfifohead(SPI_NAVI_CMD_FIFO *cmd_fifo)
{
    /*U16 offset;
    if (cmd_fifo->buffer.mFIFOHead >= cmd_fifo->cmd_head)
        offset = cmd_fifo->buffer.mFIFOHead- cmd_fifo->cmd_head;
    else
        offset = cmd_fifo->buffer.mFIFOHead + (cmd_fifo->buffer.mFIFOSize - cmd_fifo->cmd_head);
    */
    cmd_fifo->buffer.mFIFOHead = cmd_fifo->cmd_head;
    //cmd_fifo->buffer.mFIFOLength += offset;
}

/***********************************************************************
*  Name         : spi_navi_update_cmdfifosize
*  Description : 
*  Parameter  : cmd_fifo
*  Returns      : None
***********************************************************************/
void spi_navi_update_cmdfifosize(SPI_NAVI_CMD_FIFO *cmd_fifo) /*note: length is #bytes in the buffer*/
{
    if (cmd_fifo->cmd_tail >= cmd_fifo->cmd_head)
        cmd_fifo->buffer.mFIFOLength = cmd_fifo->cmd_tail - cmd_fifo->cmd_head;
    else
        cmd_fifo->buffer.mFIFOLength = cmd_fifo->buffer.mFIFOSize - (cmd_fifo->cmd_head - cmd_fifo->cmd_tail);

}


/*---Private----------------------------------------------------------*/

/***********************************************************************
*  Name         : MonitorResynReq
*  Description : proc for cs pin
*  Parameter  : None
*  Returns      : None
***********************************************************************/
void MonitorResynReq(void)
{
    csStatus = GET_CS_STATUS();
    if(csStatus!=csStatusPre)
    {
        if(csStatus == 0)
        {
            //when CS pin asserted(low) by soc, a resync of spi is needed
            CLEAR_REQ_PIN_FOR_DATA_SENDING();
            spi_navi2up_resync_on = TRUE;
            spi_resync_required = TRUE;
        }
        else if(csStatus == 1)
        {
            //after SPI_Slave_Ready packet is successfully received by Navi, cs pin will be deactived
            spi_navi2up_resync_on = FALSE;
        }
    }
    csStatusPre = csStatus;
}

/***********************************************************************
*  Name         : trap_log_spi_error
*  Description : to save the error state
*  Parameter  : rx_error,tx_error,debugging_info
*  Returns      : None
***********************************************************************/
void trap_log_spi_error(U8 rx_error, U8 tx_error, char* debugging_info)
{
    if (rx_error != 0xFF)
    {
        rx_error_log |= rx_error;
        //save spi_rx_error_log to EEPROM (to be done!)
    }
    if (tx_error != 0xFF)
    {
        tx_error_log |= tx_error;
        //save spi_tx_error_log to EEPROM (to be done!)
    }
}

/***********************************************************************
*  Name         : trap_restart_system
*  Description : reset system
*  Parameter  : None
*  Returns      : None
***********************************************************************/
void trap_restart_system(void)
{
    //while (1); //to trigger watchdog reset
    //g_RteInfo.SystemReset();
    Sys_Reset();
}

/***********************************************************************
*  Name         : init_var
*  Description : init all the spi var
*  Parameter  : None
*  Returns      : None
***********************************************************************/
static void init_var(void)
{
    rx_status.packet_received = 0;
    rx_status.total_packet = 2;//0x10; //just make it unequal to packet received
    rx_status.repeat_counter = 0;
    rx_status.rx_state = RX_IDLE;
    fifo_init(&rx_status.rx_q[RX_HQ].buffer, rx_hqbuffer, SPI_NAVI_INP_HQBUF_SIZE); //rx_hq buffer init
    rx_status.rx_q[RX_HQ].cmd_head = 0;
    rx_status.rx_q[RX_HQ].cmd_tail= 0;
    fifo_init(&rx_status.rx_q[RX_LQ].buffer, rx_lqbuffer, SPI_NAVI_INP_LQBUF_SIZE); //rx_lq buffer init
    rx_status.rx_q[RX_LQ].cmd_head = 0;
    rx_status.rx_q[RX_LQ].cmd_tail= 0;

    tx_status.packet_transmitted = 0;
    tx_status.total_packet = 2;//0x10; //just make it unequal to packet transmitted
    tx_status.retry_counter = 0;
    tx_status.tx_state = TX_IDLE;
    tx_status.hq_ack_request = FALSE;
    fifo_init(&tx_status.tx_q[TX_HQ].buffer, tx_hqbuffer, SPI_NAVI_OUT_HQBUF_SIZE); //tx_hq buffer init
    tx_status.tx_q[TX_HQ].cmd_head = 0;
    tx_status.tx_q[TX_HQ].cmd_tail= 0;
    fifo_init(&tx_status.tx_q[TX_LQ].buffer, tx_lqbuffer, SPI_NAVI_OUT_LQBUF_SIZE); //tx_lq buffer init
    tx_status.tx_q[TX_LQ].cmd_head = 0;
    tx_status.tx_q[TX_LQ].cmd_tail= 0;

    rx_cmd_processed[RX_HQ] = 0;
    rx_cmd_processed[RX_LQ] = 0;
    tx_cmd_processed[TX_HQ] = 0;
    tx_cmd_processed[TX_LQ] = 0;
    rx_cmdid_processed[RX_HQ] = 0;
    rx_cmdid_processed[RX_LQ] = 0;

    tx_frameid[TX_HQ] = 0x00; //start from 1 to skip 0x00 (used as idle byte)
    tx_frameid[TX_LQ] = 0x00; //start from 1 to skip 0x00 (used as idle byte)
    
    spi_navi2up_resync_on = FALSE;
    spi_resync_required = FALSE;
    
    reset_counter = 0;
    spi_ove_counter =0;
    cserror_counter = 0;
    spi_tx_sending_timeout_counter = 0;
    spi_tx_ack_timeout_counter = 0;
    spi_tx_continuous_cmd_count = 0;
    power_on_wait = TRUE;
    tx_late_ack = FALSE;

    spi_tx_trigger_firstPacket = FALSE;
    spi_tx_ack = FALSE;

    rx_error_log = 0;	//record of SPI Rx errors, to be stored in E2PROM or print out to trace!
    tx_error_log = 0; 	//record of SPI Tx errors, to be stored in E2PROM or print out to trace!

    eSocDriverState = E_DRIVER_IDLE;
    eSocDriverControlState = E_IDLE_WORKSTATE;
}

/**************** END OF FILE *****************************************/
