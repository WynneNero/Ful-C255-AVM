/* File for os test  */

#include "tcbpost.h"
#include "iodefine.h"
#include "OSAPI.h"

#define array_count 60		// change array element number to test stack
#define schedule_interval 1	// number of system tick, now TAUD0I0 tick=2ms



// task index
/*
#define SystemSwitchHigh ((TaskType)0)
#define FastCyclic ((TaskType)1)
#define EventTask ((TaskType)2)
#define SlowCyclic ((TaskType)3)
#define SlowJob ((TaskType)4)
#define SystemSwitchLow ((TaskType)5)
#define ResetTask ((TaskType)6)
*/


#define TOTAL_LOOP ((schedule_interval*1000u)/12u)
#define MAXLOOP_FOR_TASK1	(TOTAL_LOOP/63u)	//+1)		//		3// 3*63*11.76>2ms

#define TASK1_LOOP (MAXLOOP_FOR_TASK1)		//	SystemSwitchHigh
#define TASK2_LOOP (TASK1_LOOP<<1)			//	FastCyclic
#define TASK3_LOOP (TASK1_LOOP<<2)			//	EventTask	
#define TASK4_LOOP (TASK1_LOOP<<3)			//	SlowCyclic	
#define TASK5_LOOP (TASK1_LOOP<<4)			//	SlowJob
#define TASK6_LOOP (TASK1_LOOP<<5)			//	SystemSwitchLow

/*
#define TASK1_LOOP 	10	// 1 loop ~ 11.76us/ 12.275us
#define TASK2_LOOP 	10	// 
#define TASK3_LOOP 	10	// 
#define TASK4_LOOP 	10	// 
#define TASK5_LOOP 	10	// 
#define TASK6_LOOP 	10	// 
*/

//static boolean init_ok=false;
//static uint32 TAUD0I0_count=0;
//static uint32 TAUB0I0_count=0;
//static uint32 TAUJ0I0_count=0;
static uint32 TAUJ1I0_count=0u;

static uint32 invoke_cnt[6]={0u,0u,0u,0u,0u,0u};			// record activate task times
static uint32 task_run_cnt[6]={0u,0u,0u,0u,0u,0u};		// record task executed times
static uint32 cal_error_cnt[6]={0u,0u,0u,0u,0u,0u};		// record calculation error times,  caused by interrupt ?

static uint32 invoke_cnt_st0[6]={0u,0u,0u,0u,0u,0u};			// record activate task times at point 0
static uint32 invoke_cnt_st1[6]={0u,0u,0u,0u,0u,0u};			// record activate task times at point 1
static uint32 invoke_cnt_st2[6]={0u,0u,0u,0u,0u,0u};			// record activate task times at point 2
static uint32 task_run_step[6]={0u,0u,0u,0u,0u,0u};	// record point 0,1,2

static boolean b_SysSwitch_run=FALSE;		// for lock/unlock schedule test. =True, SysSwtichHigh task run counter increases 
StatusType fun_return=0u;

void ResetTaskfunc(void)	//pri 0,auto start, enter once
{
	//if(!init_ok)
	{	
	   osActivateTask(SlowJob);
	   osActivateTask(EventTask);
	   osActivateTask(FastCyclic);
  	   osActivateTask(SlowCyclic);
	   osActivateTask(SystemSwitchHigh);
  	   osActivateTask(SystemSwitchLow);
	}
	osTerminateTask();
}

// perform calculation to test stack operation and delay some time
// parameter in: 
//	cal_loop
// 10 loop-117.6us,	5 loop -58.8us
// return:
//		always 1
double calculation_delay(uint16 cal_loop)
{
	double a=1;
	double b=2000000;
	double cal_result=1;
	uint16 i=0u;
	uint16 loop=0u;

	loop=cal_loop;
		for(i=0u;i<loop;i++)   // 10 loop-117.6us,	5 loop -58.8us
		{
		    a+=0.1;
			b-=0.1;
			cal_result=(a*b);
			cal_result=cal_result/(a*b);
		}

	
	return cal_result;
}


void SystemSwitchHighfunc(void)	
{
	double cal_result=0u;

	for(;;)
	{
		task_run_step[SystemSwitchHigh]=0u;		
	       fun_return=osWaitEvent(1u);		
		task_run_step[SystemSwitchHigh]=1u;    

		if(b_SysSwitch_run)
		{
			b_SysSwitch_run=FALSE;
			//P8    |= 0x0080U;		// p8_7 = high

			cal_result=calculation_delay(TASK1_LOOP);
			//P8    &= 0xFF7FU;		// low
					
			if(cal_result==1u)
			{
			    task_run_cnt[SystemSwitchHigh]++;
			}
			else
			{
				cal_error_cnt[SystemSwitchHigh]++;
			}
		}
		else
		{
			//missing execution of SysSwitchLow ???
		}
		    osClearEvent(1u);	    
		    task_run_step[SystemSwitchHigh]=2u;   
	}
}

