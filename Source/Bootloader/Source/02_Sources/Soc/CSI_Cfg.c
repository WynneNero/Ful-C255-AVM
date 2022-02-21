/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : CT AD     									   *
*   AUTHOR	   : 									   *
************************************************************************
* Object        :
* Module        :	CSI
* Instance      :
* Description   :	Configure callbacks when a interrupt occur.
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
*
*=====================================================================*/
#include "CSI_Cfg.h"
#include "SocDriver_IF.H"

const CSI_SENT_CALLBACK csi_tx_callback[CSI_MAX]=
{
SocDriver_SentIsr,
NULL,
NULL,
NULL,
NULL
};
// callback on receive every byte
const CSI_RECEV_BYTE_CALLBACK csi_rx_byte_callback[CSI_MAX]=
{
SocDriver_ReceiveIsr,
NULL,
NULL,
NULL,
NULL
};

const CSI_RECEV_CALLBACK csi_rx_callback[CSI_MAX]=
{
NULL,
NULL,
NULL,
NULL,
NULL
};

const CSI_ERROR_CALLBACK csi_error_callback[CSI_MAX]=
{
NULL,
NULL,
NULL,
NULL,
NULL
};
