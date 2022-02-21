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
* ----------------------------------------------------------------------
* 0.3    Jan 06,2017    ShangQiuju    add size of data type len 
*------------------------------------------------------------------------
* 0.4    Jan 13,2017  ZhangJie  Fix Coverity warning.
 ----------------------------------------------------------------------
* 0.5    Jan 16,2017    RenWeimin    Add enum type for test code.
*----------------------------------------------------------------------
* 0.6    Jan 24,2017    ZhangJie     Fix Coverity warning phase2.
*----------------------------------------------------------------------
* 0.7    Feb 08,2017    PEI Jingli     Fix defination errors of S64 and U64
*----------------------------------------------------------------------
* 0.8    Apr 01,2017    PEI Jingli     Fix defination BIT_FIELD
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
typedef long long       S64;
typedef unsigned long long  U64;
typedef unsigned char   BIT;
typedef unsigned char   BOOL;

typedef  volatile  U8  UREG08;                       /*  8-bit register                                      */
typedef  volatile  U16 UREG16;                       /* 16-bit register                                      */
typedef  volatile  U32  UREG32;                       /* 32-bit register                                      */
typedef  volatile  U64  UREG64;                       /* 64-bit register                                      */

#ifndef NULL
#define NULL          ((void*)0)
#endif

typedef void( *Func_Void_Proc)( void );
typedef void( *Func_Param8_Proc)(U8 param);
typedef void( *Func_Param16_Proc)(U16 param);
typedef void( *Func_Param32_Proc)(U32 param);
typedef void( *Func_Param64_Proc)(U64 param);
typedef void( *Func_ParamP_Proc)(void* param);
typedef void (*IOCALLBACK_FUNC)(U8 evetype, U16 param);

#ifndef VOLATILE
#define VOLATILE volatile
#endif 

#ifndef STATIC
#define STATIC static
#endif

/**** Definition of macros ****/
#ifndef TRUE
#define TRUE         ((BOOL)1)
#endif

#ifndef FALSE
#define FALSE        ((BOOL)0)
#endif

#define STD_ON 0x01u
#define STD_OFF 0x00u

#define SIZE_OF_U8 0x01u
#define SIZE_OF_U16 0x02u

typedef struct
{  unsigned char	btf0:1;			/* MSB			*/
   unsigned char	btf1:1;
   unsigned char	btf2:1;
   unsigned char	btf3:1;
   unsigned char	btf4:1;
   unsigned char	btf5:1;
   unsigned char	btf6:1;
   unsigned char	btf7:1;			/* LSB			*/	
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
	ERR_SPEED,                     /* This device does not work in the active speed mode. */
	ERR_RANGE,                     /* Parameter out of range. */
	ERR_VALUE ,                    /* Parameter of incorrect value. */
	ERR_OVERFLOW,                  /* Timer overflow. */
	ERR_MATH ,                     /* Overflow during evaluation. */
	ERR_ENABLED ,                  /* Device is enabled. */
	ERR_DISABLED ,                 /* Device is disabled. */
	ERR_BUSY ,                     /* Device is busy. */
	ERR_NOTAVAIL,                  /* Requested value or method not available. */
	ERR_RXEMPTY,                  /* No data in receiver. */
	ERR_TXFULL,                   /* Transmitter is full. */
	ERR_BUSOFF,                  /* Bus not available. */
	ERR_OVERRUN ,                 /* Overrun error is detected. */
	ERR_FRAMING ,                 /* Framing error is detected. */
	ERR_PARITY ,                  /* Parity error is detected. */
	ERR_NOISE ,                   /* Noise error is detected. */
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
	ERR_SEVICE_NOT_READY,
	ERR_IIC_SLAVE_NOACK,	
} ERR_TYPE;

 enum
{
    E_NEGATIVE_BAD_REQUEST=0x0,		/* bad request or handle fail, no data is sent back*/
    E_POSITIVE=0x01,
    E_NOT_SENT_RESULT = 0xff,
};

typedef enum
{
    E_NACK,
    E_ACK,
    E_NULL,
} E_DATASEND_RESP;

 
#endif /*_DEFINE_H_*/

/****************************** END OF FILE ***************************/

