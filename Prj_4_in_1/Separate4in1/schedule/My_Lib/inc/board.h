#ifndef __BOARD_
#define __BOARD_

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#include <string.h>
#include <stdint.h>
#include <math.h>

#include "schedule.h"

/***************硬件中断分组******************/
#define NVIC_GROUP   NVIC_PriorityGroup_3

#define NOW 0
#define OLD 1
#define NEW 2

#define GET_TIME_NUM 10
#define TICK_PER_SECOND 1000 
#define TICK_US	(1000000/TICK_PER_SECOND)

void TDT_Cycle_Time_Init(void);
float Get_Cycle_T(u8);

void TDT_SysTick_Configuration(void);
uint32_t GetSysTime_us(void);
void DelayUs(uint32_t us);
void DelayMs(uint32_t ms);
void TDT_Board_ALL_Init(void);

extern volatile uint32_t sysTickUptime;

#endif
