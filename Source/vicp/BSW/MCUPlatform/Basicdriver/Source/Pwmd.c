/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  pwmd.c 
* Module        : 
* Instance      : 
* Description   : hardware pwm
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
------------------------------------------------------------------------
* 0.1     Aug 18,2016   PEI Jingli  Initial 
------------------------------------------------------------------------
* 0.2     Nov 10,2016   PEI Jingli  Add PWD_SetDuty
------------------------------------------------------------------------
* 0.3     Nov 17,2016   PEI Jingli  Change PWD_SetDuty
------------------------------------------------------------------------
* 0.4     Dec 15,2016   PEI Jingli   Add dutyType params for PWM interfaces
------------------------------------------------------------------------
* 0.5     Dec 16,2016   PEI Jingli   Add return type of PWD_SetDuty,add parameter checking
------------------------------------------------------------------------
* 0.6     Dec 20,2016   PEI Jingli   Change return value to ERR_TYPE
*-----------------------------------------------------------------------
* 0.7     Dec 20,2016   ShangQiuju change irq.h to irq_if.h
*-----------------------------------------------------------------------
* 0.8     Dec 29,2016   PEI Jingli  Add extern pwmClocKCfg and pwmChannelClocK for temporary
*-----------------------------------------------------------------------
* 0.9     Jan 03,2017   PEI Jingli   Changes for codeReview result
*-----------------------------------------------------------------------
* 1.0    Jan 10,2017   PEI Jingli    Change parameters checking 
*-----------------------------------------------------------------------
* 1.1    Jan 13,2017   PEI Jingli    Correct error in PWMD_Unit_Deinit
*----------------------------------------------------------------------
* 1.2    Jan 24,2017    ZhangJie     Fix Coverity warning.
*-----------------------------------------------------------------------
* 1.3   Apr 1,2017     PEI Jingli   Fix include files.
*======================================================================*/

/*============================================================================
* Includes
============================================================================*/
#include "Pwmd_cfg.h"
#include "Pwmd_if.h"
#include "Clock_cfg.h"
#include "SYS_ASSERT_IF.H"


/***********************************************************************
*  Name        : PWMD_Module_Init
*  Description : Initialize all PWM channels
*       permit PWBA, set and start PWMCLKm
*  Parameter :None
*  Returns     : None
***********************************************************************/
void PWMD_Unit_Init(void)
{
    PWM_CLKTYPE index=E_PWMCLK0;
    
    /*Before writing BRS, PWBAn.PWBATEm should be 0 first,that is all PWMCLK be stopped*/ 
    while(PWBA0_REG_TE&0x0Fu)
    {
        PWBA0_REG_TT                  = 0x0FU;
    }

    /* Setting of the clock cycle of PWMCLKm.
    PWBAnBRSm    - PWBAnBRSm Register
    b15:b11                   - Reserved set to 0
    b10:b 0        PWBAnBRSm  - Register for setting the clock cycle of PWMCLKm.   */
    for( index=E_PWMCLK0;index<=E_PWMCLK3; index++)
    {
       PWBA0_REG_BRS((U8)index)=pwmClocKCfg[index];
    }
    
    /* Control operations of PWSA.
    PWSAnCTL     - PWSAnCTL Register
    b 7:b 6                   - Reserved set to 0
    b 0            PWSAnENBL  - Operation Permission Control                          - Operation is enabled. */
    PWSA0_REG_CTL                = 0x01U;
    
    /* Start for PWMCLKm.
    PWBAnTS      - PWBAnTS Register
    b 7:b 4                   - Reserved set to 0
    b 3            PWBAnTS3   - Start trigger bit for PWMCLK3                         - set to 1'b
    b 2            PWBAnTS2   - Start trigger bit for PWMCLK2                         - set to 1'b
    b 1            PWBAnTS1   - Start trigger bit for PWMCLK1                         - set to 1'b
    b 0            PWBAnTS0   - Start trigger bit for PWMCLK0                         - Starts the output of PWMCLK0. */
    PWBA0_REG_TS                  = 0x0FU;
    while( (PWBA0_REG_TE & 0x0FU) != 0x0FU ) 
    {
        /* Waiting for PWBA0TE to set. */
    }
}

