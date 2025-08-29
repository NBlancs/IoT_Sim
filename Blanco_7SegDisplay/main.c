#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define SEG_A GPIO_NUM_13
#define SEG_B GPIO_NUM_12
#define SEG_C GPIO_NUM_14
#define SEG_D GPIO_NUM_27
#define SEG_E GPIO_NUM_26
#define SEG_F GPIO_NUM_25
#define SEG_G GPIO_NUM_33

const uint8_t digits[10][7] = {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
};

gpio_num_t segments[7] = {
    SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G
};

void init_segments() {
    for (int i = 0; i < 7; i++) {
        gpio_reset_pin(segments[i]);
        gpio_set_direction(segments[i], GPIO_MODE_OUTPUT);
    }
}

void show_number(int num) {
    for (int i = 0; i < 7; i++) {
        gpio_set_level(segments[i], digits[num][i]);
    }
}

void app_main(void) {
    init_segments();

    while (1) {
        for (int i = 0; i < 10; i++) {
            show_number(i);
            vTaskDelay(pdMS_TO_TICKS(1000)); 

        }
    }
}
