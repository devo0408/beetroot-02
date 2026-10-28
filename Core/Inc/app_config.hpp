#ifndef APP_CONFIG_HPP
#define APP_CONFIG_HPP

#include "led.hpp"

struct LedConfig
{
  static inline GPIO_TypeDef *const Port = GPIOC;

  static constexpr uint16_t Pin             = GPIO_PIN_13;
  static constexpr bool     ActiveLow       = true;
  static constexpr uint32_t BlinkIntervalMs = 500;
  static constexpr LedState InitialState    = LedState::Off;
};

#endif /* APP_CONFIG_HPP */
