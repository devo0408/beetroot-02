#ifndef LED_HPP
#define LED_HPP

#include "main.h"

enum class LedState : uint8_t
{
  Off,
  On
};

class Led
{
public:
  Led(GPIO_TypeDef *port, uint16_t pin, bool active_low);

  void init(LedState initial_state);
  void set(LedState state);
  void toggle();

  LedState state() const { return state_; }

private:
  GPIO_TypeDef *const port_;
  const uint16_t      pin_;
  const bool          active_low_;
  LedState            state_ = LedState::Off;
};

#endif /* LED_HPP */
