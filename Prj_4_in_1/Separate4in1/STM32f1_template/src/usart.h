#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
extern void UART_Configuration(uint32_t bound);
void USART1_IRQHandler(void);
#endif