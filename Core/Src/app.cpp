/**
  ******************************************************************************
  * @file           : app.cpp
  * @brief          : Application class implementation
  ******************************************************************************
  */
#include "app.h"
#include "app.hpp"
#include "main.h"
#include "log.hpp"

void App::init()
{
  LOG_INFO("APP", "started, SYSCLK = %lu Hz", HAL_RCC_GetSysClockFreq());
}

void App::superloop()
{
  uint32_t lastTick = HAL_GetTick();
  uint32_t counter = 0;

  while (true)
  {
    if ((HAL_GetTick() - lastTick) >= 1000U)
    {
      lastTick = HAL_GetTick();
      LOG_DEBUG("APP", "tick %lu", counter++);
    }
  }
}

extern "C" void App_Main(void)
{
  static App app;

  app.init();
  app.superloop();
}
