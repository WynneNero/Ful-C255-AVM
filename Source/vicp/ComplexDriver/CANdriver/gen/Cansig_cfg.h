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
 ----------------------------------------------------------------------
*  0.1 Sep 26,2016 init version.
 ----------------------------------------------------------------------
*  0.2 Jan 06,2017 ShangQiuju Add method to avoid complie fail when no send or receive signal.
*------------------------------------------------------------------------
*  0.3 Jan 24,2017  ZhangJie  Fix Coverity warnings.
*=====================================================================*/
/**** Definition of constants ****/
/**** Definition of macros ****/
/**** Declaration of constants ****/
/**** Declaration of variables ****/

/**** Declaration of functions ****/
/*TX Signal Name, Functionname, ILfunctionname*/
/*
if no send signal ,should close define of CANTXSIG_PASS_1
*/
#ifdef BEGIN_CANTXSIGDESCS
BEGIN_CANTXSIGDESCS
CANTXSIGDESC(TX_SIG_SET_ID_AVSErrorSt,AVSErrorSt,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVM_LanedepartureSt_2U,AVM_LanedepartureSt_2U,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVMOpModCntSt,AVMOpModCntSt,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVMVecColorSetSt,AVMVecColorSetSt,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVM_SideView_2U,AVM_SideView_2U,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVMGuidesSt_1U,AVMGuidesSt_1U,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVMDynGudSetSt,AVMDynGudSetSt,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVM_LandpartSt_3U,AVM_LandpartSt_3U,pDataBuf[0])
//CANTXSIGDESC(TX_SIG_SET_ID_AVM360DVCalStat,AVM360DVCalStat,pDataBuf[0])



#if 0  /*Remove those CAN signal definition for Coverity warnings,but Reserve those here as a template*/
CANTXSIGDESC(TX_SIG_SET_ID_AC_MaxAcState,AC_MaxAcState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_DefrostState,AC_DefrostState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_IntakeAirState,AC_IntakeAirState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_AqsState,AC_AqsState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_BlowerLevel,AC_BlowerLevel,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_DualState,AC_DualState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_IONIZERState,AC_IONIZERState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_AirDistributionMode,AC_AirDistributionMode,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_OnState,AC_OnState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_RearKeyLockSts,AC_RearKeyLockSts,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_LeftSetTemperature,AC_LeftSetTemperature,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_AirCleanState,AC_AirCleanState,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_RightSetTemperature,AC_RightSetTemperature,pDataBuf[0])
CANTXSIGDESC(TX_SIG_SET_ID_AC_RemoteControlSt,AC_RemoteControlSt,pDataBuf[0])
#endif
END_CANTXSIGDESCS
#undef  BEGIN_CANTXSIGDESCS
#undef  END_CANTXSIGDESCS
#undef  CANTXSIGDESC
#endif

/*
if no receive signal ,should close define of CANRXSIG_PASS_1
*/
#ifdef BEGIN_CANRXSIGDESCS
/*TX Signal Name, Functionname, ILfunctionname*/
BEGIN_CANRXSIGDESCS
CANRXSIGDESC(RX_SIG_GET_ID_VehicleSpeed,VehicleSpeed,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_VehSpdAvgDrvnV,VehSpdVd_1U,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_VehSpdAvgDrvn,VehicleSpeed_13U,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_VehSpdAvgDrvnRdV,VehSpdAvgDrvnRdV,Data8U) //
//CANRXSIGDESC(RX_SIG_GET_ID_VehSpdAvgDrvnRd,VehSpdAvgDrvnRd,Data16U)  //
//CANRXSIGDESC(RX_SIG_GET_ID_IgnKyPstn,IgnKyPstn,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_TsmGearPsnVd_1U,TsmGearPsnVd_1U,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_GearDisplay_Sts_3U,GearDisplay_Sts_3U,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_MT_ReverseGearSt_1U,MT_ReverseGearSt_1U,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_AVMEveTyp,AVMEveTyp,Data8U) //
//CANRXSIGDESC(RX_SIG_GET_ID_TouPanX,TouPanX,Data16U) //
//CANRXSIGDESC(RX_SIG_GET_ID_TouPanY,TouPanY,Data16U) //
//CANRXSIGDESC(RX_SIG_GET_ID_AVMOpModCntRq,AVMOpModCntRq,Data8U) //
//CANRXSIGDESC(RX_SIG_GET_ID_AVMVecColorStRq,AVMVecColorStRq,Data8U) //
//CANRXSIGDESC(RX_SIG_GET_ID_DVD_AVMFuncSet_2U,DVD_AVMFuncSet_2U,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_AVMDynGudStRq,AVMDynGudStRq,Data8U) //
//CANRXSIGDESC(RX_SIG_GET_ID_Set_AVM_PGS_3U,Set_AVM_PGS_3U,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_VehOdoV,VehOdoV,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_VehOdo,VehOdo,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_EngSpd,EngSpd,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_LftTrnLmpAtv,LftTrnLmpAtv,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_RtTrnLmpAtv,RtTrnLmpAtv,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_StrWhAng,StrWhAng,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_StrWhAngV,StrWhAngV,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_TrnsRvsSwSt,TrnsRvsSwSt,Data16U)
//CANRXSIGDESC(RX_SIG_GET_ID_LFDistance,LFDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_RFDistance,RFDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_LRDistance,LRDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_LMRDistance,LMRDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_RMRDistance,RMRDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_RRDistance,RRDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_LMFDistance,LMFDistance,Data8U)
//CANRXSIGDESC(RX_SIG_GET_ID_RMFDistance,RMFDistance,Data8U)


#if 0  /*Remove those CAN signal definition for Coverity warnings,but Reserve those here as a template*/
CANRXSIGDESC(RX_SIG_GET_ID_PEPS_PowerMode,PEPS_PowerMode,Data8U)
CANRXSIGDESC(RX_SIG_GET_ID_PEPS_RemoteControlSt,PEPS_RemoteControlSt,Data8U)
CANRXSIGDESC(RX_SIG_GET_ID_ESC_VehicleSpeed,ESC_VehicleSpeed,Data16U)
CANRXSIGDESC(RX_SIG_GET_ID_ESC_VehicleSpeedInvalid,ESC_VehicleSpeedInvalid,Data8U)
#endif
END_CANRXSIGDESCS
#undef  BEGIN_CANRXSIGDESCS
#undef  END_CANRXSIGDESCS
#undef  CANRXSIGDESC
#undef  CANRXSIGDESC_B
#undef  CANRXSIGDESC_TO
#endif
/****************************** END OF FILE ***************************/

