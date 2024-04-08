/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"

#include "led.h"
#include "usart.h"


int main()
{
    led_init();
    UART_Configuration(9600);
    USART_SendData(USART1, 0xf1);

    while (1)
    {
        run_led();
    }
}
