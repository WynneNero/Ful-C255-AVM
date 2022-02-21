/***********************************************************************
*   Copyright (C) Huizhou Desay SV Automotive Co., Ltd.				   *
*				  All Rights Reserved.          					   *
*   Department : RN R&D SW1      									   *
*   AUTHOR	   : Shao Guangxian										   *
************************************************************************
* Object        :
* Module        :
* Instance      :
* Description   : Interface of IRQ module.
*-----------------------------------------------------------------------
* Version:
* Date:
* Author:
***********************************************************************/
/*-History--------------------------------------------------------------
* Version       Date    Name    Changes and comments
* ----------------------------------------------------------------------
* 0.1    Aug 01,2016 PEI Jingli      Iinitial version
* ----------------------------------------------------------------------
* 0.2    Nov 30,2016 PEI Jingli      Add interface of IRQ_IntEnableAll
* ----------------------------------------------------------------------
* 0.3    Dec 06,2016 PEI Jingli      Merge changes from REN Weimin after code review
* ----------------------------------------------------------------------
* 0.4    Dec 20,2016 ShangQiuju  remove other module used define here
*----------------------------------------------------------------------
* 0.5    Jan 24,2017  ZhangJie     Fix Coverity warning.
*=====================================================================*/

#ifndef _IRQ_IF_H_
#define _IRQ_IF_H_
#include "Define.h"   

/*ISR No. for F1L 100 pin*/
#define INTTAUD0I0 ((U16)0ul)
#define INTTAUD0I2 ((U16)1ul)
#define INTTAUD0I4 ((U16)2ul)
#define INTTAUD0I6 ((U16)3ul)
#define INTTAUD0I8 ((U16)4ul)
#define INTTAUD0I10 ((U16)5ul)
#define INTTAUD0I12 ((U16)6ul)
#define INTTAUD0I14 ((U16)7ul)
#define INTTAPA0IPEK0 ((U16)8ul)
#define INTTAPA0IVLY0 ((U16)9ul)
#define INTADCA0I0 ((U16)10ul)
#define INTADCA0I1 ((U16)11ul)
#define INTADCA0I2 ((U16)12ul)
#define INTDCUTDI ((U16)13ul)
#define INTRCANGERR ((U16)14ul)
#define INTRCANGRECC ((U16)15ul)
#define INTRCAN0ERR ((U16)16ul)
#define INTRCAN0REC ((U16)17ul)
#define INTRCAN0TRX ((U16)18ul)
#define INTCSIG0IC ((U16)19ul)
#define INTCSIG0IR ((U16)20ul)
#define INTCSIH0IC ((U16)21ul)
#define INTCSIH0IR ((U16)22ul)
#define INTCSIH0IRE ((U16)23ul)
#define INTCSIH0IJC ((U16)24ul)
#define INTRLIN30 ((U16)25ul)
#define INTRLIN30UR0 ((U16)26ul)
#define INTRLIN30UR1 ((U16)27ul)
#define INTRLIN30UR2 ((U16)28ul)
#define INTP0 ((U16)29ul)
#define INTP1 ((U16)30ul)
#define INTP2 ((U16)31ul)
#define INTWDTA0 ((U16)32ul)
#define INTWDTA1 ((U16)33ul)
#define INTP3 ((U16)34ul)
#define INTP4 ((U16)35ul)
#define INTP5 ((U16)36ul)
#define INTP10 ((U16)37ul)
#define INTP11 ((U16)38ul)
#define INTTAUD0I1 ((U16)39ul)
#define INTTAUD0I3 ((U16)40ul)
#define INTTAUD0I5 ((U16)41ul)
#define INTTAUD0I7 ((U16)42ul)
#define INTTAUD0I9 ((U16)43ul)
#define INTTAUD0I11 ((U16)44ul)
#define INTTAUD0I13 ((U16)45ul)
#define INTTAUD0I15 ((U16)46ul)
#define INTADCA0ERR ((U16)47ul)

