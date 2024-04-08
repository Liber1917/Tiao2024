#include "usart.h"

// 定义串口接收缓冲区大小
#define RX_BUFFER_SIZE 128
char rx_buffer[RX_BUFFER_SIZE];
volatile uint8_t rx_buffer_index = 0;

USART_TypeDef *USART_TEST = USART1;

// 串口配置函数
void UART_Configuration(uint32_t bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能串口和GPIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    // 配置USART1 TX (PA.9) 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置USART1 RX (PA.10) 引脚
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // USART 初始化设置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART_TEST, &USART_InitStructure);

    // 使能 USART1 接收中断
    USART_ITConfig(USART_TEST, USART_IT_RXNE, ENABLE);

    // 配置 NVIC 中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 使能串口
    USART_Cmd(USART_TEST, ENABLE);
}

// 串口接收中断处理函数
void USART1_IRQHandler(void)
{
    // 检查是否是串口接收中断
    if (USART_GetITStatus(USART_TEST, USART_IT_RXNE) != RESET)
    {
        // 从串口接收数据寄存器中读取数据
        char received_char = USART_ReceiveData(USART_TEST);

        // 处理接收到的数据
        rx_buffer[rx_buffer_index++] = received_char;
        // 如果缓冲区已满，则重置索引
        if (rx_buffer_index >= RX_BUFFER_SIZE)
        {
            rx_buffer_index = 0;
        }

        // 清除中断标志
        USART_ClearITPendingBit(USART_TEST, USART_IT_RXNE);
    }

}