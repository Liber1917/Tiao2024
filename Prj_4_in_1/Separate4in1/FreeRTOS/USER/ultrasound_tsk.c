#include "ultrasound_tsk.h"

TaskHandle_t receive; // 声明一个 TaskHandle_t 类型的变量
int SER_PutChar16(uint16_t ch);
int done=0;
int ultrasound_init(void)
{
    xTaskCreate( init_receive, "init_receive", 32, NULL, 3, &receive );
    UART_Configuration(9600);
    SER_PutChar16(0xf1);
    return 1;
}

int SER_PutChar16(uint16_t ch)
{
    // 等待发送寄存器为空，即等待上一次发送完成
    while (!USART_GetFlagStatus(USART_TEST, USART_FLAG_TC))
        ;
    // 将 16 位十六进制数发送到 USART，按照十六进制的格式发送
    USART_SendData(USART_TEST, (ch >> 8) & 0xFF); // 先发送高 8 位
    while (!USART_GetFlagStatus(USART_TEST, USART_FLAG_TC))
        ;
    USART_SendData(USART_TEST, ch & 0xFF); // 再发送低 8 位
    // 返回发送的十六进制数
    return ch;
}


void init_receive(void *pvParameters)
{

    RCC_APB2PeriphClockCmd(LED2_GPIO_PORT_RCC, ENABLE);
    GPIO_InitTypeDef gpio_conf;
    GPIO_StructInit(&gpio_conf);
    gpio_conf.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_conf.GPIO_Pin = LED2_GPIO;
    gpio_conf.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED2_GPIO_PORT, &gpio_conf);


    // while(1) {
    //     if(USART_GetFlagStatus(USART_TEST, USART_FLAG_RXNE)||(USART_GetITStatus(USART_TEST, USART_IT_RXNE) != RESET))
    //     {
            GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO);
            vTaskDelay(pdMS_TO_TICKS(100));
            GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO);
            vTaskDelay(pdMS_TO_TICKS(100));
            GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO);
            vTaskDelay(pdMS_TO_TICKS(100));
            GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO);
            vTaskDelay(pdMS_TO_TICKS(100));
        //     break;
        // }

        
    // }

    vTaskDelete(NULL);//删除任务
    // vTaskSuspend(NULL);//挂起任务
}


// 定义全局变量用于存储接收到的数据
uint32_t receivedBytes;


void ultrasound_task(void *pvParameters)
{
    while(1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        
        // 检查 TXE 和 RXNE 标志位
        if (
            (USART_GetITStatus(USART_TEST, USART_IT_RXNE) == RESET)) {
            // "当前无发送且接收数据" 的状态
            SER_PutChar16(0xa0);
        }


        // // 检查是否接收到了数据
        // if (USART_GetFlagStatus(USART_TEST, USART_FLAG_RXNE))
        // {
        //     GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO);
        //     // 依次接收三个字节数据
        //     receivedBytes = USART_ReceiveData(USART_TEST);
        //     vTaskDelay(pdMS_TO_TICKS(100));
        //     GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO);
        //     continue;

        // }
        // else
        // {
        //     GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO);
        // }
    }
    // vTaskDelete(NULL);
}