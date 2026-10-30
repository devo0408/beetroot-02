#include "app.h"
#include "app_config.hpp"
#include "timebase.hpp"

void App_Run()
{
  Led led(LedConfig::Port, LedConfig::Pin, LedConfig::ActiveLow);
  led.init(LedConfig::InitialState);

  IntervalTimer blink_timer(LedConfig::BlinkIntervalMs);

  while (true)
  {
    if (blink_timer.elapsed())
    {
      led.toggle();
    }
  }
}
