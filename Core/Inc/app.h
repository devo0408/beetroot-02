
#ifndef __APP_H
#define __APP_H

#include "main.h"

typedef struct {
    IWDG_HandleTypeDef* Watch_Dog_Counter;
} AppParams;


void App_Main(AppParams appParams);

#endif /* __APP_H */
