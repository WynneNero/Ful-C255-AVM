/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   :            										   *
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
* 0.1    Feb 10,2013    NI Rujin    Initial version
* ----------------------------------------------------------------------
* 0.2    Aug 01,2016    PEI Jingli    add constants defination
*=====================================================================*/
#ifndef _DEFINE_H_
#define _DEFINE_H_ 

/**** Definition of constants ****/


/**** Definition of types ****/ 

typedef signed char     S8;
typedef unsigned char   U8;
typedef short           S16;
typedef unsigned short  U16;
typedef int             S32;
typedef unsigned int    U32;
typedef long        S64;
typedef unsigned long  U64;
typedef unsigned char   BIT;
typedef unsigned char   BOOL;
typedef  unsigned  char        CPU_INT08U;                      /*  8-bit unsigned integer                              */
typedef  unsigned  short       CPU_INT16U;                      /* 16-bit unsigned integer                              */
typedef  unsigned  int         CPU_INT32U;                      /* 32-bit unsigned integer                              */
typedef  unsigned  long        CPU_INT64U;                      /* 64-bit unsigned integer                              */

typedef  CPU_INT08U volatile CPU_REG08;                       /*  8-bit register                                      */
typedef  CPU_INT16U volatile CPU_REG16;                       /* 16-bit register                                      */
typedef  CPU_INT32U volatile CPU_REG32;                       /* 32-bit register                                      */
typedef  CPU_INT64U volatile CPU_REG64;                       /* 64-bit register                                      */


typedef  volatile  U8  UREG08;                       /*  8-bit register                                      */
typedef  volatile  U16 UREG16;                       /* 16-bit register                                      */
typedef  volatile  U32  UREG32;                       /* 32-bit register                                      */
typedef  volatile  U64  UREG64;                       /* 64-bit register                                      */

#ifndef NULL
#define NULL          0u
#endif

#define  CPU_WORD_SIZE_08                          1    /*  8-bit word size (in octets).                                */
#define  CPU_WORD_SIZE_16                          2    /* 16-bit word size (in octets).                                */
#define  CPU_WORD_SIZE_32                          4    /* 32-bit word size (in octets).                                */
#define  CPU_WORD_SIZE_64                          8    /* 64-bit word size (in octets).  */

typedef void( *Func_Void_Proc)( void );
typedef void( *Func_Param8_Proc)(U8 param);
typedef void( *Func_Param16_Proc)(U16 param);
typedef void( *Func_Param32_Proc)(U32 param);
typedef void( *Func_ParamP_Proc)(void* param);
typedef void (*IOCALLBACK_FUNC)(U8 evetype, U16 param);

#ifndef VOLATILE
#define VOLATILE volatile
#endif 

#ifndef STATIC
#define STATIC static
#endif

#ifndef TRUE
#define TRUE         (BOOL)1
#endif

#ifndef FALSE
#define FALSE        (BOOL)0
#endif

#define STD_ON 0x01u
#define STD_OFF 0x00u

typedef struct
{  unsigned int	btf0:1;			/* MSB			*/
   unsigned int	btf1:1;
   unsigned int	btf2:1;
   unsigned int	btf3:1;
   unsigned int	btf4:1;
   unsigned int	btf5:1;
   unsigned int	btf6:1;
   unsigned int	btf7:1;			/* LSB			*/	
}BIT_FIELD;

/**** Declaration of constants ****/
typedef enum
{
    DISABLE = 0x00,
    ENABLE = 0x01,

} FUNCTION_STATE;

typedef enum
{
	ERR_OK ,                       /* OK */
	ERR_RANGE,                     /* Parameter out of range. */
	ERR_BUSY ,                     /* Device is busy. */
	ERR_IDLE ,                    /* Idle error is detected. */
	ERR_FAULT ,                   /* Fault error is detected. */
	ERR_BREAK ,                   /* Break char is received during communication. */
	ERR_CRC ,                     /* CRC error is detected. */
	ERR_ARBITR,                  /* A node losts arbitration. This error occurs if two nodes start transmission at the same time. */
	ERR_PROTECT ,                 /* Protection error is detected. */
	ERR_UNDERFLOW ,               /* Underflow error is detected. */
	ERR_UNDERRUN ,                /* Underrun error is detected. */
	ERR_COMMON ,                  /* Common error of a device. */
	ERR_LINSYNC,                  /* LIN synchronization error is detected. */
	ERR_FAILED ,                  /* Requested functionality or process failed. */
	ERR_INVALID_PARAMETER,        /* Incorrect parameter provided*/
	ERR_RETRY,
	ERR_SERIOUS,
	ERR_FINISHED,
	ERR_DISABLED,
	ERR_SEVICE_NOT_READY
} ERR_TYPE;

typedef enum
{
   E_DEV_POWERON,
   E_DEV_POWEROFF,   	
   E_DEV_WAKEUP,
   E_DEV_SLEEP
}E_DEV_POWER;


typedef enum
{
   E_DEV_SPOWERON,
   E_DEV_SPOWEROFF,   	
   E_DEV_SWAKEUP,
   E_DEV_SSLEEP
}E_DEV_POWERS;
 
#endif /*_DEFINE_H_*/

/****************************** END OF FILE ***************************/

