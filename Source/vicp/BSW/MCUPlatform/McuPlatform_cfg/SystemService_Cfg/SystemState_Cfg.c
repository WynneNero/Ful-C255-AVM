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
* 0.1    Jun 26,2016    PEI Jingli  Initial version
* ----------------------------------------------------------------------
* 0.2    Aug 01,2016    PEI Jingli  Add calling of signal 
* ----------------------------------------------------------------------
* 0.3    Aug 01,2016    PEI Jingli  re-structure 
* ----------------------------------------------------------------------
* 0.4    Dec 28,2016    PEI Jingli  Rename Sig_ADInit
* ----------------------------------------------------------------------
* 0.5    Jan 09,2017    PEI Jingli  Add initial interfaces of pwmd complex
*------------------------------------------------------------------------
* 0.6   Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warning.
* ----------------------------------------------------------------------
* 0.7     Jan 13,2017     PEI Jingli  Correct error when S2 to S1
*-----------------------------------------------------------------------
* 0.8     Jan 24,2017   ZhangJie   Remove unused include file.
*------------------------------------------------------------------------
* 0.9    Mar 08,2017  ZhangJie    Add  cpu usage rate init task.
*------------------------------------------------------------------------
* 1.0    Apr 07,2017  ZhangJie    Fix warnings of external interface.
*=====================================================================*/
#include "SystemState_Cfg.h"
#include "config.h"

extern void Application_S0Init(void);
extern void Application_GotoSleep(void);
extern void EEPDriver_Init(void);
extern void EED_Load_Request(void);
extern void EED_ResetInit(void);
extern void EED_S1Init(void);
extern void EED_S1Init(void);
extern void Sig_ADInit(void);
extern void Sig_ADDeInit(void);
extern void Sig_DioInit(void);
extern void Sig_DioDeInit(void);
//extern void PowerManager_DeInit(void);
extern void SocDriver_Init(void);
extern void SocDriver_S0Init(void);
extern void SocDriver_DeInit(void);
extern void SocManager_Init(void);
extern void SocManager_DeInit(void);
extern void SocMsg_Init(void);
extern void SocMsg_DeInit(void);
extern void SocTransmitManager_Init(void);
extern void SocTransmitManager_DeInit(void);
//extern void keyboard_create(void);
//extern void illum_lcd_reset_create(void);
extern void CanDriver_Init(void);
extern void CanManager_Init(void);
//extern void eng_comm_create(U8 is_eng_first_connect);
#ifdef __DEBUG__
extern void CpuRate_Init(void);
#endif
extern void Pwmd_ComplexDriver_Init(void);
extern void Pwmd_ComplexDriver_DeInit(void);
//extern void RTC_PowerOn_Init(void);

#if (SYSTEM_STATE_METHOD== SYSSTATE_FULLSTATE)
/*Run in the first task and init all application's*/
void SysState_apResetContainer(void)
{
    /* Add the application initialization function here! */
    Sig_ADInit();
    Sig_DioInit();
    EED_ResetInit();
    SocDriver_S0Init();
    Application_S0Init();
    Pwmd_ComplexDriver_Init();	
	CanManager_Init();
	//RTC_PowerOn_Init();
}

/*
* Pointers to the functions that are to be carried out during state transition from state
* SX to state SY. The last entry in the array must be a NULL.
*/
void SysState_apS0ToS1Container(void)
{
    /* Add the application initialization function here! */
    /*init S1 state module*/
    /*load 2 phase eeprom*/
}

void SysState_apS1ToS0Container(void)
{
    /* Add the application initialization function here! */

}

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
void SysState_apS0ToS2Container(void)
{
	/* Add the application initialization function here! */	
    EED_Load_Request();
   #ifdef EOL_OPTION   //EOL only can woking in first power on 
    EolUartDriver_Init();
    EolMsg_Init();
    EOLInit();
    EolService_Init();
#endif
}

void SysState_apS1ToS2Container(void)
{ 
    /* Add the application initialization function here! */
    Sig_DioInit();
    Sig_ADInit();
    Pwmd_ComplexDriver_Init();
}

