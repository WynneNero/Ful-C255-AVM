/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
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
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
*=====================================================================*/
#include "Core_cfg.H"
#include "TYPES.H"

#define IIC_MASTER_REC_LEN		9		//10
#define I2C_TARGET_ADDR 	0x15   // NextEV ICS address		
#define IIC_MASTER_SEND_LEN 9			// 11	// master write byte length, for test
/***********************************************************************
*  Name        : IIC_10ms_test
*  Description : None        
*  Parameter   : None
*  Returns     : None
***********************************************************************/
void IIC_10ms_test(void)
{
	U8 send_data[IIC_MASTER_SEND_LEN]={0x02, 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};		//,0x99,0xAA};
	static U8 reg_adr=0x04;	// delibrately make read address!= write address	//	0x31;		// master send, reg address to read
	static U8 write_dev_adr[4]={0xA1,0x00,0xA1};
	static U8 i2c_rec_data[IIC_MASTER_REC_LEN]={0x12,0xff,0xff};
	static U8 eprom_adr=0;
	BOOL bIIC_opResult=FALSE;
	
#ifdef IIC_TEST   		 
		eprom_adr++;
   #ifdef IO_SIMULATE_IIC_MASTER
		//	IO simulated test
		S_IIC_SendStart();
		S_IIC_SendData(&write_dev_adr[0],1);
		S_IIC_RecData(&i2c_rec_data[0],9);	// read data
		S_IIC_SendStop();		
   #else

	#ifdef IIC_MASTER_TEST
		#ifdef IIC_MASTER_READ_TEST
			#ifndef IIC_MASTER_READ_RESTART
					IIC_MasterReadFrame(I2C_TARGET_ADDR,&i2c_rec_data[0],8,0);
				#else					
					// first, send regsiter address
					IIC_MasterWriteFrame(I2C_TARGET_ADDR,&reg_adr,1,0);
					//STOP+START to replace Restart
					delay_us(700);
					IIC_MasterReadFrame(I2C_TARGET_ADDR,&i2c_rec_data[0],IIC_MASTER_REC_LEN,0);
				#endif			
			#else			
				IIC_MasterWriteFrame(I2C_TARGET_ADDR,&reg_adr,1,0);			
			#endif
		#endif
		
		#ifdef IIC_MASTER_WRITE_TEST
			IIC_MasterWriteFrame(I2C_TARGET_ADDR,&send_data[0],IIC_MASTER_SEND_LEN,0);	//also used to write EEPROM
		#endif		
	#endif
   #endif
}































