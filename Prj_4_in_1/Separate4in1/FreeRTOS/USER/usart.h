#ifndef __USART_H
#define __USART_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "air32f10x.h"
#include "air32f10x_usart.h"

#include "FreeRTOS.h"
#include "task.h"


extern USART_TypeDef *USART_TEST;

extern void UART_Configuration(uint32_t bound);
void USART1_IRQHandler(void);
#endif