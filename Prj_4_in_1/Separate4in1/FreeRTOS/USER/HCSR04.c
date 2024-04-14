#include "air32f10x.h"               // Device header
#include "HCSR04.h"
#include "FreeRTOS.h"
#include "task.h"

//TODO 配置定时器，移植到RTOs
// #include "Delay.h"
// #include "Timer.h"
uint16_t Time;//高电平时间

void HCSR04_Init()
{
	RCC_APB2PeriphClockCmd(Trig_RCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStruct.GPIO_Pin = Trig_Pin;          //PA0
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;//io口速度50MHZ
	GPIO_Init(Trig_Port, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;		//上拉输入
	GPIO_InitStruct.GPIO_Pin = Echo_Pin;					//PA1
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Echo_Port, &GPIO_InitStruct);
	
	GPIO_ResetBits(Trig_Port, Trig_Pin);
}

void HCSR04_Start()
{
	GPIO_SetBits(Trig_Port, Trig_Pin);
	// Delay_us(45);
	vTaskDelay(pdMS_TO_TICKS(45));
	GPIO_ResetBits(Trig_Port, Trig_Pin);
	// Timer_Init();
}

uint16_t HCSR04_GetValue()
{
	HCSR04_Start();
	// Delay_ms(100);
	vTaskDelay(pdMS_TO_TICKS(100));
	return ((Time * 0.0001) * 34000) / 2;  // cm/s  [(0.00001s*340m/s)/2] * 100
//	return Time;
}