#define INTCSIG0IRE ((U16)49ul)
#define INTRLIN20 ((U16)50ul)
#define INTRLIN21 ((U16)51ul)
#define INTDMA0 ((U16)52ul)
#define INTDMA1 ((U16)53ul)
#define INTDMA2 ((U16)54ul)
#define INTDMA3 ((U16)55ul)
#define INTDMA4 ((U16)56ul)
#define INTDMA5 ((U16)57ul)
#define INTDMA6 ((U16)58ul)
#define INTDMA7 ((U16)59ul)
#define INTDMA8 ((U16)60ul)
#define INTDMA9 ((U16)61ul)
#define INTDMA10 ((U16)62ul)
#define INTDMA11 ((U16)63ul)
#define INTDMA12 ((U16)64ul)
#define INTDMA13 ((U16)65ul)
#define INTDMA14 ((U16)66ul)
#define INTDMA15 ((U16)67ul)
#define INTRIIC0TI ((U16)68ul)
#define INTRIIC0TEI ((U16)69ul)
#define INTRIIC0RI ((U16)70ul)
#define INTRIIC0EE ((U16)71ul)
#define INTTAUJ0I0 ((U16)72ul)
#define INTTAUJ0I1 ((U16)73ul)
#define INTTAUJ0I2 ((U16)74ul)
#define INTTAUJ0I3 ((U16)75ul)
#define INTOSTM0 ((U16)76ul)
#define INTENCA0IOV_PWGA4 ((U16)77ul)
#define INTENCA0IUD_PWGA5 ((U16)78ul)
#define INTENCA0I0_PWGA6 ((U16)79ul)
#define INTENCA0I1_PWGA7 ((U16)80ul)
#define INTENCA0IEC ((U16)81ul)
#define INTKR0 ((U16)82ul)
#define INTQFULL ((U16)83ul)
#define INTPWGA0 ((U16)84ul)
#define INTPWGA1 ((U16)85ul)
#define INTPWGA2 ((U16)86ul)
#define INTPWGA3 ((U16)87ul)
#define INTPWGA8 ((U16)88ul)
#define INTPWGA9 ((U16)89ul)
#define INTPWGA10 ((U16)90ul)
#define INTPWGA11 ((U16)91ul)
#define INTPWGA12 ((U16)92ul)
#define INTPWGA13 ((U16)93ul)
#define INTPWGA14 ((U16)94ul)
#define INTPWGA15 ((U16)95ul)

#define INTFLERR ((U16)102ul)
#define INTFLENDNM ((U16)103ul)
#define INTCWEND ((U16)104ul)
#define INTRCAN1ERR ((U16)105ul)
#define INTRCAN1REC ((U16)106ul)
#define INTRCAN1TRX ((U16)107ul)
#define INTCSIH1IC ((U16)108ul)
#define INTCSIH1IR ((U16)109ul)
#define INTCSIH1IRE ((U16)110ul)
#define INTCSIH1IJC ((U16)111ul)
#define INTRLIN31 ((U16)112ul)
#define INTRLIN31UR0 ((U16)113ul)
#define INTRLIN31UR1 ((U16)114ul)
#define INTRLIN31UR2 ((U16)115ul)
#define INTPWGA20 ((U16)116ul)
#define INTPWGA21 ((U16)117ul)
#define INTPWGA22 ((U16)118ul)
#define INTPWGA23 ((U16)119ul)
#define INTP6 ((U16)120ul)
#define INTP7 ((U16)121ul)
#define INTP8 ((U16)122ul)
#define INTP12 ((U16)123ul)
#define INTCSIH2IC ((U16)124ul)
#define INTCSIH2IR ((U16)125ul)
#define INTCSIH2IRE ((U16)126ul)
#define INTCSIH2IJC ((U16)127ul)

