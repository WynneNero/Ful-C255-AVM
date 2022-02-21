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
* 0.1          Jun 11,2016             Init version.
*------------------------------------------------------------------------
* 0.2          Aug 31,2016            Add string API 
*------------------------------------------------------------------------
* 0.3          Jan 11,2017  ZhangJie  Add u for constant value to avoid Coverity warnings.
*-----------------------------------------------------------------------
* 0.4          Jan 24,2017   ZhangJie   Remove unused include file.
*=====================================================================*/


/**** System include files ****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*---Public include files---------------------------------------------*/

/*---Private include files--------------------------------------------*/
#include "Tools.h"   


/*===VARIABLES========================================================*/

/*---Global-----------------------------------------------------------*/

/*---Private----------------------------------------------------------*/
#define HIGH_MASK			0xF0u
#define LOW_MASK			0x0Fu
#define BCD_OFFSET			0x04u


/*===FUNCTIONS========================================================*/

/*---Global-----------------------------------------------------------*/

/***********************************************************************
*  Name        : get_ram_bitband
*  Description : get mcu_ram_bitband address
*  Parameter   : U8 *a  the address of the variable
*  Returns     : None
***********************************************************************/
RAM_BIT_BAND_TYPE* get_ram_bitband( U8 *a )
{
    return( RAM_BIT_BAND_TYPE* )( 0x22000000u + ( ( int )a - 0x20000000u ) * 32u );
}  


U8 get_the_maximum(U8 *src,U8 size)
{
    U8 i=0u;
    U8 max = (U8)src[0];
    for(i=1u;i<size;i++)
    {
       if(max <src[i])
       {
           max = src[i];
       }
    }
    return max;
}


U8 get_the_minimum(U8 *src,U8 size)
{
    U32 i=0u;
    U8 min = src[0];
    for(i=1u;i<size;i++)
    {
       if(min >src[i])
       {
           min = src[i];
       }
    }
    return min;
}

/***********************************************************************
*  Name        : get_size_of_string
*  Description : get size of string.
*  Parameter   : src   - string address
*  Returns     : size of string.
***********************************************************************/
U8 get_size_of_string(const U8 * src)
{
    U8 size = 0u;
    while(*src != 0u)
    {
        size ++;
        src ++;
    }
    return size;
}


BOOL  is_same_in_array(U8 * array,U8 size)
{
    U8 index;
	for(index = size -1u ;index>0u ;index--)
	{
		if(array[index] != array[index -1u] )
		{
			return FALSE;
		}
	}
	return TRUE;
}

/***********************************************************************
*  Name        : is_same_arrays
*  Description : compare the data in two buffers.
*  Parameter   : src   - string address
*  Returns     : if all are same, return TRUE, else return FALSE.
***********************************************************************/
BOOL is_same_arrays(U8* dest, U8* src, U16 len)
{
 U16 i=0u;
 BOOL ret = TRUE;

  for(;i<len;i++)
  {
    	if(*dest != *src)
    	{
    		ret = FALSE;
    		break;
	}
    dest++;
    src++;
  }

  return ret;
}

void _memcpy(U8* dest, U8* src, U16 len)
{
    U16 i=0u;

    if((NULL!=dest)&&(NULL!=src))
    {
        for(; i<len; i++)
        {
            *dest=*src;
            dest++;
            src++;
        }
    }
}

void _memset(U8* dest, U8 value, U16 len)
{
    U16 i=0u;

    if(NULL!=dest)
    {
        for(; i<len; i++)
        {
            *dest=value;
            dest++;
        }
    }

}

void _strcpy(char* dest, const char* src)
{
    /*U16 i=0;*/
    U16 len =0u;

    if((NULL!= dest)&&(NULL!=src))
    {
        len = _strlen(src);
        _memcpy((U8*)dest,(U8*)src,len);
        /*below line must be added to ensure ending char exist*/
        *(dest+len)=0u;
    }

}

extern char* _strncpy(char*  s1 , const char* s2, U16 n)
{
    U16 len = 0u;

    if((NULL!=s1)&&(NULL!=s2))
    {
        len =     _strlen(s2);
        if(len>n)
            len=n;

        _memcpy((U8*)s1,(U8*)s2,len);

        /*below line must be added to ensure ending char exist*/
        *(s1+len)=0u;
    }


    return s1;
}


