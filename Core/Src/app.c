/**
  ******************************************************************************
  * @file           : app.c
  * @brief          : Application implementation
  ******************************************************************************
  */
#include "app.h"
#include "main.h"

static volatile uint8_t btn_pressed_flag;
static volatile uint32_t btn_pressed_timestamp;

static void App_Init(void);
static void App_Superloop(void);

void App_Main(void)
{
  App_Init();
  App_Superloop();
}

static void App_Init(void)
{
}

static void App_Superloop(void)
{
  uint32_t heart_beat_blink = HAL_GetTick();

  while (1)
  {
    uint32_t now = HAL_GetTick();

    if (btn_pressed_flag && now - btn_pressed_timestamp >= 30u)
    {
      if (HAL_GPIO_ReadPin(BUTTON_USER_GPIO_Port, BUTTON_USER_Pin) == GPIO_PIN_RESET) {
        HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
      }

      btn_pressed_flag = 0u;
    }

    // verify that system is active
    if (now - heart_beat_blink > 500u)
    {
        HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
        heart_beat_blink = now;
    }


  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == BUTTON_USER_Pin)
  {
    btn_pressed_flag = 1u;
    btn_pressed_timestamp = HAL_GetTick();
  }
}
