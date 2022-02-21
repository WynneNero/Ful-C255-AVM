/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
------------------------------------------------------------------------
* 0.1	   Sep 20,2016  PEI Jingli  Initial version
------------------------------------------------------------------------
* 0.2	   Sep 26,2016  PEI Jingli  Modify micro defination	
*------------------------------------------------------------------------
* 0.3          Jan 24,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.4         Mar 17,2017 Pei Jingli   Fix headfile.
*------------------------------------------------------------------------
* 0.5   Apr 01,2017   PEI Jingli  Fix headfile included.
*=====================================================================*/
#ifndef _EEPDRIVER_EEL_H_
#define _EEPDRIVER_EEL_H_
#include "CONFIG.H"
#include "Define.H"
#include "EEPTable_Cfg.h"
#include "Clock_cfg.h"
#include "EEPJobManager.h"

#define  DATAFLASH_BASE_ADDR    ( (CPU_INT32U )0xFF200000u)
/*****************************************************************************************************************
 *  Important definitions for run-time configuration of the FDL: 
 *   - Frequency -
 *****************************************************************************************************************/
/* The Flash programming hardware is provided with a clock, derived from the CPU subsystem frequency. Check that 
   the frequency is correct as this has an impact on the programming quality and performance! */
#define CPU_FREQUENCY_MHZ       (CPUCLK_NORMAL_HZ/1000000u)                              /**< CPU frequency in MHz. >*/

/*****************************************************************************************************************
 *  Important definitions for run-time configuration of the FDL: 
 *   - EEL/FDL Pool -
 *****************************************************************************************************************/
/* The physical erase unit of the Data Flash is 64Byte. 
   The Renesas EEL works with a ring buffer consisting of ring buffer (virtual) blocks that merge a certain number 
   of physical blocks.
   E.g. virtual block size of 2kB equals 32 physical blocks of 64Bytes --> EEL_VIRTUALBLOCKSIZE = 32
        virtual block size of 4kB equals 64 physical blocks of 64Bytes --> EEL_VIRTUALBLOCKSIZE = 64
   
   Note: If the Renesas EEL is not used, an alignment is not necessary "EEL_VIRTUALBLOCKSIZE" need not be defined 
   and the pools start and size definitions can be set free to the applicaiton needs */
#define EEL_VIRTUALBLOCK_LEN    64u       /*bytes  */            
#define EEL_VIRTUALBLOCKSIZE    32u       /* no. of blocks for 2k   */           

#define FDL_POOL_SIZE           (16u * EEL_VIRTUALBLOCKSIZE)    /**< Number of Data Flash blocks, accessible by 
                                                                     the FDL. Typically it is the complete 
                                                                     no. of available Data Flash blocks */    
#define EEL_POOL_START        (1u * EEL_VIRTUALBLOCKSIZE)     /**< 1st block of the EEL pool */
#define EEL_POOL_SIZE           (6u * EEL_VIRTUALBLOCKSIZE)     /**< no. of blocks for the EEL pool */     


/******************************************************************************************************************
* Important definitions for run-time configuration of the EEL
******************************************************************************************************************/
#define EEL_CONFIG_VBLK_SIZE                    32u           /**< Virtual block size (# physical Flash blocks) */
#define EEL_CONFIG_VBLK_CNT_REFRESH_THRESHOLD    3u           /**< Threshold for minimum no. of prepared blocks */
#define EEL_CONFIG_ERASE_SUSPEND_THRESHOLD      10u           /**< Threshold for erase suspend cnt. Exceeding this 
                                                                  results in a warning */
#define EEL_CONFIG_IDX_NUM                      EED_nLastBlock            /** Number of Data sets. be equal to EED_nLastBlock */


extern EEO_ConfigType EEPDriver_ConfigData;

#endif /*_EEPDRIVER_EEL_H_*/
/****************************** END OF FILE ***************************/

