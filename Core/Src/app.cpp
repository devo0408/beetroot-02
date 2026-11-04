/**
  ******************************************************************************
  * @file           : app.cpp
  * @brief          : Application class implementation
  ******************************************************************************
  */
#include "app.h"
#include "app.hpp"
#include "main.h"

static volatile uint8_t btn_pressed_flag;
static volatile uint32_t btn_pressed_timestamp;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == BTN_Pin)
  {
    btn_pressed_flag = 1u;
    btn_pressed_timestamp = HAL_GetTick();
  }
}

void App::init()
{
}

void App::superloop()
{

  uint32_t heard_beat = HAL_GetTick();

  while (true)
  {
    uint32_t now = HAL_GetTick();

    if (btn_pressed_flag == 1 && now - btn_pressed_timestamp >= 30u)
    {
      if (HAL_GPIO_ReadPin(BTN_GPIO_Port, BTN_Pin) == GPIO_PIN_RESET)
      {
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
      }
      btn_pressed_flag = 0u;
    }

    if (HAL_GetTick() - heard_beat > 500u) {
      HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
      heard_beat = HAL_GetTick();
    }

  }
}

extern "C" void App_Main(void)
{
  static App app;

  app.init();
  app.superloop();
}
