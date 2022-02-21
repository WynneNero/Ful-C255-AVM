/*===========================================================================*/
/* Module       = dr7f701023.ld                                              */
/* Version      = V1.10                                                      */
/*                extracted from device file dr7f701023.dvf                  */
/*                by DeFiXRH850 0.7.1.4                                      */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2013 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Purpose:     Template of linker directive file                            */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* Environment:                                                              */
/*              Device:         R7F701023xAFP                                */
/*              IDE:            GHS Multi for V800  V6.xx or later           */
/*---------------------------------------------------------------------------*/
/* Ver    Date           Name        Changes and comment                     */
/* --------------------------------------------------------------------------*/
/* 0.1    Jul 26,2016    LIU Chenxi  Merge with RWM codes, add bootloader    */
/*===========================================================================*/

CONSTANTS
{
  zero_start = 0xffff8000
}

MEMORY
 {
    /*flash configuration with UDS bootloader enabled*/
    iROM_BOOT : ORIGIN = 0x00000000,  LENGTH = 96K
    iROM_VECTOR: ORIGIN = 0x00018000,  LENGTH = 1k
    iROM_EIINTV: ORIGIN = 0x00018400,  LENGTH = 1k
    iROM_MYCONST: ORIGIN = 0x00018800, LENGTH = 1K
    iROM_0     : ORIGIN = 0x00018C00,  LENGTH = 285k
 
    /*flash configuration without UDS bootloader*/
    //iROM_VECTOR: ORIGIN = 0x00000000,  LENGTH = 1k	// no bl
    //iROM_EIINTV: ORIGIN = 0x00000400,  LENGTH = 1k      // no bl  
    //iROM_0     : ORIGIN = 0x00000800,  LENGTH = 382k	// no bl

  iROM_1     : ORIGIN = 0x01000000,  LENGTH = 32k		// extended user area
  iROM_1_TOP : ORIGIN = .         ,  LENGTH = 0

  //10223 only has primary RAM,16k
  iRAM_0     : ORIGIN = 0xFEDFC000,  LENGTH = 16k
  iRAM_0_TOP : ORIGIN = .         ,  LENGTH = 0
  iRAM_R     : ORIGIN = 0xFEE00000,  LENGTH = 32k+773
  iRAM_R_TOP : ORIGIN = .         ,  LENGTH = 0  
  //iRAM_BOOTLOAD_FLAG     : ORIGIN = 0xFEE07FF0,  LENGTH = 16
  //iRAM_BOOTLOAD_TOP : ORIGIN = .         ,  LENGTH = 0  
 }

