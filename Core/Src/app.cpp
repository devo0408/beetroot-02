/**
  ******************************************************************************
  * @file           : app.cpp
  * @brief          : Application class implementation
  ******************************************************************************
  */
#include "app.h"
#include "app.hpp"
#include "main.h"

uint32_t loop_timestamp_now = 0u;

typedef struct {
  GPIO_TypeDef * port;
  uint32_t pin;
  uint32_t half_period;
  uint32_t last_time_change_timestamp;
} LED_type_t;

LED_type_t LEDS[] =
{
  [0] = {.port = LED_1_GPIO_Port, .pin = LED_1_Pin, .half_period = 200, .last_time_change_timestamp = 0u},
  [1] = {.port = LED_2_GPIO_Port, .pin = LED_2_Pin, .half_period = 500, .last_time_change_timestamp = 0u},
  [2] = {.port = LED_3_GPIO_Port, .pin = LED_3_Pin, .half_period = 1000, .last_time_change_timestamp = 0u},
};

void App::init()
{
}

void App::superloop()
{

  while (true)
  {
    loop_timestamp_now = HAL_GetTick();
    //if (HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin) == GPIO_PIN_RESET)
    {
      // __disable_irq();
      // HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
      // __enable_irq();
      // HAL_Delay(500);

      for (uint8_t led_idx = 0; led_idx < 3; led_idx++) {

        LED_type_t* led = &LEDS[led_idx];
        if (loop_timestamp_now - led->last_time_change_timestamp >= led->half_period)
        {
          HAL_GPIO_TogglePin(led->port, led->pin);
          led->last_time_change_timestamp = loop_timestamp_now;
        }
      }

    }


  }
}

extern "C" void App_Main(void)
{
  static App app;

  app.init();
  app.superloop();
}
