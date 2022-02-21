/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file of a crc algorithm, this algorithm is used
 *              by BZIP2.
 *
 *  \file       bl_crc32_bzip2.c
 *  \ingroup    security_manager_module
 *  \author     mingqing.tang <mingqing.tang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 25/03/2010 | hewei.zhang      | N/A | Boot010001
 *      02.00.00 | 18/05/2011 | mingqing.tang    | N/A | Boot020001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_security_funcfg.h"
#include "bl_crc32_bzip2.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 506,602,1252,1532,2100,2103,3212,3227 EOF*/
/*
 * 506:Dereferencing pointer value that is possibly NULL.
 * The parameter delay is not a null pointer.
 *
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * 1252:suffixed integer constant implicitly converted to different integer.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 2100:Integral promotion : unsigned char promoted to signed int.
 *
 * 2103:Integral promotion, unsigned short promoted to unsigned int.
 * This message will therefore only be generated when a short and an int are of
 * equal size.
 *
 * 3212:This explicit cast is redundant and could be removed.
 * BL_BE32_TO_MCU is not explicit cast.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/
#if ((SECM_CRC_WIDTH != 32u) || (SECM_CRC_VALUE_SIZE != 4u))
#error "This crc algorithm is not used for current security manager module."
#endif

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#define BZIP2_CRC_SIZE_OPIMITE_MASK (0x0Fu)
#define BZIP2_CRC_SHIFT_BITS        (SECM_CRC_WIDTH - BZIP2_CALCULATED_WIDTH)

#define BZIP2_INIT_CRC_TABLE_MASK   (0x80000000UL)
#define BZIP2_INIT_CRC_TABLE_SHIFT  (24UL)
#define BZIP2_INIT_CRC_TABLE_BITS   (8UL)

#if (SECM_CRC_OPIMITE_BY_SIZE == BL_FUN_ON)
#define BZIP2_TABLE_SIZE            (16UL)
#define BZIP2_CALCULATED_WIDTH      (4UL)
#else
#define BZIP2_TABLE_SIZE            (256u)
#define BZIP2_CALCULATED_WIDTH      (8u)
#endif
const bl_u8_t Rflct_tab[16]=
                            {0x00,0x08,0x04,0x0c,
                             0x02,0x0a,0x06,0x0e,
                             0x01,0x09,0x05,0x0d,
                             0x03,0x0b,0x07,0x0f}; 

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
static void _Bzip2_InitTable(void);
static bl_u8_t _8bit_rev(bl_u8_t data);                               

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
static bl_u32_t gs_bzip2CrcRemainder;
static bl_u32_t gs_bzip2CrcTable[BZIP2_TABLE_SIZE];
/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the bzip2 crc32 algorithm.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Bzip2_Init(void)
{
    _Bzip2_InitTable();
}

/**************************************************************************//**
 *
 *  \details Start the bzip2 crc32 algorithm.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Bzip2_Start(void)
{
    gs_bzip2CrcRemainder = CRC32_BZIP2_INIT_VALUE;
}

/**************************************************************************//**
 *
 *  \details Update the crc value.
 *
 *  \param[in]  size - the size of data.
 *  \param[in]  data - the value of data.
 *
 *  \return If the crc value is calculated successfully return BL_ERR_OK,
 *          otherwise crc value BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the crc value is calculated successfully.
 *  \retval BL_ERR_NOT_OK - the crc value is not calculated successfully.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Bzip2_Update(bl_Size_t size, const bl_Buffer_t *data)
{

//    bl_Buffer_t tmp;
//    bl_Size_t i;
//    bl_u32_t crc = gs_bzip2CrcRemainder;
//    bl_u8_t ldata;
//    for (i = 0; i < size; i++)
//    {

//        ldata = _8bit_rev(data[i]);
//        /*tmp = (bl_Buffer_t)((crc >> BZIP2_CRC_SHIFT_BITS) ^ data[i]);*/
//        tmp = (bl_Buffer_t)((crc >> BZIP2_CRC_SHIFT_BITS) ^ ldata);

//        crc = (crc << BZIP2_CALCULATED_WIDTH) ^ gs_bzip2CrcTable[tmp];

//    }

//    gs_bzip2CrcRemainder = crc;

