#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "air32f10x.h"

#include "FreeRTOS.h"
#include "task.h"

#include "led.h"
#include "ultrasound_tsk.h"

uint32_t SystemCoreClock = 256000000;

// 定义主任务的优先级: 空闲任务优先级加 3
#define mainCREATOR_TASK_PRIORITY ( tskIDLE_PRIORITY + 3 )

// 定义 LED 任务的优先级，其值为 3
#define TASK_PRORITY_LED 3


int main(void)
{
	RCC_ClocksTypeDef clocks;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	RCC_GetClocksFreq(&clocks); //获取时钟频率

	// 超声检测初始化
	ultrasound_init();
	//

	
	// printf("SYSCLK: %3.1fMhz, \nHCLK: %3.1fMhz, \nPCLK1: %3.1fMhz, \nPCLK2: %3.1fMhz, \nADCCLK: %3.1fMhz\n",
	// 		   (float)clocks.SYSCLK_Frequency / 1000000, (float)clocks.HCLK_Frequency / 1000000,
	// 		   (float)clocks.PCLK1_Frequency / 1000000, (float)clocks.PCLK2_Frequency / 1000000, (float)clocks.ADCCLK_Frequency / 1000000);
    
    // 创建一个 FreeRTOS 任务来运行 LED 控制任务
	// 参数说明：
	//   - task_led: 任务函数的指针，这里是指向任务 LED 控制函数的指针
	//   - "task_led": 任务的名称，在调试时用于识别任务
	//   - 128: 任务堆栈的大小，以字为单位，这里分配了 128 字节的堆栈空间
	//   - NULL: 传递给任务函数的参数，这里没有传递任何参数
	//   - TASK_PRORITY_LED: 任务的优先级，定义在代码中，用于控制任务的调度顺序
	//   - NULL: 任务的句柄，用于后续对任务的操作，这里不需要返回任务句柄，因此为 NULL
	xTaskCreate( task_led, "task_led", 64, NULL, TASK_PRORITY_LED, NULL );
	xTaskCreate( ultrasound_task, "ultrasound_task", 128, NULL, 2, NULL );


	
    
	/* Start the scheduler. */
	vTaskStartScheduler();
	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}

void SystemInit(void)
{
	RCC_DeInit(); //复位RCC寄存器
	RCC_HSEConfig(RCC_HSE_ON); //使能HSE
	while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET); //等待HSE就绪
	RCC_PLLCmd(DISABLE);										 //关闭PLL
	AIR_RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_32, FLASH_Div_2); //配置PLL,8*32=256MHz
	RCC_PLLCmd(ENABLE); //使能PLL
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET); //等待PLL就绪
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //选择PLL作为系统时钟
	RCC_HCLKConfig(RCC_SYSCLK_Div1); //配置AHB时钟
	RCC_PCLK1Config(RCC_HCLK_Div2);	 //配置APB1时钟
	RCC_PCLK2Config(RCC_HCLK_Div1);	 //配置APB2时钟
	RCC_LSICmd(ENABLE); //使能内部低速时钟
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);				//等待LSI就绪
	RCC_HSICmd(ENABLE); //使能内部高速时钟
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET); //等待HSI就绪
}

void xPortSysTickHandler( void );
void SysTick_Handler( void )
{
    // 检查任务调度器的状态是否已经启动
    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        // 如果调度器已经启动，则调用 FreeRTOS 提供的 SysTick 处理函数
        xPortSysTickHandler();
    }
}


