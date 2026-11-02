/**
  ******************************************************************************
  * @file           : app.cpp
  * @brief          : Application class implementation
  ******************************************************************************
  */
#include "app.h"
#include "app.hpp"
#include "main.h"

static constexpr uint32_t BTN_SAMPLE_PERIOD_TIMESTAMP = 5;
static constexpr uint32_t LED_MAX_HALF_PERIOD = 8000;

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

typedef struct BUTTON_type_t {

  static constexpr uint32_t BTN_STABLE_STATE_CLICKS = 5;

  GPIO_TypeDef * port;
  uint32_t pin;
  uint32_t last_time_sample_timestamp;

  uint32_t clickCount = 0;
  bool wasPressed = false;

  void RegisterClick()
  {
    if (clickCount < BTN_STABLE_STATE_CLICKS)
    {
      clickCount++;
    }
  }

  void RegisterClean()
  {
    if (clickCount > 0)
    {
      clickCount--;
    }
  }

  bool IsPressed() {
    return BTN_STABLE_STATE_CLICKS == clickCount;
  }

  bool JustPressed() {
    bool pressed = IsPressed();
    bool result = pressed && !wasPressed;
    wasPressed = pressed;
    return result;
  }

} BUTTON_type_t;

BUTTON_type_t TURN_OFF_BUTTON = {.port = BUTTON_1_GPIO_Port, .pin = BUTTON_1_Pin, .last_time_sample_timestamp = 0u};
BUTTON_type_t LED_2_PERIOD_BUTTON = {.port = BUTTON_2_GPIO_Port, .pin = BUTTON_2_Pin, .last_time_sample_timestamp = 0u};



void App::init()
{
}

void App::superloop()
{

  while (true)
  {
    loop_timestamp_now = HAL_GetTick();
    {

      // turn off all leds by button click
      BUTTON_type_t* turn_off_button_pointer =  &TURN_OFF_BUTTON;
      if (loop_timestamp_now - turn_off_button_pointer->last_time_sample_timestamp >= BTN_SAMPLE_PERIOD_TIMESTAMP)
      {
        GPIO_PinState state = HAL_GPIO_ReadPin(turn_off_button_pointer->port, turn_off_button_pointer->pin);
        turn_off_button_pointer->last_time_sample_timestamp = loop_timestamp_now;

        if (state) {
          turn_off_button_pointer->RegisterClean();
        } else {
          turn_off_button_pointer->RegisterClick();
        }

        if (turn_off_button_pointer->IsPressed())
        {
          uint8_t leds_size = sizeof(LEDS) / sizeof(LEDS[0]);
          for (uint8_t led_idx = 0; led_idx < leds_size; led_idx++) {

            LED_type_t* led = &LEDS[led_idx];
            if (loop_timestamp_now - led->last_time_change_timestamp >= led->half_period)
            {
              HAL_GPIO_WritePin(led->port, led->pin, GPIO_PIN_SET); // Schema how LED connected: 3.3 V - R - LED -  PA2
              led->last_time_change_timestamp = loop_timestamp_now;
            }
          }
        }

      }

      // change LED 2 period
      BUTTON_type_t* led_2_period_button =  &LED_2_PERIOD_BUTTON;
      if (loop_timestamp_now - led_2_period_button->last_time_sample_timestamp >= BTN_SAMPLE_PERIOD_TIMESTAMP) {

        GPIO_PinState state = HAL_GPIO_ReadPin(led_2_period_button->port, led_2_period_button->pin);
        led_2_period_button->last_time_sample_timestamp = loop_timestamp_now;

        if (state) {
          led_2_period_button->RegisterClean();
        } else {
          led_2_period_button->RegisterClick();
        }

        if (led_2_period_button->JustPressed()) {

          LED_type_t* led = &LEDS[1]; // led 2 index
          if (led->half_period < LED_MAX_HALF_PERIOD) {
            led->half_period *= 2;
          }
        }
      }


      // LED blinks
      uint8_t leds_size = sizeof(LEDS) / sizeof(LEDS[0]);
      for (uint8_t led_idx = 0; led_idx < leds_size; led_idx++) {

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