#define INTTAUB0I0 ((U16)134ul)
#define INTTAUB0I1 ((U16)135ul)
#define INTTAUB0I2 ((U16)136ul)
#define INTTAUB0I3_PWGA16 ((U16)137ul)
#define INTTAUB0I4 ((U16)138ul)
#define INTTAUB0I5_PWGA17 ((U16)139ul)
#define INTTAUB0I6 ((U16)140ul)
#define INTTAUB0I7_PWGA18 ((U16)141ul)
#define INTTAUB0I8 ((U16)142ul)
#define INTTAUB0I9_PWGA19 ((U16)143ul)
#define INTTAUB0I10 ((U16)144ul)
#define INTTAUB0I11_PWGA26 ((U16)145ul)
#define INTTAUB0I12 ((U16)146ul)
#define INTTAUB0I13_PWGA30 ((U16)147ul)
#define INTTAUB0I14 ((U16)148ul)
#define INTTAUB0I15_PWGA31 ((U16)149ul)
#define INTCSIH3IC ((U16)150ul)
#define INTCSIH3IR ((U16)151ul)
#define INTCSIH3IRE ((U16)152ul)
#define INTCSIH3IJC ((U16)153ul)
#define INTRLIN22 ((U16)154ul)

#define INTRLIN32 ((U16)156ul)
#define INTRLIN32UR0 ((U16)157ul)
#define INTRLIN32UR1 ((U16)158ul)
#define INTRLIN32UR2 ((U16)159ul)
#define INTTAUJ1I0 ((U16)160ul)
#define INTTAUJ1I1 ((U16)161ul)
#define INTTAUJ1I2 ((U16)162ul)
#define INTTAUJ1I3 ((U16)163ul)

#define INTPWGA24 ((U16)176ul)
#define INTPWGA25 ((U16)177ul)
#define INTPWGA27 ((U16)178ul)
#define INTPWGA28 ((U16)179ul)
#define INTPWGA29 ((U16)180ul)
#define INTPWGA32 ((U16)181ul)
#define INTPWGA33 ((U16)182ul)
#define INTPWGA34 ((U16)183ul)
#define INTPWGA35 ((U16)184ul)
#define INTPWGA36 ((U16)185ul)
#define INTPWGA37 ((U16)186ul)
#define INTPWGA38 ((U16)187ul)
#define INTPWGA39 ((U16)188ul)
#define INTPWGA40 ((U16)189ul)
#define INTPWGA41 ((U16)190ul)
#define INTPWGA42 ((U16)191ul)
#define INTPWGA43 ((U16)192ul)
#define INTPWGA44 ((U16)193ul)
#define INTPWGA45 ((U16)194ul)
#define INTPWGA46 ((U16)195ul)
#define INTPWGA47 ((U16)196ul)
#if ( MCU_PIN > PIN100 )
#define INTP9 ((U16)197ul)
#endif
#define INTP13 ((U16)198ul)
#if ( MCU_PIN > PIN100 )
#define INTP14 ((U16)199ul)
#define INTP15 ((U16)200ul)
#endif

#define Reserved ((U16)208ul)
#define INTRCAN2ERR ((U16)209ul)
#define INTRCAN2REC ((U16)210ul)
#define INTRCAN2TRX ((U16)211ul)

#define INTRLIN33 ((U16)220ul)
#define INTRLIN33UR0 ((U16)221ul)
#define INTRLIN33UR1 ((U16)222ul)
#define INTRLIN33UR2 ((U16)223ul)

#define IRQ_INT_ID_MAX       (INTRLIN33UR2+1ul)

extern void IRQ_Init_Setup (void);
extern void IRQ_IntClr           (U16     int_id);
extern void IRQ_IntDis           (U16     int_id);
extern void IRQ_IntEn            (U16     int_id);
extern void IRQ_IntDisAll        (void);
extern void  IRQ_IntEnableAll (void);
extern void  IRQ_IntClrAll        (void);

#endif
/****************************** END OF FILE ***************************/
