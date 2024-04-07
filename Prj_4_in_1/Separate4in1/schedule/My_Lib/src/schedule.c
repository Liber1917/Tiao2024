#include "schedule.h"
int i = 0 , j = 0 , k = 0 ,state[5] = {0,1,0,0,0} ;
void TDT_Loop_1000Hz(void)//1ms执行一次
{
	
}

void TDT_Loop_500Hz(void)	//2ms执行一次
{
	
}

void TDT_Loop_200Hz(void)	//5ms执行一次
{
	
}

void TDT_Loop_100Hz(void)	//10ms执行一次
{
	if(state[1] == 1)
	{
		if(k%20>10)
		{	
			GPIO_SetBits (GPIOA,GPIO_Pin_15) ;
			
			if(k == 19)
			{
				state[2] = 1 ;
				state[1] = 0 ;
				state[3] = 0 ;
				k = 0 ;
			}
			else
			{
				k++ ;
			}
		}
		else
		{
			GPIO_ResetBits (GPIOA,GPIO_Pin_15) ;
			k++ ;
		}
	
	
	}
	
	
}

void TDT_Loop_50Hz(void)	//20ms执行一次
{
	if(state[2] == 1)
	{
		if(j%20>10)
		{
			GPIO_SetBits (GPIOB,GPIO_Pin_12) ;
			if(j == 39)
			{
				state[2] = 0 ;
				state[1] = 0 ;
				state[3] = 1 ;
				j = 0 ;
			}
			else
			{
				j++ ;
			}
		}
		else
		{
			GPIO_ResetBits (GPIOB,GPIO_Pin_12) ;
			j++ ;
		}
	}
}

void TDT_Loop_20Hz(void)	//50ms执行一次
{
	if(state[3] == 1)
	{
		if(i%40>20)
		{

			GPIO_SetBits (GPIOB,GPIO_Pin_11) ;
			if(i == 119)
			{
				state[2] = 0 ;
				state[1] = 1 ;
				state[3] = 0 ;
				i = 0 ;
			}
			else
			{
				i++ ;
			}
			
		}
		else
		{
			GPIO_ResetBits (GPIOB,GPIO_Pin_11) ;
			i++ ;
		}

	
	}
	
}

void TDT_Loop(schedule* robotSchdule)
{
	if(robotSchdule->cnt_1ms >= 1)
	{
		TDT_Loop_1000Hz();	
		robotSchdule->cnt_1ms = 0;
	}
	if(robotSchdule->cnt_2ms >= 2)
	{
		TDT_Loop_500Hz();
		robotSchdule->cnt_2ms = 0;
	}		
	if(robotSchdule->cnt_5ms >= 5)
	{	
		TDT_Loop_200Hz();
		robotSchdule->cnt_5ms = 0;
	}
	if(robotSchdule->cnt_10ms >= 10)
	{		
		TDT_Loop_100Hz();
		robotSchdule->cnt_10ms = 0;
	}
	if(robotSchdule->cnt_20ms >= 20)
	{		
		TDT_Loop_50Hz();
		robotSchdule->cnt_20ms = 0;
	}
	if(robotSchdule->cnt_50ms >= 50)
	{		
		TDT_Loop_20Hz();
		robotSchdule->cnt_50ms = 0;
	}
}
