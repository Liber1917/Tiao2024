#ifndef __LED_H
#define __LED_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "air32f10x.h"

#include "FreeRTOS.h"
#include "task.h"

#define LED1_GPIO_PORT GPIOB
#define LED1_GPIO_PORT_RCC RCC_APB2Periph_GPIOB
#define LED1_GPIO GPIO_Pin_11



extern void task_led(void *pvParameters);

#endif /* __LED_H */
