#ifndef __ADC_H
#define __ADC_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "air32f10x.h"
#include "air32f10x_adc.h"
#include "math.h"

#define PRINTF_LOG printf

#define CONV_CHANNEL_NUM 1
#define VREF (3300)

extern void UART_Configuration(void);
extern void ADC_Configuration(void);
extern void DMA_Configuration(void);

#define ADC_TEST_CHANNEL_PIN (GPIO_Pin_2)
extern void task_adc(void *pvParameters);

#endif