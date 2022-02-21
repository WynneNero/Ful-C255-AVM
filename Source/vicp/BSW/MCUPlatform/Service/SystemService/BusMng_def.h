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
* 
*=====================================================================*/
/**** Definition of constants ****/

/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
#ifdef BUSMNG_PASS_1
    #undef BUSMNG_PASS_1
    #define BEGIN_BUSDESCS       typedef enum {
    #define END_BUSDESCS         BUSMNG_BUS_MAXNUM}BUSType; 
    #define BUSDESC(x)   x,

    #define BEGIN_DEVDESCS	
    #define END_DEVDESCS		
    #define DEVDESC(x,y)      
	
   #include <BUSMNG_CFG.h>

#endif

#ifdef BUSMNG_PASS_2
    #undef BUSMNG_PASS_2

    #define BEGIN_BUSDESCS      
    #define END_BUSDESCS          
    #define BUSDESC(x)   
	
    #define BEGIN_DEVDESCS	typedef enum {
    #define END_DEVDESCS		BUSMNG_DEV_MAXNUM}DevType;
    #define DEVDESC(x,y)      x,

    #include <BUSMNG_CFG.h>
  
#endif

#ifdef BUSMNG_PASS_3
    #undef BUSMNG_PASS_3
    #define BEGIN_BUSDESCS      
    #define END_BUSDESCS          
    #define BUSDESC(x)   
	
    #define BEGIN_DEVDESCS	const U8 BusMng_au8DevCfg[BUSMNG_DEV_MAXNUM]={
    #define END_DEVDESCS		}; 
    #define DEVDESC(x,y)      {y},


   #include <BUSMNG_CFG.h>
 
#endif

/****************************** END OF FILE ***************************/

