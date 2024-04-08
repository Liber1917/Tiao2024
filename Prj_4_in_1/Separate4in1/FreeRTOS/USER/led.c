#include "led.h"

void task_led(void *pvParameters)
{

    RCC_APB2PeriphClockCmd(LED1_GPIO_PORT_RCC, ENABLE);
    GPIO_InitTypeDef gpio_conf;
    GPIO_StructInit(&gpio_conf);
    gpio_conf.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_conf.GPIO_Pin = LED1_GPIO;
    gpio_conf.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO_PORT, &gpio_conf);

    while(1) {
        GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO);
        vTaskDelay(pdMS_TO_TICKS(500));
        GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    vTaskDelete(NULL);
}
