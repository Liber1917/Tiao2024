#include "led.h"

void delay(int x)//
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 1000; j++)
            __NOP();
    }
}

void led_init(void)
{
    GPIO_InitTypeDef gpioDef;
    RCC_APB2PeriphClockCmd(LED_PERIPH, ENABLE);
    gpioDef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpioDef.GPIO_Pin = LED_PIN;
    gpioDef.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(LED_PORT, &gpioDef);
}

void run_led(void)
{
    GPIO_WriteBit(LED_PORT, LED_PIN, (BitAction)!GPIO_ReadInputDataBit(LED_PORT, LED_PIN));
    delay(5000);
}