/***********************************************************************
*  Name        : PWMD_Unit_Deinit
*  Description :De-Initialize all PWM channels
*       stop PWBA, stop PWMCLKm
*  Parameter :None
*  Returns     : None
***********************************************************************/
void PWMD_Unit_Deinit(void)
{
   /* Stop PWMCLKm.
    PWBAnTT      - PWBAnTS Register
    b 7:b 4                   - Reserved set to 0
    b 3            PWBAnTT3   - Stop trigger bit for PWMCLK3                         - set to 0'b
    b 2            PWBAnTT2   - Stop trigger bit for PWMCLK2                         - set to 0'b
    b 1            PWBAnTT1   - Stop trigger bit for PWMCLK1                         - set to 0'b
    b 0            PWBAnTT0   - Stop trigger bit for PWMCLK0                         - Stop the output of PWMCLK0. */
    PWBA0_REG_TT                  = 0x0FU;
    while(PWBA0_REG_TE & 0x0FU)  
    {
        /* Waiting for PWBA0TE to set. */
    }

    /* Setting of the clock cycle of PWMCLKm to be default. PWBAnBRSm Register */

    /* Control operations of PWSA.
    PWSAnCTL     - PWSAnCTL Register
    b 7:b 6                   - Reserved set to 0
    b 0            PWSAnENBL  - Operation Permission Control                          - Operation is disabled. */
    PWSA0_REG_CTL                = 0x00U;

}

/***********************************************************************
*  Name        : PWMD_GetFrequency
*  Description : Get the frequency of  a pwm_channel.
*             when PERI2 is 40MHZ, max of pwm Frequency=9765HZ
*  Returns    : BOOL
*  Parameter : pwm_channel  0~(PWM_CHANNEL_MAX-1)
*  Returns     : clock frequency, HZ
***********************************************************************/
U32 PWMD_GetFrequency(U8 pwm_channel)
{
    U32 freq=PERI2_CLKDOMAIN_HZ; /* pclk is iperi2*/
    PWM_CLKTYPE ck=E_PWMCLK0;
    assert_param(pwm_channel<PWM_CHANNEL_MAX);

    /*caculate PWMCLKm frequency*/
    ck=pwmChannelClocK[pwm_channel];
    if(0u==pwmClocKCfg[ck])
    {/* 1 div*/
        freq=freq;
    } 
    else
    {
        freq=freq/(2u*pwmClocKCfg[ck]);
    }

    /*caculate pwm channel frequency*/
    freq=freq/(0x0FFFu+1u);
    
    return freq;  
}

