x#ifndef TIMEBASE_HPP
#define TIMEBASE_HPP

//#include "main.h"

inline uint32_t millis()
{
  return HAL_GetTick();
}

class IntervalTimer
{
public:
  explicit IntervalTimer(uint32_t interval_ms)
    : interval_ms_(interval_ms), last_ms_(millis())
  {
  }

  bool elapsed()
  {
    if ((millis() - last_ms_) >= interval_ms_)
    {
      last_ms_ += interval_ms_;
      return true;
    }
    return false;
  }

private:
  const uint32_t interval_ms_;
  uint32_t       last_ms_;
};

#endif /* TIMEBASE_HPP */