void SysState_apS2ToS1Container(void)
{
	/* Add the application initialization function here! */
    Sig_ADDeInit();
    Sig_DioDeInit();
    Pwmd_ComplexDriver_DeInit();

    /*the last function to goto sleep*/
    Application_GotoSleep();
}

void SysState_apS2ToS0Container(void)
{
    /* Add the application initialization function here! */

}
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 2) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
void SysState_apS0ToS3Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS1ToS3Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS2ToS3Container(void)
{ 
	/* Add the application initialization function here! */
    Sig_DioInit();
	CanDriver_Init();
	//CanManager_Init();
	SocDriver_Init();
	SocMsg_Init();
	SocManager_Init();
	SocTransmitManager_Init();
#ifdef CAN_DIAG_OPTION
    CanDiagDtcInit();
    CanDiagServiceInit();
#endif
	#ifdef __DEBUG__
    CpuRate_Init();
	#endif
    PWD_LED_Init();
    DescSecurityGetAttCounter();
}

void SysState_apS3ToS2Container(void)
{
    /* Add the application initialization function here! */
//	PowerManager_DeInit();
	SocTransmitManager_DeInit();
	SocManager_DeInit();
	SocMsg_DeInit();
	SocDriver_DeInit();
}

void SysState_apS3ToS1Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS3ToS0Container(void)
{
    /* Add the application initialization function here! */

}
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
void SysState_apS0ToS4Container(void)
{
    /* Add the application initialization function here! */
    EED_Load_Request();
    Sig_ADInit();
    Sig_DioInit();
}

void SysState_apS1ToS4Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS2ToS4Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS3ToS4Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS4ToS3Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS4ToS2Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS4ToS1Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS4ToS0Container(void)
{
    /* Add the application initialization function here! */
}
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
void SysState_apS0ToS5Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS1ToS5Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS2ToS5Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS3ToS5Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS4ToS5Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS5ToS4Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS5ToS3Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS5ToS2Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS5ToS1Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS5ToS0Container(void)
{
    /* Add the application initialization function here! */
}
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
void SysState_apS0ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS1ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS2ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS3ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS4ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS5ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS6ToS5Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS6ToS4Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS6ToS3Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS6ToS2Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS6ToS1Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS6ToS0Container(void)
{
    /* Add the application initialization function here! */
}
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
void SysState_apS0ToS7Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS1ToS7Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS2ToS7Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS3ToS7Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS4ToS7Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS5ToS7Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS6ToS7Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS7ToS6Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS7ToS5Container(void)
{
    /* Add the application initialization function here! */

}

void SysState_apS7ToS4Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS7ToS3Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS7ToS2Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS7ToS1Container(void)
{
    /* Add the application initialization function here! */
}

void SysState_apS7ToS0Container(void)
{
    /* Add the application initialization function here! */

}
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */


/* Vector with pointers to state initialisation transition functions. */
const Func_Void_Proc SysState_apToS0[] =
{
    NULL,
    SysState_apS1ToS0Container,
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
    SysState_apS2ToS0Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 2) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
    SysState_apS3ToS0Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    SysState_apS4ToS0Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    SysState_apS5ToS0Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS6ToS0Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS0Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
};

const Func_Void_Proc SysState_apToS1[] =
{
    SysState_apS0ToS1Container,
    NULL,
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
    SysState_apS2ToS1Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 2) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
    SysState_apS3ToS1Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    SysState_apS4ToS1Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    SysState_apS5ToS1Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS6ToS1Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS1Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */

};

const Func_Void_Proc SysState_apToS2[] =
{
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
    SysState_apS0ToS2Container,
    SysState_apS1ToS2Container,
    NULL,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 2) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
    SysState_apS3ToS2Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    SysState_apS4ToS2Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    SysState_apS5ToS2Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS6ToS2Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS2Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
    NULL
};

const Func_Void_Proc SysState_apToS3[] =
{
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
    SysState_apS0ToS3Container,
    SysState_apS1ToS3Container,
    SysState_apS2ToS3Container,
    NULL,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    SysState_apS4ToS3Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    SysState_apS5ToS3Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS6ToS2Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS3Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
    NULL
};

