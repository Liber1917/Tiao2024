#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_PERIPH RCC_APB2Periph_GPIOB
#define LED_PORT GPIOB
#define LED_PIN GPIO_Pin_11

extern void delay(int x);
extern void led_init(void);
extern void run_led(void);

#endif