/***********************************************************************
*  Name        : PWMD_Config
*  Description : Configrature a pwm channel
*  Parameter  : pwm_channel -can be 0 to PWM_CHANNEL_MAX-1
*                 duty - percentage of high level , can't large than dutyType
*         dutyType - Enum_PwmdRatio_Type
*            frequency = PWMD_GetFrequency(pwm_channel),
*                   when PERI2 is 40MHZ, max of pwm Frequency=9765HZ
*  Returns    : ERR_TYPE
***********************************************************************/
ERR_TYPE PWMD_Config( U8 pwm_channel, Enum_PwmdRatio_Type dutyType, U16 duty )
{
    ERR_TYPE eRet =ERR_OK;
    assert_param(IS_PWMD_CHANNEL(pwm_channel));
    assert_param(dutyType<=E_PWMD_RATIO4095);
    assert_param(dutyType<duty);

    if(duty>dutyType)
    {
        eRet =ERR_VALUE;
    }
    else
    {    
        /* Sets the setting condition for PWGA_TOUTn output.
        PWGAnCSDR    - PWM Output Set Condition Register. For Low level period
        b15:b12                   - Reserved set to 0
        b11:b 0        PWGAnCSDR  - Setting condition for PWM output. 
                                   High Level = (PWGAnCRDR - PWGAnCSDR) * ( 1 / PWMCLKm )    */
        PWGAn_REG_CSDR(pwm_channel)=(U16)((U32)0x0FFFu*(dutyType-duty)/dutyType );
    
        /* Sets the reset condition for PWGA_TOUTn output.
        PWGAnCRDR    - PWM Output Set Condition Register
        b15:b12                   - Reserved set to 0
        b11:b 0        PWGAnCRDR  - Reset condition for PWM output. */
        PWGAn_REG_CRDR(pwm_channel)=0x0FFFu;
        
        /* Select the count clock from PWBA.
        PWGAnCTL     - PWGA Control Register
        b 7:b 6                   - Reserved set to 0
        b 0            PWGAnCKS   - Count Clock Enable Input PWMCLK3 to PWMCLK0 Select */
        PWGAn_REG_CTL(pwm_channel)= (U8)(pwmChannelClocK[pwm_channel]);
    }
    
    return eRet; 
}

/***********************************************************************
*  Name        : PWMD_Cmd
*  Description : Enable one channel of PWMs
*  Parameter  :  pwm_channel can select 0 to PWM_CHANNEL_MAX-1
                 state can be ENABLE or DISABLE
*  Returns     : BOOL
***********************************************************************/
BOOL PWMD_Cmd( U8 pwm_channel, FUNCTION_STATE state )
{
    assert_param(IS_PWMD_CHANNEL(pwm_channel));

    if(state)
    {
        /* Start for respective channels simultaneously.
        b31:b 0        SLPWGA     - Trigger start and stop to multiple channels simultaneously. 
                                                                                                 - set bit to 1             */
        if(pwm_channel<32u)
        {
          PWGAn_REG_SLPWGA(0u)    |=  (1u<<pwm_channel);
        }
        else if(pwm_channel<64u)
        {
          PWGAn_REG_SLPWGA(1u)    |=  (1u<<(pwm_channel-32u));
        }
        else if(pwm_channel<72u)
        {
          PWGAn_REG_SLPWGA(2u)    |=  (1u<<(pwm_channel-64u));
        }
    }
    else
    {
       /* Stop for respective channels simultaneously.
        b31:b 0        SLPWGA     - Trigger start and stop to multiple channels simultaneously. 
                                                                                                 - set bit to 0             */
       if(pwm_channel<32u)
       {
        PWGAn_REG_SLPWGA(0u)    &= ~ (1u<<pwm_channel);
       }
       else if(pwm_channel<64u)
       {
        PWGAn_REG_SLPWGA(1u)    &=  ~(1u<<(pwm_channel-32u));
       }
       else if(pwm_channel<72u)
       {
        PWGAn_REG_SLPWGA(2u)    &= ~ (1u<<(pwm_channel-64u));
       }
    }
    return TRUE;
}

