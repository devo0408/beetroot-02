/**
  ******************************************************************************
  * @file           : app.c
  * @brief          : Application implementation
  ******************************************************************************
  */
#include "app.h"
#include "main.h"
#include "components/watchdog.h"

static void App_Init(AppParams appParams)
{
  Watchdog_CheckResetCause();
  Watchdog_Init(appParams.Watch_Dog_Counter);
}

static void App_Superloop(void)
{
  while (1)
  {
    Watchdog_Kick();
  }
}

void App_Main(AppParams appParams)
{
  App_Init(appParams);
  App_Superloop();
}
