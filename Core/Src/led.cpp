#include "led.hpp"

Led::Led(GPIO_TypeDef *port, uint16_t pin, bool active_low)
  : port_(port), pin_(pin), active_low_(active_low)
{
}

void Led::init(LedState initial_state)
{
  set(initial_state);
}

void Led::set(LedState state)
{
  state_ = state;

  const bool pin_high = (state_ == LedState::On) != active_low_;
  GPIO_PinState pin_state = pin_high ? GPIO_PIN_SET : GPIO_PIN_RESET;

  HAL_GPIO_WritePin(port_, pin_, pin_state);
}

void Led::toggle()
{
  set((state_ == LedState::On) ? LedState::Off : LedState::On);
}