SECTIONS
 {
  .R_BOOT_CODE  align(4)                  :{vicp.mem(.raw)}>iROM_BOOT   /* initialized data */ 	        
  __top_of_iROM_BOOT = MEMENDADDR( iROM_BOOT);
  
 //Start of internal ROM area (iROM_0) */
//  .intvect_reset    :>iROM_BOOT 
  .osExceptionVectorTable_c0    :>iROM_VECTOR
//    .osExceptionVectorTable_c0_end  0x200 :>
  .osEIINTVectorTable_c0    :>iROM_EIINTV
//   .osEIINTVectorTable_c0_end      0x200 :>.
  .myconst	:>iROM_MYCONST
  
  //.intvect                              :>iROM_0 /* start of interrupt vector */
  //.intvect_end  0x0580                  :>.      /* end   of interrupt vector */
  //.intvect_end  0x0D80                  :>.      /* end   of interrupt vector */
  .rozdata                              :>iROM_0       /* constant datas in ZDA area */
  .robase   align(4)                    :>.      /* initialize textpointer TP for SDA addressing */
  .rosdata  align(4)                    :>.      /* constant datas in SDA area */
  .rodata   align(4)                    :>.      /* constant datas in normal area */
  .os_rodata align(4)			:>.

  .text     align(4)                    :>.      /* program code area */
  .os_text  align(4)			:>.      // add
  //.osExceptionVectorTable_c0		:>.
  //.osEIINTVectorTable_c0		:>.
  
  .fixaddr  align(4)                    :>.      /* ghs internal (compiler) */
  .fixtype  align(4)                    :>.      /* ghs internal (compiler) */
  .secinfo  align(4)                    :>.      /* ghs internal (runtime library) */
  .syscall  align(4)                    :>.      /* ghs internal (linker) */

  .romdata  ROM(.data)                  :>.      /* constant data to initialize variables (copied to RAM at startup)*/
  .romzdata ROM(.zdata)                 :>.      /* constant data to initialize variables in ZDA area (copied to RAM at startup)*/
  .romsdata ROM(.sdata)                 :>.      /* constant data to initialize variables in SDA area (copied to RAM at startup)*/
  .romtdata ROM(.tdata)                 :>.      /* constant data to initialize variables in TDA area (copied to RAM at startup)*/
  .romrodata ROM(.os_data)	        :>.

/* Renesas FDL/EEL Program code sections */

  .R_FDL_Text    align(4)               :>.      /* FDL code in ROM */
  .R_FDL_Const   align(4)               :>.      /* FDL constants in ROM */
  .R_EEL_Text    align(4)               :>.      /* EEL code in ROM (Empty if no EEL is implemented) */
  .R_EEL_Const   align(4)               :>.      /* EEL constants in ROM (Empty if no EEL is implemented) */

/* Start of internal User-Boot-ROM area (iROM_1) */

  .bcode    align(4)             :>iROM_1     /* user defined segment for executable code located in user boot area */
  .bconst   align(4)             :>.           /* user defined segment for constant data located in user boot area   */
  .top_of_ROM_BOOT align(4)      :>iROM_1_TOP

/* Start of internal RAM area (iRAM) */

  .data                                 :>iRAM_0 /* initialized data */
 

  .sdabase  align(4)                    :>.      /* initialize globalpointer GP for SDA addressing */
  .sdata    align(4)                    :>.      /* initialized data in SDA area*/
  .sbss     align(4)                    :>.      /* zero initialized data in SDA area*/

  .zdata    align(4)                    :>.      /* initialized data in ZDA area*/
  .zbss     align(4)                    :>.      /* zero initialized data in ZDA area*/
  .os_data align(4)				:>.
  .os_bss	align(4)				:>.

  .ramtext  align(128) MAX_SIZE(0x2000) :>.      /* initialized and zero-initialized data in TDA area */
  .tdata    align(4)   MAX_SIZE(0x0100) :>.      /* initialized and zero-initialized data in TDA area */
  .exec     align(128)                  :>.  

/* Renesas FDL/EEL data sections */
  .R_FDL_Data                           :>.      /* FDL data */
  .R_FDL_CodeRam                        :>.      /* FDL code in RAM (Empty if R_FDL_EXE_INIT_CODE_ON_STACK is defined) */
  .R_EEL_Data                           :>.      /* EEL data (Empty if no EEL is implemented) */

   .osIntStackLevel0_c0  align(4)  :>.
   _osIntStackLevel0_c0_StartAddr = addr(.osIntStackLevel0_c0);
   _osIntStackLevel0_c0_EndAddr = endaddr(.osIntStackLevel0_c0);

   .osIntStackLevel1_c0  align(4)  :>.
   _osIntStackLevel1_c0_StartAddr = addr(.osIntStackLevel1_c0);
   _osIntStackLevel1_c0_EndAddr = endaddr(.osIntStackLevel1_c0);

   .osSystemStack_c0  align(4)  :>.
   _osSystemStack_c0_StartAddr = addr(.osSystemStack_c0);
   _osSystemStack_c0_EndAddr = endaddr(.osSystemStack_c0);

   .osTaskStack0  align(4)  :>.
   _osTaskStack0_StartAddr = addr(.osTaskStack0);
   _osTaskStack0_EndAddr = endaddr(.osTaskStack0);

   .osTaskStack1  align(4)  :>.
   _osTaskStack1_StartAddr = addr(.osTaskStack1);
   _osTaskStack1_EndAddr = endaddr(.osTaskStack1);

   .osTaskStack2  align(4)  :>.
   _osTaskStack2_StartAddr = addr(.osTaskStack2);
   _osTaskStack2_EndAddr = endaddr(.osTaskStack2);

   .osTaskStack3  align(4)  :>.
   _osTaskStack3_StartAddr = addr(.osTaskStack3);
   _osTaskStack3_EndAddr = endaddr(.osTaskStack3);

   .osTaskStack4  align(4)  :>.
   _osTaskStack4_StartAddr = addr(.osTaskStack4);
   _osTaskStack4_EndAddr = endaddr(.osTaskStack4);

   .osTaskStack5  align(4)  :>.
   _osTaskStack5_StartAddr = addr(.osTaskStack5);
   _osTaskStack5_EndAddr = endaddr(.osTaskStack5);

   .osTaskStack6  align(4)  :>.
   _osTaskStack6_StartAddr = addr(.osTaskStack6);
   _osTaskStack6_EndAddr = endaddr(.osTaskStack6);


  //.stack    align(4) pad(0x0800)        :>.      /* definition of stack size */

  .heapbase align(4)                    :>.
  .heap     align(4)
  	        pad(addr(iRAM_0_TOP)-addr(.heapbase))
  	        NOCLEAR	                    :>.      /* definition of heap size */ 

  .top_of_RAM align(4)                  :>iRAM_0_TOP


  
/* Start of internal retention RAM area (iRAM_R) */  //fedfea00
  .stack        align(4) pad(0x0800)    :>iRAM_R      /* definition of stack size */
  .rdata        align(4)                :>.           /* user defined segment for for initialized data located in retention RAM  */ 
  .rbss         align(4)                :>.           /* user defined segment for zero initialized data located in retention RAM */
   .bss      align(4)                    :>.      /* zero initialized data*/
  .top_of_RAM_R align(4)                :>iRAM_R_TOP

 // .bootload_flagdata align(4)         :>iRAM_BOOTLOAD_FLAG
 //.bootload_flagdata       :>iRAM_BOOTLOAD_FLAG
 // .top_of_bootload align(4)		:>iRAM_BOOTLOAD_TOP
/*  Symbols for compiler references */

  ___ghs_romstart   = MEMADDR(iROM_0);
  ___ghs_romend     = MEMENDADDR(iROM_0);

  ___ghs_ramstart   = MEMADDR(iRAM_0);
  ___ghs_ramend     = MEMENDADDR(iRAM_0);

  ___ghs_rramstart  = MEMADDR(iRAM_R);
  ___ghs_rramend    = MEMENDADDR(iRAM_R);

 }

/*===========================================================================*/
/*      End of File                                                          */
/*===========================================================================*/
