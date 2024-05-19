#ifndef __ULTRASOUND_TSK_H
#define __ULTRASOUND_TSK_H

#include "FreeRTOS.h"
#include "task.h"

#include "usart.h"
#include "HCSR04.h"
#define LED2_GPIO_PORT GPIOB
#define LED2_GPIO_PORT_RCC RCC_APB2Periph_GPIOB
#define LED2_GPIO GPIO_Pin_10

extern int ultrasound_init(void);
extern void init_receive(void *pvParameters);
extern void ultrasound_task(void *pvParameters);

#endif