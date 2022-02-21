/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*
*                             (c) Copyright 1992-2010, Micrium, Weston, FL
*                                          All Rights Reserved
*
*                                          Renesas V850E2M Port
*
* File      : OS_CPU.H
* Version   : V2.90
* By        : Fernando J. Flores
*
* For       : Renesas V850E2M
* Toolchain : IAR EWV850 v3.7x and up
*********************************************************************************************************
*/

#ifndef  OS_CPU_H
#define  OS_CPU_H
#include <McuBoard_I.h>
/*
*********************************************************************************************************
*                                              DATA TYPES
*                                         (Compiler Specific)
*********************************************************************************************************
*/

typedef unsigned char   BOOLEAN;
typedef unsigned char   INT8U;                   /* Unsigned  8 bit quantity                            */
typedef signed   char   INT8S;                   /* Signed    8 bit quantity                            */
typedef unsigned short  INT16U;	                 /* Unsigned 16 bit quantity                            */	
typedef signed	 short  INT16S;                  /* Signed   16 bit quantity                            */	
typedef unsigned int    INT32U;                  /* Unsiged  32 bit quantity                            */	
typedef signed   int    INT32S;                  /* Signed   32 bit quantity                            */	
typedef          float  FP32;                    /* Single precision floating point                     */
typedef          double FP64;                    /* Double precision floating point                     */

typedef unsigned int    OS_STK;                  /* Each stack entry is 16-bit wide                     */
typedef unsigned int  OS_CPU_SR;               /* Define size of CPU status register                  */


/*
*********************************************************************************************************
*
* Method #1:  Disable/Enable interrupts using simple instructions.  After critical section, interrupts
*             will be enabled even if they were disabled before entering the critical section.
*
* Method #2:  Disable/Enable interrupts by preserving the state of interrupts.  In other words, if
*             interrupts were disabled before entering the critical section, they will be disabled when
*             leaving the critical section.
*             NOT IMPLEMENTED
*
* Method #3:  Disable/Enable interrupts by preserving the state of interrupts.  Generally speaking you
*             would store the state of the interrupt disable flag in the local variable 'cpu_sr' and then
*             disable interrupts.  'cpu_sr' is allocated in all of uC/OS-II's functions that need to
*             disable interrupts.  You would restore the interrupt disable state by copying back 'cpu_sr'
*             into the CPU's status register.
*********************************************************************************************************
*/

#define	 OS_CRITICAL_METHOD        3u

#if      OS_CRITICAL_METHOD == 3u
#define  OS_ENTER_CRITICAL()    {cpu_sr = CPU_SR_Save();} 	
#define  OS_EXIT_CRITICAL()     {CPU_SR_Restore(cpu_sr);} 	
#endif

/*
*********************************************************************************************************
*                                               Miscellaneous
*********************************************************************************************************
*/

#define  OS_STK_GROWTH             1u            /* Stack growth (0 == Up. 1 == Down)                                   */

#if (COMPILER==CBPLUS)
#define  OS_TASK_SW()           __asm("trap 0x00") 
#define  MCU_DI()	      __asm("di")
#define  MCU_EI()          	      __asm("ei")
#define  MCU_NOP()          	      __asm("nop")
#define  MCU_HALT()                __asm("halt")
#elif(COMPILER==IAR)
#define  OS_TASK_SW()           asm("trap 0x00")
#define  MCU_DI()	      asm("di")
#define  MCU_EI()          	      asm("ei")
#define  MCU_NOP()          	      asm("nop")
#define  MCU_HALT()                asm("halt")
#elif(COMPILER==GHS)
/*#define  OS_TASK_SW()           asm("TRAP 0x00")*/
#define  MCU_DI()	      asm("DI")
#define  MCU_EI()          	      asm("EI")
#define  MCU_NOP()          	      asm("NOP")
#define  MCU_HALT()                asm("HALT")
#endif

/*
*********************************************************************************************************
*                                              PROTOTYPES
*
* Note(s) :  (1) OS_CPU_TickInit() must be implemented by the user to initialize the timer, which will
*                be used as the tick interrupt. Moreover, OS_CPU_TickHandler() must be registered in the 
*                proper vector address of timer that will be used as the tick.
*********************************************************************************************************
*/

#if OS_CRITICAL_METHOD == 3u                     /* See OS_CPU_A.S85                                                    */
OS_CPU_SR  OS_CPU_SR_Save        (void);
void       OS_CPU_SR_Restore     (OS_CPU_SR cpu_sr);
#endif

void       OSCtxSw               (void);
void       OSIntCtxSw            (void);
void       OSStartHighRdy        (void);
                                                                /* See Note # 1.                                        */
void       OS_CPU_TickHandler    (void);
void       OS_CPU_TickInit       (INT32U  tick_per_sec);
#endif
