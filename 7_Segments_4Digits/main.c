#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

#define SEG_A GPIO_NUM_13
#define SEG_B GPIO_NUM_12
#define SEG_C GPIO_NUM_14
#define SEG_D GPIO_NUM_27
#define SEG_E GPIO_NUM_26
#define SEG_F GPIO_NUM_25
#define SEG_G GPIO_NUM_33

#define DIGIT1 GPIO_NUM_4 // tens of mins
#define DIGIT2 GPIO_NUM_16 // minutes
#define DIGIT3 GPIO_NUM_17 // tens of seconds
#define DIGIT4 GPIO_NUM_18 // seconds

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

gpio_num_t digit_s[4] = {
    DIGIT1, DIGIT2, DIGIT3, DIGIT4
};

void init_pins(){
  for (int i = 0; i < 7; i++){
    gpio_reset_pin(segments[i]);
    gpio_set_direction(segments[i], GPIO_MODE_OUTPUT);
  }
  for (int i = 0; i < 4; i++){
    gpio_reset_pin(digit_s[i]);
    gpio_set_direction(digit_s[i], GPIO_MODE_OUTPUT);
  }
}

void display(int position, int value) {
  for (int i = 0; i < 4; i++) {
    gpio_set_level(digit_s[i], 1);
  }

  for (int i = 0; i < 7; i++) {
    gpio_set_level(segments[i], digits[value][i]);
  }

  gpio_set_level(digit_s[position], 0);

  esp_rom_delay_us(1000); 
}

void display_time(int minutes, int seconds){
  int values[4] = {
    minutes / 10,
    minutes % 10,
    seconds / 10,
    seconds % 10
  };

  for (int i = 0; i < 4; i++){
    display(i, values[i]);
  }
}


void app_main (void) {
  init_pins();

  int minutes = 0;
  int seconds = 0;

  while (true) {
    TickType_t start = xTaskGetTickCount();
    while ((xTaskGetTickCount() - start) < pdMS_TO_TICKS(1000)) {
      display_time(minutes, seconds);  
    }

    seconds++;
    if (seconds >= 60) {
      seconds = 0;
      minutes++;
      if (minutes >= 100) minutes = 0;
    }

  }
}