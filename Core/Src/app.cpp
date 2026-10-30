/**
  ******************************************************************************
  * @file           : app.cpp
  * @brief          : Application class implementation
  ******************************************************************************
  */
#include "app.h"
#include "app.hpp"
#include "main.h"

void App::init()
{
}

void App::superloop()
{
  while (true)
  {
  }
}

extern "C" void App_Main(void)
{
  static App app;

  app.init();
  app.superloop();
}
