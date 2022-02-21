/**************************************************************************//**
 *
 *  \copyright  This software is the property of HiRain Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              HiRain Technologies.
 *
 *  \brief      This is a source file to make seed and verify a key.
 *
 *  \file       bl_access_udsdemo.c
 *  \ingroup    security_manager_module
 *  \author     xin.shang <xin.shang@hirain.com>
 *
 *  \version    5.1.0
 *  \date       27/03/2014
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      -------- | ---------- | ---------------- | --- | ------------
 *      01.00.00 | 25/03/2010 | hewei.zhang      | N/A | Boot010001
 *      01.01.00 | 19/05/2010 | hewei.zhang      | N/A | Boot010002
 *      05.00.00 | 19/06/2013 | xin.shang        | N/A | Boot050001
 *      05.01.00 | 27/03/2014 | mingqing.tang    | N/A | Boot050002
 *
 *****************************************************************************/
#include "bl_common.h"
#include "bl_security_funcfg.h"
#include "bl_access_udsdemo.h"

/*****************************************************************************
 *  QAC Suppression
 *****************************************************************************/
/*PRQA S 602,1532,3212,3227,3453 EOF*/
/*
 * MISRA-C:2004 20.2(602):The identifier is reserved for use by the library.
 * The Bootloader do not use any library funtion and use the underscores to
 * indicate that the function is a interal function.
 *
 * 1532:The function is only referenced in one translation unit.
 * all functions in this file are configurations in the Security Module.
 *
 * 3212:This explicit cast is redundant and could be removed.
 * ACC_UDSDEMO_KEY_FROM_BUF and ACC_UDSDEMO_SEED_TO_BUF are not explicit cast.
 *
 * 3227:The parameter is never modified and so it could be declared with const.
 * Acc_UdsDemoGetSeed, the seed will be modify.
 * Acc_UdsDemoVerifyKey, the key is declared with const.
 *
 * MISRA-C:2004 19.7(3453):A function could probably be used instead of this
 * function-like macro.
 * ACC_UDSDEMO_KEY_FROM_BUF macro do not have side-effect.
 * ACC_UDSDEMO_SEED_TO_BUF macro do not have side-effect.
 *
 */

/*****************************************************************************
 *  Verify The Configurations of Macro
 *****************************************************************************/
#if ((SECM_ACCESS_KEY_SIZE != 4u) && (SECM_ACCESS_KEY_SIZE != 2u))
#error "The size of a key is only four or two, other values are invalid."
#endif

#if ((SECM_ACCESS_SEED_SIZE != 4u) && (SECM_ACCESS_SEED_SIZE != 2u))
#error "The size of a seed is only four or two, other values are invalid."
#endif
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/
#if (SECM_ACCESS_KEY_SIZE == 4u)
#define ACC_UDSDEMO_KEY_MASK                (0x42313532UL)
#define ACC_UDSDEMO_KEY_FROM_BUF(buf)       BL_BE32_TO_MCU(buf)
#define ACC_UDSDEMO_SEED_MASK               (0x80000000UL)
#define ACC_UDSDEMO_UNLOCKKEY               (0x00000000UL)
#define ACC_UDSDEMO_UNLOCKSEED              (0x00000000UL)
#define ACC_UDSDEMO_UNDEFINESEED            (0xFFFFFFFFUL)
#elif (SECM_ACCESS_KEY_SIZE == 2u)
#define ACC_UDSDEMO_KEY_MASK                (0xDFB6u)
#define ACC_UDSDEMO_KEY_FROM_BUF(buf)       BL_BE16_TO_MCU(buf)
#endif

#if (SECM_ACCESS_SEED_SIZE == 4u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDSDEMO_RANDOM_SEED             (*(volatile bl_u32_t *)0xFFEC0004)
#define ACC_UDSDEMO_SEED_INITVALUE          (0x12350012UL)
#define ACC_UDSDEMO_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE32(buf,seed)
#elif (SECM_ACCESS_SEED_SIZE == 2u)
/** \brief It is used to calculate the random seed*/
#define ACC_UDSDEMO_RANDOM_SEED             (16807u)
#define ACC_UDSDEMO_SEED_INITVALUE          (0x1235u)
#define ACC_UDSDEMO_SEED_TO_BUF(seed,buf)   BL_MCU_TO_BE16(buf,seed)
#endif
#define  ROR_3(buf)           ((buf >> 3) | (buf << 5))

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
#if (SECM_ACCESS_SEED_SIZE == 4u)
typedef bl_u32_t bl_UdsDemoSeed_t;
#elif (SECM_ACCESS_SEED_SIZE == 2u)
typedef bl_u16_t bl_UdsDemoSeed_t;
#endif

#if (SECM_ACCESS_KEY_SIZE == 4u)
typedef bl_u32_t bl_UdsDemoKey_t;
#elif (SECM_ACCESS_KEY_SIZE == 2u)
typedef bl_u16_t bl_UdsDemoKey_t;
#endif


/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
/** \brief Calculate the key from the gs_UdsDemoSeed.*/
static bl_UdsDemoKey_t _Acc_UdsDemoCalculateKey(void);

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
static bl_UdsDemoSeed_t gs_UdsDemoSeed;

