//
// Created by Denys Vovk on 28.11.2026.
//

#include <stdbool.h>
#include "main.h"

static IWDG_HandleTypeDef* iwdg;
static bool wasIwdgReset;

void Watchdog_Init(IWDG_HandleTypeDef* iwdgValue) {
    iwdg = iwdgValue;

    __HAL_DBGMCU_FREEZE_IWDG();
    __HAL_DBGMCU_FREEZE_TIM2();
    __HAL_DBGMCU_FREEZE_TIM3();

    HAL_DBGMCU_EnableDBGSleepMode();
}

void Watchdog_CheckResetCause(void)
{
    wasIwdgReset = (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET);
    __HAL_RCC_CLEAR_RESET_FLAGS();
}

void Watchdog_Kick(void)
{
    HAL_IWDG_Refresh(iwdg);
}

bool Watchdog_WasIwdgReset(void)
{
    return wasIwdgReset;
}