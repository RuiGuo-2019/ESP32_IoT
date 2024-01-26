// #include <stdio.h>
// #include <driver/gpio.h>
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// #define GPIO_BUTTON_IO  4
// #define GPIO_LED_IO     5

// #define LED_PIN GPIO_NUM_5
// #define BUTTON_PIN GPIO_NUM_4
// void app_main() {
//     printf("Demo2: led");
//     gpio_config_t my_io_config =
//     {
//         .pin_bit_mask = 1 << GPIO_LED_IO, //
//         .mode = GPIO_MODE_OUTPUT, //设置为输出模式
//     };
//     gpio_config(&my_io_config);
//     // step 2 点亮LED

//     bool led_value = false;
//     while(1){
//         gpio_set_level(GPIO_LED_IO, led_value);
//         vTaskDelay(1000/portTICK_PERIOD_MS);
//         // ets_delay_us(1000000);
//         led_value = !led_value;
//     }


//     // // always prompt warnings
//     // printf("Demo2: led and button");
//     // gpio_pad_select_gpio(LED_PIN);
//     // gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
//     // gpio_set_level(LED_PIN, 0);

//     // gpio_pad_select_gpio(BUTTON_PIN);
//     // gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
//     // // gpio_set_level(BUTTON_PIN, 0);
    
//     // int btnState = 0;
//     // int lastState = 0;
//     // while(true)
//     // {
//     //     btnState = gpio_get_level(BUTTON_PIN);
//     //     if(lastState != btnState){
//     //         gpio_set_level(LED_PIN, btnState);
//     //         printf("Current State: %d", btnState);
//     //         lastState = btnState;
//     //     }
//     // }

// }

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"


#define LED_PIN GPIO_NUM_5
#define BUTTON_PIN GPIO_NUM_4

/* 定时器1回调函数 */
void timer1_Callback(void *arg);
/* 用于保存按钮的状态 */
uint16_t buttom_state = 0;  

static const char *TAG = "a buttom contorl a LED";
static esp_timer_handle_t timer1_handler;  /* 定时器1的句柄 */

/* 定时器1的参数 */
static esp_timer_create_args_t timer_Once_Obj = {
    .name = "Timer_NUM_1",          /* 定时器的名称 */
    .arg = NULL,                    /* 传递给回调函数的参数 */
    .callback = &timer1_Callback,   /* 回调函数 */
};

void app_main(void)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");

    /* 复位GPIO的状态 */
    gpio_reset_pin(LED_PIN);
    gpio_reset_pin(BUTTON_PIN);

    /* 设置GPIO4为输入模式 */
    gpio_set_direction(BUTTON_PIN,GPIO_MODE_INPUT);
    /* 设置GPIO4为上拉模式 */
    gpio_set_pull_mode(BUTTON_PIN,GPIO_PULLUP_ONLY);
    /* 设置GPIO5为输出模式 */
    gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT);

    /* 初始化定时器 */
    esp_timer_init(); 

    /* 创建定时器1 */
    esp_timer_create(&timer_Once_Obj,&timer1_handler);

    /* 启动定时器1（周期性） */
    esp_timer_start_periodic(timer1_handler,100 * 1000);

    while(1)
    {
        vTaskDelay(300 / portTICK_PERIOD_MS);   /* 延时300ms */
    }

}

/* 定时器1回调函数 */
uint16_t buttom_state_pre = 0;
void timer1_Callback(void *arg)
{
    buttom_state = gpio_get_level(BUTTON_PIN);   /* 获取gpio的电平状态，gpio=0时，表示按钮被按下，gpio=1时，表示按钮没有被按下 */
    if(buttom_state_pre != buttom_state){
        ESP_LOGI(TAG, "the state of buttom is %d",buttom_state);

        /* 如果按钮被按下，LED亮起来 */
        if(0 == buttom_state)
            gpio_set_level(LED_PIN,0);
        /* 否则LED熄灭 */
        else
            gpio_set_level(LED_PIN,1);    
        
        buttom_state_pre = buttom_state;
    }
    

}