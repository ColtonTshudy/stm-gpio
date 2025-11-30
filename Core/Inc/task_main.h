#pragma once

#include "main.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "task_usb.h"
#include "task_gpio.h"
#include <stdio.h>

#define ENABLE_DEBUG 1
#if ENABLE_DEBUG
#define Debug(__info, ...) printf(" [DBG]: " __info "\r\n", ##__VA_ARGS__)
#else
#define Debug(__info, ...)
#endif

void Main_Setup();
void Main_Loop();