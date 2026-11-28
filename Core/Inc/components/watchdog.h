//
// Created by Denys Vovk on 28.11.2026.
//

#ifndef CLION_TEST_STM32_WATCHDOG_H
#define CLION_TEST_STM32_WATCHDOG_H

#include <stdbool.h>

void Watchdog_Init(IWDG_HandleTypeDef* iwdg);
void Watchdog_CheckResetCause(void);
void Watchdog_Kick(void);
bool Watchdog_WasIwdgReset(void);

#endif //CLION_TEST_STM32_WATCHDOG_H