U16 _strlen(const char* dest)
{
    U16 len=0u;

    if(NULL!= dest)
    {
        while(*(dest+len))
        {
            len++;
            if(len>0xFFFEu)
            {
                len=0u;
                break;
            }
        }
    }

    return len;

}

extern U16 _memcmp(const void* s1, const void* s2, U16 n)
/*extern _ARMABI int memcmp(const void * s1, const void * s2, size_t n) __attribute__((__nonnull__(1,2)))*/
{
    return (U16)memcmp(s1,s2,n);
}

extern char* _strstr(const char* s1, const char* s2)
{
    return strstr(s1,s2);
}

extern U16 _strcmp(const char* s1, const char* s2)
{
    return (U16)strcmp(s1,s2);
}

U16 _strcspn(const char* s1,const char* s2)
{
    return (U16)strcspn(s1,s2);
}

U16 _strncmp(char* str1, char* str2, U16 maxlen)
{
    return (U16)strncmp(str1, str2, maxlen);
}

U16 _atoi(char* str)
{
    return (U16)atoi(str);
}

void csprintf(char* dest, char* format, U8 src)
{
	sprintf(dest, "*%02X", src);
}

void _ssprintf(char* dest, char* format, U8 src)
{
    sprintf(dest, (const char*)format, src);
}


U8 NumToASC(U8 data)
{
	U8 ret;
	/*if((data>=MIN_NUM) && (data<=MAX_NUM))*/
	if(data<=MAX_NUM)
		ret = data + NUM_BASE;
	else
		ret =  (data-MIN_ALBA)+ ALBA_BASE;

	return ret;
}

U8 ASCToNum(U8 data)
{
	U8 ret;
	if((data>=(MIN_NUM+NUM_BASE)) && (data <= (MAX_NUM+NUM_BASE)))
		ret = data - NUM_BASE;
	else
		ret =  (data- ALBA_BASE)+MIN_ALBA;

	return ret;
}

void BCD_Encode(U8 *src, U8 len, U8* tar)
{
	U8 i, temp;
	if((src == NULL) || (len == 0u))
		return;
	

	for(i=0u; i<len; i++)
	{
		temp = (src[i]&HIGH_MASK)>>BCD_OFFSET;
		tar[i*2u]= NumToASC(temp);
		
		temp = src[i]&LOW_MASK;
		tar[i*2+1u] = NumToASC(temp);
	}	
}

void BCD_Decode(U8 *src, U8 len, U8 *tar)
{
	U8 i, temp;
	if((src == NULL) || (len == 0))
		return;

	for(i=0u; i<len; i=i+2u)
	{
		temp = ASCToNum(src[i]);
		tar[i/2u] = temp<<BCD_OFFSET;		

		temp = ASCToNum(src[i+1u]);
		tar[i/2u] += temp;		
	}	

}

/***********************************************************************
*  Name        : type_conv_hex_to_ascii
*  Description : change hex code to ascii code        
*  Parameter   : U8 hex
*  Returns     : U8 ascii
***********************************************************************/
U8 type_conv_hex_to_ascii(U8 hex)
{
    U8 ascii;

    if(hex <= 0x09)
    {
        ascii = hex + 0x30;
    }
    else
    {
        if( hex <= 0x0F && hex >= 0x0A)
        {
            ascii = hex + 0x37;
        }
        else
        {
            ascii = 0x00;  // need  modify to the wrong value
        }
    }
    return ascii;
}

/***********************************************************************
*  Name        : type_conv_byte_to_ascii
*  Description : change hex code to ascii code        
*  Parameter   : U8 hex
*  Returns     : U8 ascii
***********************************************************************/
U16 type_conv_byte_to_ascii(U8 hex,U8 * dst)
{
    U16 ascii;
	U8 H;
	U8 L;
	H = (hex & 0xF0)>>4;
	L = hex & 0x0F;
	
	H = type_conv_hex_to_ascii(H);
	L = type_conv_hex_to_ascii(L);

	dst[0] = H;
	dst[1] = L;
	ascii = (H<<4) & L ;

    return ascii;
}


/*---Private----------------------------------------------------------*/




/**************** END OF FILE *****************************************/