const Func_Void_Proc SysState_apToS4[] =
{
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    SysState_apS0ToS4Container,
    SysState_apS1ToS4Container,
    SysState_apS2ToS4Container,
    SysState_apS3ToS4Container,
    NULL,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    SysState_apS5ToS4Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS6ToS4Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS4Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
    NULL
};

const Func_Void_Proc SysState_apToS5[] =
{
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    SysState_apS0ToS5Container,
    SysState_apS1ToS5Container,
    SysState_apS2ToS5Container,
    SysState_apS3ToS5Container,
    SysState_apS4ToS5Container,
    NULL,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS6ToS5Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS5Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
    NULL
};

const Func_Void_Proc SysState_apToS6[] =
{
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    SysState_apS0ToS6Container,
    SysState_apS1ToS6Container,
    SysState_apS2ToS6Container,
    SysState_apS3ToS6Container,
    SysState_apS4ToS6Container,
    SysState_apS5ToS6Container,
    NULL,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS7ToS6Container,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
    NULL
};

const Func_Void_Proc  SysState_apToS7[] =
{
#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    SysState_apS0ToS7Container,
    SysState_apS1ToS7Container,
    SysState_apS2ToS7Container,
    SysState_apS3ToS7Container,
    SysState_apS4ToS7Container,
    SysState_apS5ToS7Container,
    SysState_apS6ToS7Container,
    NULL,
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */
    NULL
};

#elif (SYSTEM_STATE_METHOD== SYSSTATE_UPDOWNSTATE)

void SysState_ResetContainer(void)
{
    /* Add the application initialization function here! */

}

void SysState_InitS1Container(void)
{
    /* Add the application initialization function here! */

}

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
void SysState_InitS2Container(void)
{
    /* Add the application initialization function here! */

}

#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
void SysState_InitS3Container(void)
{
    /* Add the application initialization function here! */
}

#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
void SysState_InitS4Container(void)
{
    /* Add the application initialization function here! */

}

#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
void SysState_InitS5Container(void)
{
    /* Add the application initialization function here! */

}

#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
void SysState_InitS6Container(void)
{
    /* Add the application initialization function here! */

}

#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
void SysState_InitS7Container(void)
{
    /* Add the application initialization function here! */

}

#endif
/* Vector with pointers to state initialisation transition functions. */
const Func_Void_Proc SysState_Init[] =
{
    SysState_InitS1Container

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
    ,SysState_InitS2Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 2) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
    ,SysState_InitS3Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    ,SysState_InitS4Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    ,SysState_InitS5Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    ,SysState_InitS6Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    ,SysState_InitS7Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */

};

void  SysState_DeInitS1Container(void)
{
    /* Add the application initialization function here! */

}

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
void SysState_DeInitS2Container(void)
{
    /* Add the application initialization function here! */

}
#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
void SysState_DeInitS3Container(void)
{
    /* Add the application initialization function here! */

}
#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
void SysState_DeInitS4Container(void)
{
    /* Add the application initialization function here! */

}
#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
void SysState_DeInitS5Container(void)
{
    /* Add the application initialization function here! */
}
#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
void SysState_DeInitS6Container(void)
{
    /* Add the application initialization function here! */

}
#endif

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
void SysState_DeInitS7Container(void)
{
    /* Add the application initialization function here! */
}
#endif

/* Vector with pointers to state deinitialisation transition functions. */
const Func_Void_Proc SysState_DeInit[] =
{
    SysState_DeInitS1Container

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 2u)
    ,SysState_DeInitS2Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 2) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 3u)
    ,SysState_DeInitS3Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 3) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 4u)
    ,SysState_DeInitS4Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 4) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 5u)
    ,SysState_DeInitS5Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 5) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 6u)
    ,SysState_DeInitS6Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 6) */

#if (SYS_CFG_NO_OF_SYSTEM_STATES > 7u)
    ,SysState_DeInitS7Container
#endif /* #if (SYS_CFG_NO_OF_SYSTEM_STATES > 7) */

};
#endif
/**************** END OF FILE *****************************************/

