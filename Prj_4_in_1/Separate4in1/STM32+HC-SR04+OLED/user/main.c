#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "FMQ.h"
#include "Serial.h"
#include "HCSR04.h"

uint16_t T;//距离

int main(void)
{
	 OLED_Init();
	 mfq_Init();
	 Serial_Init();
	 HCSR04_Init();
	
	OLED_ShowChinese(0, 47, "超声波测距：");
	OLED_ShowString(112,47,"cm",OLED_8X16);
	OLED_Update();

	while(1)
	{
		T = HCSR04_GetValue();
		
		OLED_ShowNum(88,47,T,2,OLED_8X16);
		OLED_Update();
		fmq(T);

		printf("超声波测距= %d cm\r\n",T);
	}
}