void FastCyclicfunc(void)	
{
	double cal_result=0u;
	//int a[array_count]=100;
	//int b[array_count]=0;
	//unsigned int i=0;

    for(;;)
    {
     	task_run_step[FastCyclic]=0u;   
	fun_return=osWaitEvent(1u);
     	task_run_step[FastCyclic]=1u;   	

	cal_result=calculation_delay(TASK2_LOOP);

	if(cal_result==1u)
	{	
		task_run_cnt[FastCyclic]++;
	}
	else
	{
		cal_error_cnt[FastCyclic]++;
	}
	/*
	delay_us(1000);
	P8    |= 0x0080U;		// p8_7 = high
	
	delay_us(1000);
	P8    &= 0xFF7FU;		// low
	
	delay_us(1000);
	P8    |= 0x0080U;		// p8_7 = high

	delay_us(1000);
	P8    &= 0xFF7FU;		// low

		delay_us(1000);
	P8    |= 0x0080U;		// p8_7 = high

	delay_us(1000);
	P8    &= 0xFF7FU;		// low
	*/
	/*
	if(invert)
	{
		P8    |= 0x0080U;		// p8_7 = high
	    invert=0;
	}
	else
	{
		P8    &= 0xFF7FU;		// low
	    	    invert=1;
	}
	*/
	osClearEvent(1u);	
	task_run_step[FastCyclic]=2u;
    }
}

void EventTaskfunc(void)
{
   	double cal_result=0u;

    for(;;)
    {
    	task_run_step[EventTask]=0u;   
	fun_return=osWaitEvent(1u);
 	task_run_step[EventTask]=1u;   

	cal_result=calculation_delay(TASK3_LOOP);
	
	if(cal_result==1u)
	{	
		task_run_cnt[EventTask]++;
	}
	else
	{
		cal_error_cnt[EventTask]++;
	}

	osClearEvent(1u);
	task_run_step[EventTask]=2u;   
    }
}



void SlowCyclicfunc(void)  	
{
   double cal_result=0u;

    for(;;)
    {
    	task_run_step[SlowCyclic]=0u;
	fun_return=osWaitEvent(1u);
    	task_run_step[SlowCyclic]=1u;
	
	cal_result=calculation_delay(TASK4_LOOP);
	
	if(cal_result==1u)
	{	
		task_run_cnt[SlowCyclic]++;
	}
	else
	{
		cal_error_cnt[SlowCyclic]++;
	}

    	osClearEvent(1u);
    	task_run_step[SlowCyclic]=2u;
    }
}
void SlowJobfunc(void)		
{    
	double cal_result=0u;

	for(;;)
	{
	    task_run_step[SlowJob]=0u;   
	    fun_return=osWaitEvent(1u);	
	    task_run_step[SlowJob]=1u;   
	    
		cal_result=calculation_delay(TASK5_LOOP);
		
		if(cal_result==1u)
		{
		   task_run_cnt[SlowJob]++;
		}
	   	else
		{
			cal_error_cnt[SlowJob]++;
		}
	    osClearEvent(1u);
     	task_run_step[SlowJob]=2u;   
	}
	
}


void SystemSwitchLowfunc(void)	
{
	double cal_result=0u;
//    TickRefType start_time=0;
//    TickRefType use_time=0;
    
//    start_time =osGetCurrentTimeStd(0);
    //osGetCounterValue(0,start_time);

    for(;;)
    {
      	task_run_step[SystemSwitchLow]=0u;
	fun_return=osWaitEvent(1u);
      	task_run_step[SystemSwitchLow]=1u;


	osSuspendOSInterrupts();		//task lock/unlock schedule
	b_SysSwitch_run=TRUE;		//SysSwitchhigh task has to wait for this to run
	osResumeOSInterrupts();		//task lock/unlock schedule
	
		
	cal_result=calculation_delay(TASK6_LOOP);
	
	if(cal_result==1u)
	{
	   task_run_cnt[SystemSwitchLow]++;
	}
   	else
	{
		cal_error_cnt[SystemSwitchLow]++;
	}

	osClearEvent(1u);
      	task_run_step[SystemSwitchLow]=2u;
		

    }
}

//in parameter: 
//				taskid- task to activate
//				invoke_times-	activate task mutiple times, times=invoke_times+1
void invoke_task(TaskType taskid,uint16 invoke_times)
{	
	uint16 i=0u;
	uint16 invokeTimes=0u;
	
	invokeTimes=invoke_times+1u;
	
	for(i=0u;i<invokeTimes;i++)
	{
		osSetEvent(taskid,1u);
		invoke_cnt[taskid]++;
		
		switch(task_run_step[taskid])
		{
			case 0:
				invoke_cnt_st0[taskid]++;
				break;
			case 1:
				invoke_cnt_st1[taskid]++;				
				break;		
			case 2:
				invoke_cnt_st2[taskid]++;								
				break;					
			default:
				break;
		}
	}
}


void ISR_WDTA0func(void)
{
	// for test
	static U32 WDT_cnt=0u;		// can't enter
	WDT_cnt++;	
}
/*
void ISR_CAN0ERRfunc(void)
{}
 void ISR_CAN0RECfunc(void)
 {}
void ISR_CAN0TRXfunc(void)
 {}
void ISR_CANGERRfunc(void)
 {}
void ISR_CANGRECCfunc(void)
 {}
*/
void CanIsrStatus_0(void)
{}
void CanIsrWakeup_0(void)
{}
void CanIsrTx_0(void)
{}
void CanIsrGlobalStatus(void)
{}
void CanIsrRxFifo(void)
{}


