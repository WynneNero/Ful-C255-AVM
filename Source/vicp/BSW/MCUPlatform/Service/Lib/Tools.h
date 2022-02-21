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
*------------------------------------------------------------------------
* 0.1          Jun 11,2016                Init version.
*------------------------------------------------------------------------
* 0.2          Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warning.
*-----------------------------------------------------------------------
* 0.3          Jan 17,2017   ZhangJie   Remove unused include file.
*=====================================================================*/
#ifndef _TOOLS_H_
#define _TOOLS_H_
#include "Define.h"

/**** Definition of constants ****/

/**** Definition of types ****/ 
typedef struct
{
    U32 bit[8];
} RAM_BIT_BAND_TYPE;


/**** Definition of macros ****/
#define  BITBAND(addr,  bitnum)  (((addr)  &  0xF0000000u)+0x2000000u+(((addr)  & 0xFFFFFu)<<5)+((bitnum)<<2)) 
#define  MEM_ADDR(addr) *((volatile U16 *) (addr))

#define MIN_NUM			0x00u
#define MAX_NUM			0x09u
#define MIN_ALBA		0x0Au
#define MAX_ALBA		0x0Fu

#define NUM_BASE	0x30u
#define ALBA_BASE	0x41u


/**** Definition of types ****/ 


/**** Definition of macros ****/


/**** Declaration of constants ****/


/**** Declaration of variables ****/


/**** Declaration of functions ****/
extern RAM_BIT_BAND_TYPE* get_ram_bitband( U8 *a );
extern U8 get_the_maximum(U8 *src,U8 size);
extern U8 get_the_minimum(U8 *src,U8 size);
extern U8 get_size_of_string(const U8 * src);
extern BOOL  is_same_in_array(U8 * array,U8 size);
extern U8 NumToASC(U8 data);
extern U8 ASCToNum(U8 data);
extern void BCD_Encode(U8 *src, U8 len, U8* tar);
extern void BCD_Decode(U8 *src, U8 len, U8 *tar);
extern void _memcpy(U8* dest, U8* src, U16 len);
extern void _memset(U8* dest, U8 value, U16 len);
extern U16 _memcmp(const void* s1, const void* s2, U16 n);
extern char* _strstr(const char* s1, const char* s2);
extern U16 _strcmp(const char* s1, const char* s2);
extern U16 _strcspn(const char* s1,const char* s2);
extern U16 _strncmp(char* str1, char* str2, U16 maxlen);
extern U16 _memcmp(const void* s1, const void* s2, U16 n);
extern char* _strstr(const char* s1, const char* s2) ;
extern U16 _strcmp(const char* s1, const char* s2);
extern char* _strncpy(char*  s1 , const char* s2, U16 n);
extern void _strcpy(char* dest,const char* src);
extern U16 _strlen(const char* dest);
extern U16 _atoi(char* str);
extern void csprintf(char *dest, char *format, U8 src);
extern BOOL is_same_arrays(U8* dest, U8* src, U16 len);
extern void Lib_RunContainer( Func_Void_Proc *ContainerArray);
extern void Lib_RunParamContainer( Func_Param16_Proc *ContainerArray, U16 param);
extern void _ssprintf(char* dest, char* format, U8 src);
extern U16 type_conv_byte_to_ascii(U8 hex,U8 * dst);

#endif /*_TOOLS_H_*/

/****************************** END OF FILE ***************************/

