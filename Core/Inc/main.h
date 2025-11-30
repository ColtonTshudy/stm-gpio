/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define IO19_Pin GPIO_PIN_2
#define IO19_GPIO_Port GPIOE
#define IO25_Pin GPIO_PIN_3
#define IO25_GPIO_Port GPIOE
#define IO20_Pin GPIO_PIN_4
#define IO20_GPIO_Port GPIOE
#define IO21_Pin GPIO_PIN_5
#define IO21_GPIO_Port GPIOE
#define IO23_Pin GPIO_PIN_6
#define IO23_GPIO_Port GPIOE
#define USER_Btn_Pin GPIO_PIN_13
#define USER_Btn_GPIO_Port GPIOC
#define IO26_Pin GPIO_PIN_0
#define IO26_GPIO_Port GPIOF
#define IO24_Pin GPIO_PIN_1
#define IO24_GPIO_Port GPIOF
#define IO22_Pin GPIO_PIN_2
#define IO22_GPIO_Port GPIOF
#define IO15_Pin GPIO_PIN_3
#define IO15_GPIO_Port GPIOF
#define IO53_Pin GPIO_PIN_4
#define IO53_GPIO_Port GPIOF
#define IO17_Pin GPIO_PIN_5
#define IO17_GPIO_Port GPIOF
#define IO28_Pin GPIO_PIN_7
#define IO28_GPIO_Port GPIOF
#define IO27_Pin GPIO_PIN_8
#define IO27_GPIO_Port GPIOF
#define IO30_Pin GPIO_PIN_9
#define IO30_GPIO_Port GPIOF
#define IO18_Pin GPIO_PIN_10
#define IO18_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define IO11_Pin GPIO_PIN_0
#define IO11_GPIO_Port GPIOC
#define IO55_Pin GPIO_PIN_2
#define IO55_GPIO_Port GPIOC
#define IO13_Pin GPIO_PIN_3
#define IO13_GPIO_Port GPIOC
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOA
#define IO9_Pin GPIO_PIN_3
#define IO9_GPIO_Port GPIOA
#define IO64_Pin GPIO_PIN_4
#define IO64_GPIO_Port GPIOA
#define IO71_Pin GPIO_PIN_5
#define IO71_GPIO_Port GPIOA
#define IO69_Pin GPIO_PIN_6
#define IO69_GPIO_Port GPIOA
#define IO67_Pin GPIO_PIN_7
#define IO67_GPIO_Port GPIOA
#define IO37_Pin GPIO_PIN_0
#define IO37_GPIO_Port GPIOB
#define IO57_Pin GPIO_PIN_1
#define IO57_GPIO_Port GPIOB
#define IO49_Pin GPIO_PIN_2
#define IO49_GPIO_Port GPIOB
#define IO61_Pin GPIO_PIN_12
#define IO61_GPIO_Port GPIOF
#define IO60_Pin GPIO_PIN_13
#define IO60_GPIO_Port GPIOF
#define IO56_Pin GPIO_PIN_14
#define IO56_GPIO_Port GPIOF
#define IO52_Pin GPIO_PIN_15
#define IO52_GPIO_Port GPIOF
#define IO33_Pin GPIO_PIN_0
#define IO33_GPIO_Port GPIOG
#define IO32_Pin GPIO_PIN_1
#define IO32_GPIO_Port GPIOG
#define IO46_Pin GPIO_PIN_7
#define IO46_GPIO_Port GPIOE
#define IO47_Pin GPIO_PIN_8
#define IO47_GPIO_Port GPIOE
#define IO59_Pin GPIO_PIN_9
#define IO59_GPIO_Port GPIOE
#define IO43_Pin GPIO_PIN_10
#define IO43_GPIO_Port GPIOE
#define IO58_Pin GPIO_PIN_11
#define IO58_GPIO_Port GPIOE
#define IO40_Pin GPIO_PIN_12
#define IO40_GPIO_Port GPIOE
#define IO54_Pin GPIO_PIN_13
#define IO54_GPIO_Port GPIOE
#define IO39_Pin GPIO_PIN_14
#define IO39_GPIO_Port GPIOE
#define IO38_Pin GPIO_PIN_15
#define IO38_GPIO_Port GPIOE
#define IO36_Pin GPIO_PIN_10
#define IO36_GPIO_Port GPIOB
#define IO34_Pin GPIO_PIN_11
#define IO34_GPIO_Port GPIOB
#define ID1_Pin GPIO_PIN_12
#define ID1_GPIO_Port GPIOB
#define ID2_Pin GPIO_PIN_13
#define ID2_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define ID3_Pin GPIO_PIN_15
#define ID3_GPIO_Port GPIOB
#define STLK_RX_Pin GPIO_PIN_8
#define STLK_RX_GPIO_Port GPIOD
#define STLK_TX_Pin GPIO_PIN_9
#define STLK_TX_GPIO_Port GPIOD
#define IO42_Pin GPIO_PIN_11
#define IO42_GPIO_Port GPIOD
#define IO44_Pin GPIO_PIN_12
#define IO44_GPIO_Port GPIOD
#define IO45_Pin GPIO_PIN_13
#define IO45_GPIO_Port GPIOD
#define IO65_Pin GPIO_PIN_14
#define IO65_GPIO_Port GPIOD
#define IO63_Pin GPIO_PIN_15
#define IO63_GPIO_Port GPIOD
#define IO6_Pin GPIO_PIN_2
#define IO6_GPIO_Port GPIOG
#define IO7_Pin GPIO_PIN_3
#define IO7_GPIO_Port GPIOG
#define IO41_Pin GPIO_PIN_4
#define IO41_GPIO_Port GPIOG
#define USB_PowerSwitchOn_Pin GPIO_PIN_6
#define USB_PowerSwitchOn_GPIO_Port GPIOG
#define USB_OverCurrent_Pin GPIO_PIN_7
#define USB_OverCurrent_GPIO_Port GPIOG
#define ID5_Pin GPIO_PIN_6
#define ID5_GPIO_Port GPIOC
#define IO70_Pin GPIO_PIN_7
#define IO70_GPIO_Port GPIOC
#define IO0_Pin GPIO_PIN_8
#define IO0_GPIO_Port GPIOC
#define IO1_Pin GPIO_PIN_9
#define IO1_GPIO_Port GPIOC
#define USB_SOF_Pin GPIO_PIN_8
#define USB_SOF_GPIO_Port GPIOA
#define USB_VBUS_Pin GPIO_PIN_9
#define USB_VBUS_GPIO_Port GPIOA
#define USB_ID_Pin GPIO_PIN_10
#define USB_ID_GPIO_Port GPIOA
#define USB_DM_Pin GPIO_PIN_11
#define USB_DM_GPIO_Port GPIOA
#define USB_DP_Pin GPIO_PIN_12
#define USB_DP_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ID0_Pin GPIO_PIN_15
#define ID0_GPIO_Port GPIOA
#define IO2_Pin GPIO_PIN_10
#define IO2_GPIO_Port GPIOC
#define IO3_Pin GPIO_PIN_11
#define IO3_GPIO_Port GPIOC
#define IO4_Pin GPIO_PIN_12
#define IO4_GPIO_Port GPIOC
#define IO29_Pin GPIO_PIN_0
#define IO29_GPIO_Port GPIOD
#define IO31_Pin GPIO_PIN_1
#define IO31_GPIO_Port GPIOD
#define IO5_Pin GPIO_PIN_2
#define IO5_GPIO_Port GPIOD
#define IO16_Pin GPIO_PIN_3
#define IO16_GPIO_Port GPIOD
#define IO14_Pin GPIO_PIN_4
#define IO14_GPIO_Port GPIOD
#define IO12_Pin GPIO_PIN_5
#define IO12_GPIO_Port GPIOD
#define IO10_Pin GPIO_PIN_6
#define IO10_GPIO_Port GPIOD
#define IO8_Pin GPIO_PIN_7
#define IO8_GPIO_Port GPIOD
#define IO48_Pin GPIO_PIN_9
#define IO48_GPIO_Port GPIOG
#define IO50_Pin GPIO_PIN_14
#define IO50_GPIO_Port GPIOG
#define IO66_Pin GPIO_PIN_3
#define IO66_GPIO_Port GPIOB
#define IO62_Pin GPIO_PIN_4
#define IO62_GPIO_Port GPIOB
#define IO68_Pin GPIO_PIN_5
#define IO68_GPIO_Port GPIOB
#define IO51_Pin GPIO_PIN_6
#define IO51_GPIO_Port GPIOB
#define LD2_Pin GPIO_PIN_7
#define LD2_GPIO_Port GPIOB
#define ID6_Pin GPIO_PIN_8
#define ID6_GPIO_Port GPIOB
#define ID4_Pin GPIO_PIN_9
#define ID4_GPIO_Port GPIOB
#define IO35_Pin GPIO_PIN_0
#define IO35_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
