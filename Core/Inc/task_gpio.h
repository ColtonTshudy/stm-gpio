#pragma once

#include "main.h"
#include "stm32f4xx.h"

#define NUM_IO_PINS 72

// Pin definition structure
typedef struct
{
    GPIO_TypeDef *port;
    uint8_t pin;
} GPIO_Pin_t;

uint8_t GPIO_GetID();
void GPIO_SetOutput(uint8_t);
void GPIO_SetAllToInputFloating();
void GPIO_SetAllToFloating();
void GPIO_SetAllToPulldown();
void GPIO_BlinkLED(uint8_t);
void GPIO_ReadAllPins(uint8_t *);
