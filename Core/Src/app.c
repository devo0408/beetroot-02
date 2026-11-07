/**
  ******************************************************************************
  * @file           : app.c
  * @brief          : Application implementation
  ******************************************************************************
  */
#include "app.h"
#include "main.h"

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
  while (1)
  {
  }
}
