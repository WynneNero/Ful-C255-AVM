/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
************************************************************************
* Object        : Exti_cfg.C
* Module        :
* Instance      :
* Description   :
*-----------------------------------------------------------------------
* Version:  0.1
* Date: 2011-11-24
* Author: Shao Guangxian
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*-----------------------------------------------------------------------
* 0.1	   Dec 02,2016   PEI Jingli     Initial version
*----------------------------------------------------------------------
* 0.2         Dec 20,2016   ShangQiuju  Add config according using hw.
 ----------------------------------------------------------------------
* 0.3          Dec 21,2016    PEI Jingli    Add ds03h hw version selection.
 ----------------------------------------------------------------------
* 0.4          Dec 22,2016    PEI Jingli    Add ds03h hw version selection for INTP6.
*-----------------------------------------------------------------------
* 0.5   	   Jan 18,2017    ZhangJie     Remove unused include headfile.
 ----------------------------------------------------------------------
* 0.6          Mar 09,2017   PEI Jingli     Delete test switch.
*=====================================================================*/
#include "Define.h"
#include "EXTI_if.h"

extern void PowerManager_CAN_DET_ISR(void);
extern void  Application_CANInhIsr(void);
extern void  Application_ACCOnIsr(void);
#ifdef USE_REVERSE_INTERRUPT_OPTION
extern void Application_ReverseINIsr(void);
#endif

/***********************************************************************
*  Name        : mcu_exti_callback
*  Description : is a fuction point array
                 when a interrupt occur,then call
                 or invoke a user function
*                FOR EXTI
***********************************************************************/
const Func_Void_Proc mcu_intp_callback[EXTI_NUM] =
{
    NULL,/* EXTI_00 */
    NULL,/* EXTI_01 */ 
    NULL,/* EXIT_02 */
	NULL,/* EXTI_03 */
    Application_ACCOnIsr,/* EXTI_04 */   
    NULL,/* EXTI_05 */   
	Application_ACCOnIsr,/* EXTI_06 */
    NULL,/* EXTI_07 */   
    NULL,/* EXTI_08 */   
    NULL,/* EXTI_09 */   

    Application_CANInhIsr,/* EXTI_10 */   
    NULL,/* EXTI_11 */  
    NULL,/* EXTI_12 */    
    NULL,/* EXTI_13 */
    NULL,/* EXTI_14 */
    NULL,/* EXTI_15 */
};

/**************** END OF FILE *****************************************/