//    return BL_ERR_OK;

    bl_Buffer_t tmp;
    bl_Size_t i;
    bl_u32_t crc = gs_bzip2CrcRemainder;
    bl_u8_t ldata;
    for (i = 0; i < size; i++)
    {
#if (SECM_CRC_OPIMITE_BY_SIZE == BL_FUN_ON)
        tmp = (bl_Buffer_t)((crc >> BZIP2_CRC_SHIFT_BITS)
                            ^ ((data[i] >> BZIP2_CALCULATED_WIDTH)
                            & BZIP2_CRC_SIZE_OPIMITE_MASK));
#else
        ldata = _8bit_rev(data[i]);
        /*tmp = (bl_Buffer_t)((crc >> BZIP2_CRC_SHIFT_BITS) ^ data[i]);*/
        tmp = (bl_Buffer_t)((crc >> BZIP2_CRC_SHIFT_BITS) ^ ldata);
        
#endif

        crc = (crc << BZIP2_CALCULATED_WIDTH) ^ gs_bzip2CrcTable[tmp];

#if (SECM_CRC_OPIMITE_BY_SIZE == BL_FUN_ON)
        tmp = (bl_Buffer_t)((crc >> BZIP2_CRC_SHIFT_BITS)
                            ^ (data[i] & BZIP2_CRC_SIZE_OPIMITE_MASK));
        crc = (crc << BZIP2_CALCULATED_WIDTH) ^ gs_bzip2CrcTable[tmp];
#endif
    }

    gs_bzip2CrcRemainder = crc;

    return BL_ERR_OK;
}

/**************************************************************************//**
 *
 *  \details The algorithm to calculate the crc value.
 *
 *  \param[in]  size - the size of data.
 *  \param[in]  data - the value of data.
 *
 *  \return If the crc value is right return BL_ERR_OK, otherwise return
 *          BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the crc value is right.
 *  \retval BL_ERR_NOT_OK - the crc value is NOT right.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Bzip2_Verify(bl_Size_t size, const bl_Buffer_t *hash)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_u32_t crc;
    bl_u32_t tranCrc;
    bl_u8_t lcrcS[4];
    bl_u8_t lcrcD[4];
    bl_u8_t i;
    
    if (SECM_CRC_VALUE_SIZE == size)
    {
        /* Finish the crc algorithm.*/
        crc = gs_bzip2CrcRemainder ^ CRC32_BZIP2_FINAL_XOR_VALUE;
        BL_MCU_TO_BE32(lcrcS,crc);
        
        for(i = 0u;i < 4u;i++)
        {
            lcrcD[i] = _8bit_rev(lcrcS[3 - i]);
        }
        crc = BL_BE32_TO_MCU(lcrcD);
        /* Verify the crc value.*/
        tranCrc = BL_BE32_TO_MCU(hash);

        if (tranCrc == crc)
        {
            ret = BL_ERR_OK;
        }
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details Initialize the crc table of the bzip2 algorithm.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/
static void _Bzip2_InitTable(void)
{
//	bl_u32_t remainder;
//	bl_u32_t dividend;
//	bl_u8_t  bit;

	/* Compute the remainder of each possible dividend.*/
//	for (dividend = 0; dividend < BZIP2_TABLE_SIZE; dividend++)
//	{
//		for(bit =0,gs_bzip2CrcTable[dividend] = dividend; bit < 8; bit++)
//		{
//			gs_bzip2CrcTable[dividend] = (gs_bzip2CrcTable[dividend] >> 1)^((gs_bzip2CrcTable[dividend]&1)?CRC32_BZIP2_POLYNOMIAL : 0);
//		}
//	}
//	return ;

    bl_u32_t remainder;
    bl_u32_t dividend;
    bl_u8_t  bit;

    /* Compute the remainder of each possible dividend.*/
    for (dividend = 0; dividend < BZIP2_TABLE_SIZE; dividend++)
    {
        /* Start with the dividend followed by zeros.*/
        remainder = dividend << BZIP2_INIT_CRC_TABLE_SHIFT;

        /* Perform modulo-2 division, a bit at a time.*/
        for (bit = (bl_u8_t)BZIP2_INIT_CRC_TABLE_BITS; bit > 0; --bit)
        {
            /* Try to divide the current data bit.*/
            if ((remainder & BZIP2_INIT_CRC_TABLE_MASK) != 0UL)
            {
                remainder = (remainder << 1) ^ CRC32_BZIP2_POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        /* Store the result into the table.*/
        gs_bzip2CrcTable[dividend] = remainder;
    }

    return ;
}

/**************************************************************************//**
 *
 *  \details Initialize the crc table of the bzip2 algorithm.
 *
 *  \since  V2.0.0
 *
 *****************************************************************************/ 
static bl_u8_t _8bit_rev(bl_u8_t data)  
{ 
    bl_u8_t ret;
    ret = (Rflct_tab[(data & 0x0f)] << 4) | (Rflct_tab[(data >> 4)]);
    return ret;
}  