/***********************************************************************
*  Name        : PWMD_SetDuty
*  Description : change duty without stop pwm output
*  Parameter  : pwm_channel- can select 0 to PWM_CHANNEL_MAX-1
*          dutyType- range in Enum_PwmdRatio_Type
*                 duty- percentage of high level , can't large than dutyType
*  Returns     : ERR_TYPE
***********************************************************************/
ERR_TYPE PWMD_SetDuty( U8 pwm_channel, Enum_PwmdRatio_Type dutyType, U16 duty )
{
    ERR_TYPE eRet =ERR_OK;
    assert_param(IS_PWMD_CHANNEL(pwm_channel));
	
    if(duty>dutyType)
    {
        eRet =ERR_VALUE;
    }
    else
    {
        /* Sets the setting condition for PWGA_TOUTn output.
        PWGAnCSDR    - PWM Output Set Condition Register. For Low level period
        b15:b12                   - Reserved set to 0
        b11:b 0        PWGAnCSDR  - Setting condition for PWM output. 
                                  High Level = (PWGAnCRDR - PWGAnCSDR) * ( 1 / PWMCLKm )        */
        PWGAn_REG_CSDR(pwm_channel)=(U16)((U32)0x0FFFu*(dutyType-duty)/dutyType );
     
        /* Sets the reset condition for PWGA_TOUTn output.
        PWGAnCRDR    - PWM Output Set Condition Register
        b15:b12                   - Reserved set to 0
        b11:b 0        PWGAnCRDR  - Reset condition for PWM output. */
        PWGAn_REG_CRDR(pwm_channel)=0x0FFFu;
     
        PWGAn_REG_RDT(pwm_channel)=0x01U;  /*rewrite register which changed*/
    }

    return eRet; 
}

/***********************************************************************
*  Name        : PWMD_ADCInit
*  Description : Enable AD diagnostic
*  Parameter  :  pwm_channel can select 0 to PWM_CHANNEL_MAX-1
                 adc_channel  for ADCA0
*  Returns     : None
***********************************************************************/
void PWMD_ADCInit( U8 pwm_channel, U8 adc_channel)
{
    /* Setting of the ADCA corresponding to each channel.
    PWSAnPVCRx_y - PWSAnPVCRx_y Register
    b31:b29                   - Reserved set to 0
    b28            PWSAnSLADy - ADCTL Select (odd-numbered channel),ADCA0 or ADCA1
    b27            PWSAnVRDTy - This bit indicates the setting value of the
                               ADCAnPWDVCR.MPXE bit (oddnumbered channel).         
    b26:b24        PWSAnVRDTy - This bit indicates the setting value of the
                               ADCAnPWDVCR.MPXV[2:0] bits (oddnumbered channel).
    b23:b22        PWSAnVRDTy - This bit indicates the setting value of the
                               ADCAnPWDVCR.ULS[1:0] bits (oddnumbered channel).  Upper limit and lower limit table select
                               00- not checked
                               01- checked for ADCAnULLMTBR0   10- for ADCAnULLMTBR1  11-for ADCAnULLMTBR2
    b21:b16        PWSAnVRDTy - This bit indicates the setting value of the
                               ADCAnPWDVCR.GCTRL[5:0] bits (odd-numbered channel). Select physical channel  
    b15:b13                   - Reserved set to 0
    b12            PWSAnSLADx - ADCTL Select (even-numbered channel)      
    b11            PWSAnVRDTx - This bit indicates the setting value of the 
                               ADCAnPWDVCR.MPXE bit. (evennumbered channel)   
    b10:b 8        PWSAnVRDTx - These bits indicate the setting value of the
                               ADCAnPWDVCR.MPXV[2:0] bits. (even-numbered channel)  
    b 7:b 6        PWSAnVRDTx - These bits indicate the setting value of the
                               ADCAnPWDVCR.ULS[1:0] bits. (even-numbered channel)    
    b 5:b 0        PWSAnVRDTx - These bits indicate the setting value of the
                               ADCAnPWDVCR.GCTRL[5:0] bits. (even-numbered channel). Select physical channel */
    if(pwm_channel%2)
      PWSA0_REG_PVCRx_y(pwm_channel)=0x00400000U; /*odd numb  16~31bit*/
    else
      PWSA0_REG_PVCRx_y(pwm_channel)=0x00000040U; /*even numb bit 0~15bit*/
}


/***********************************************************************
*  Name        : PWD_LED_Init
*  Description : Init LED pwd
*  Parameter  :  None
*  Returns     : None
***********************************************************************/
void PWD_LED_Init(void)
{
	PWMD_Unit_Init();
	PWMD_Config(22, E_PWMD_RATIO100,0);
	PWMD_Cmd(22,0x01);
}

