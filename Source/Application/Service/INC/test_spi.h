/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.                *
*                 All Rights Reserved.                                 *
*   Department : CT AD                                         *
*   AUTHOR     :                                       *
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
#ifndef _SOC_TEST_H_
#define _SOC_TEST_H_



enum SPI_TEST_QUERY
{
   TEST_SPI_RECEIVE_EVENT = 0x0201,
   TEST_SPI_SEND_EVENT = 0x0301, 
};

/**** Declaration of functions ****/

extern void Soc_SendReceive_Test(U8 cmpt_id,U16 commandid, U8* data, U16 LEN);

#endif /*_SOC_SERVICE_H_*/

/****************************** END OF FILE ***************************/

