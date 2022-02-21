/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department :  CT AD NKG 
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   :
***********************************************************************/
/*-History--------------------------------------------------------------
* Ver    Date           Name        Changes and comment
* ----------------------------------------------------------------------
* 0.1    Jul 21,2016    PEI Jingli  Initial version
*----------------------------------------------------------------------
* 0.2  Dec 20,2016   ShangQiuju  remove unused files.
* ----------------------------------------------------------------------
* 0.3  Dec 29,2016   PEI Jingli     Delete comments
* ----------------------------------------------------------------------
* 0.4  Dec 29,2016    PEI Jingli    Add definition about stbc
*------------------------------------------------------------------------
* 0.5  Jan 24,2017  ZhangJie  Fix Coverity warnings.
*-----------------------------------------------------------------------
* 0.6  Apr 04,2017   PEI Jingli   Delete testing code.
*=====================================================================*/

#ifndef _STBC_CFG_H_
#define _STBC_CFG_H_ 


/**** Definition of constants ****/
/******************************************************************************
 *                                            wakeup factors config             
 *Define unmask wakeup factors for registers as WUFMSK0,WUFMSK20,WUFMSK_ISO0. 
 * bit val=0 unmask,  =1 mask
 ******************************************************************************/
/* WUFMSK0 used :Stop->Run, Deepstop->Run,  Cyclic stop->Cyclic Run 
* wakeup factors bit0:TNMI  bit1:WDTA0NMI  bit2:INTLVIL  bit3:  bit4:  bit5:INTP0  bit6:INTP1  bit7: INTP2  
* bit8:INTWDTA0  bit9:INTP3  bit10:INTP4  bit11:INTP5  bit12:INTP10  bit13:INTP11  bit14:WKTRG1  bit15:TAUJ0I0 
* bit16:TAUJ0I1  bit17:TAUJ0I2  bit18:TAUJ0I3  bit19:WTRG0  bit20:INTP6  bit21:INTP7  bit22:INTP8  bit23:INTP12
* bit24:INTP9  bit25:INTP13  bit26:INTP14  bit27:INTP15  
*/
#define STBC_CFG_STOP_WUFMSK0          0xffeffdffu /*INTP6 + INTP3*/
/* WUFMSK20 used :Deepstop->Cyclic Run,  Cyclic stop->Cyclic Run 
*wakeup factors bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:                                                     */
#define STBC_CFG_STOP_WUFMSK20        0xffffffffu
/* WUFMSK_ISO0 used :Stop->Run, Cyclic stop->Cyclic Run
*wakeup factors bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:  bit:                                                     */
#define STBC_CFG_STOP_WUFMSK_ISO0  0xffffffffu

/**** Definition of types ****/

/**** Declaration of constants ****/
/**** Declaration of variables ****/


/**** Declaration of functions ****/
//void Clock_setup_poweron(void);
//void Clock_setup_sleep(void);
//void Clock_setup_wakeup(void);
#endif /*_STBC_CFG_H_*/

/****************************** END OF FILE ***************************/

