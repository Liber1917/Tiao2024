#include "board.h"

u8 Init_OK;

//滴答定时器计数变量 ,49天后溢出
volatile uint32_t sysTickUptime=0;
volatile float Cycle_T[GET_TIME_NUM][3];

void TDT_Cycle_Time_Init(void)
{
	u8 i;
	for(i=0;i<GET_TIME_NUM;i++)
	{
		Get_Cycle_T(i);
	}
}

float Get_Cycle_T(u8 item)	
{
	Cycle_T[item][OLD] = Cycle_T[item][NOW];	//上一次的时间
	Cycle_T[item][NOW] = GetSysTime_us()/1000000.0f; //本次的时间
	Cycle_T[item][NEW] = ( ( Cycle_T[item][NOW] - Cycle_T[item][OLD] ) );//间隔的时间（周期）
	return Cycle_T[item][NEW];
}

void TDT_SysTick_Configuration(void)
{
	RCC_ClocksTypeDef	rcc_clocks;
	uint32_t			cnts;

	RCC_GetClocksFreq(&rcc_clocks);

	cnts = (uint32_t)rcc_clocks.HCLK_Frequency / TICK_PER_SECOND;
	cnts = cnts / 8;

	SysTick_Config(cnts);
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
}

uint32_t GetSysTime_us(void) 
{
	register uint32_t ms;
	u32 value;
	ms = sysTickUptime;
	value = ms * TICK_US + (SysTick->LOAD - SysTick->VAL) * TICK_US / SysTick->LOAD;
	return value;
}

void DelayUs(uint32_t us)
{
    uint32_t now = GetSysTime_us();
    while(GetSysTime_us() - now < us);
}

void DelayMs(uint32_t ms)
{
    while (ms--)
		DelayUs(1000);
}

void Led_Init(void)
{
	GPIO_InitTypeDef GPIO_IS ;
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO,ENABLE) ;
	
	GPIO_PinRemapConfig (GPIO_Remap_SWJ_JTAGDisable ,ENABLE) ;
	
	GPIO_IS.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_IS.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_11 ;
	GPIO_IS.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOB , &GPIO_IS) ;
	
	GPIO_IS.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_IS.GPIO_Pin = GPIO_Pin_15;
	GPIO_IS.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_IS) ;
}

void TDT_Board_ALL_Init(void)
{
	/*中断分组*/
	NVIC_PriorityGroupConfig(NVIC_GROUP);
	/*滴答定时器配置*/
	TDT_SysTick_Configuration();
	/*时间初始化*/
	TDT_Cycle_Time_Init();
	/*初始化完成*/	
	Led_Init();	
	Init_OK = 1;
}