/*****************************************************************************
 *  Global Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Function Definitions
 *****************************************************************************/
/**************************************************************************//**
 *
 *  \details Initialize the DEMO security access used for UDS.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsDemoInit(void)
{
    gs_UdsDemoSeed = ACC_UDSDEMO_SEED_INITVALUE;

    return ;
}

/**************************************************************************//**
 *
 *  \details Make a new seed.
 *
 *  \since  V5.0.0
 *
 *****************************************************************************/
void Acc_UdsDemoMakeNewSeed(void)
{    
	gs_UdsDemoSeed = (((bl_UdsDemoSeed_t)ACC_UDSDEMO_RANDOM_SEED) << 16)  ;
	gs_UdsDemoSeed |= (bl_UdsDemoSeed_t)(ROR_3(ACC_UDSDEMO_RANDOM_SEED));
	if(0 == gs_UdsDemoSeed)
	{
	   gs_UdsDemoSeed = ACC_UDSDEMO_SEED_INITVALUE;
	}

	return ;
}

/**************************************************************************//**
 *
 *  \details Get current seed value.
 *
 *  \param[out]  seed - the value of current seed.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void Acc_UdsDemoGetSeed(bl_Buffer_t *seed)
{

    ACC_UDSDEMO_SEED_TO_BUF(gs_UdsDemoSeed,seed);
    
    return ;
}

/**************************************************************************//**
 *
 *  \details Verify the value of transmitted key whether is right.
 *
 *  \param[in]  key - the value of transmitted key.
 *
 *  \return If the transmitted key value is right return BL_ERR_OK, otherwise
 *          return BL_ERR_NOT_OK.
 *
 *  \retval BL_ERR_OK - the transmitted key value is right.
 *  \retval BL_ERR_NOT_OK - the transmitted key value is NOT right.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
bl_Return_t Acc_UdsDemoVerifyKey(const bl_Buffer_t *key)
{
    bl_Return_t ret = BL_ERR_NOT_OK;
    bl_UdsDemoKey_t calKey;
    bl_UdsDemoKey_t tranKey;

    calKey = _Acc_UdsDemoCalculateKey();
    tranKey = ACC_UDSDEMO_KEY_FROM_BUF(key);

    if (calKey == tranKey)
    {
        ret = BL_ERR_OK;
    }

    return ret;
}

/**************************************************************************//**
 *
 *  \details An algorithm is used to calculate the key by a seed.
 *
 *  \return the key value
 *
 *  \since V1.0.0
 *
 *****************************************************************************/
#define MASK 0x877710E9

static bl_UdsDemoKey_t _Acc_UdsDemoCalculateKey(void)
{
	unsigned int iterations ;
	unsigned int wLastSeed ;
	unsigned int wTemp ;
	unsigned int wLSBit ;
	unsigned int wTop31Bits ;
	unsigned int jj,SB1,SB2,SB3;
	unsigned int temp;
	unsigned int key = 0;  
	
	wLastSeed = gs_UdsDemoSeed;
	temp =(unsigned short)(( MASK & 0x00000800) >> 10) | ((MASK & 0x00200000)>> 21);
	if(temp == 0 )
	{
		wTemp = (unsigned int)((gs_UdsDemoSeed & 0xff000000) >> 24);
	}
	else if(temp == 1)
	{
		wTemp = (unsigned int)((gs_UdsDemoSeed & 0x00ff0000) >> 16);
	}
	else if(temp == 2)
	{
		wTemp = (unsigned int)((gs_UdsDemoSeed & 0x0000ff00) >> 8);
	}
	else
	{
		wTemp = (unsigned int)(gs_UdsDemoSeed & 0x000000ff);
	}

	SB1 = (unsigned int)(( MASK & 0x000003FC) >> 2);
	SB2 = (unsigned int)((( MASK & 0x7F800000) >> 23)^0xA5);
	SB3 = (unsigned int)((( MASK & 0x001FE000) >> 13)^0x5A);

	iterations = (unsigned int)(((wTemp ^ SB1) & SB2) + SB3 );

	for ( jj = 0; jj < iterations; jj++ )
	{
		wTemp = ((wLastSeed & 0x40000000)/0x40000000)^((wLastSeed & 0x01000000)/0x01000000)^((wLastSeed & 0x1000)/0x1000)^((wLastSeed & 0x04)/0x04) ;
		wLSBit = (wTemp & 0x00000001) ;
		wLastSeed = (unsigned int)(wLastSeed << 1); /* Left Shift the bits */
		wTop31Bits = (unsigned int)(wLastSeed & 0xFFFFFFFE) ;
		wLastSeed = (unsigned int)(wTop31Bits | wLSBit);
	}
	if (MASK & 0x00000001)
	{
		wTop31Bits = ((wLastSeed & 0x00FF0000)>>16)|((wLastSeed & 0xFF000000)>>8)|((wLastSeed & 0x000000FF)<<8)|((wLastSeed & 0x0000FF00)<<16); 
	}
	else
		wTop31Bits = wLastSeed;

	wTop31Bits = wTop31Bits ^ MASK;

	key = wTop31Bits;

	return key;
} 



