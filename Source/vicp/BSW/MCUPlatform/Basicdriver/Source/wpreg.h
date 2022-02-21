/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.		           *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									                   *
************************************************************************
* Object        :  wpreg.h 
* Module        : 
* Instance      : 
* Description   : definition about write-protected registers 
*-----------------------------------------------------------------------
* Version: 
* Date: 
* Author: 
***********************************************************************/
/*-History--------------------------------------------------------------
* Version    Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1  Apr 15,2016   PEI Jingli Initialize
* ----------------------------------------------------------------------
* 0.2  Nov 17,2016   PEI Jingli Define PROTECTED_WRITE.
*------------------------------------------------------------------------
* 0.3  Jan 24,2017  ZhangJie  Fix Coverity warning.
===============================================================*/
#ifndef  _WPREG_H
#define   _WPREG_H

#define CONTRL_CLUST0_REG_PROTCMD0	 (*(CPU_REG32 *)(0xFFF80000u)) /*for MOSCE ROSCE SOSCE IOHOLD*/
#define CONTRL_CLUST0_REG_PROTS0          (*(CPU_REG32 *)(0xFFF80004u))
#define CONTRL_CLUST1_REG_PROTCMD1	 (*(CPU_REG32 *)(0xFFF88000u)) /*for PLLE*/
#define CONTRL_CLUST1_REG_PROTS1         (*(CPU_REG32 *)(0xFFF88004u))


#define PROTCMD_WRITE_EN_VAL       (0xA5U)     /* Protection commands to enable writing */
/* control protection cluster */
#define CLUST0_PROTCMD0_WRITEENABLE()    (CONTRL_CLUST0_REG_PROTCMD0=PROTCMD_WRITE_EN_VAL)
#define CLUST0_PROTS0_ISERR()    (CONTRL_CLUST0_REG_PROTS0==1u)
#define CLUST1_PROTCMD1_WRITEENABLE()    (CONTRL_CLUST1_REG_PROTCMD1=PROTCMD_WRITE_EN_VAL)
#define CLUST1_PROTS1_ISERR()    (CONTRL_CLUST1_REG_PROTS1==1u)
/* clock monitors control and test protection cluster */

#define PROTECTED_WRITE(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;    \
                                                  (reg)=(value);   \
                                                  (reg)=~(value); \
                                                  (reg)=(value);   \
                                                  }while((pstatus)==1u)


#endif/*_WPREG_H */

