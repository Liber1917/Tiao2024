#ifndef __USART_H
#define __USART_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "air32f10x.h"


extern USART_TypeDef *USART_TEST;


extern void UART_Configuration(uint32_t bound);
#endif