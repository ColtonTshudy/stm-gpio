#include "task_main.h"
#include "task_gpio.h"

void Main_Setup()
{
    HAL_Delay(100);
    GPIO_BlinkLED(2);
}

void Main_Heartbeat()
{
    static uint32_t last_time = 0;
    if (HAL_GetTick() - 1000 > last_time)
    {
        HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
        last_time = HAL_GetTick();
    }
}

void Main_Loop()
{
    GPIO_BlinkLED(0);
    Main_Heartbeat();

    // BRINGUP CODE - CLICK USER BUTTON TO CYCLE THORUGH ALL GPIO
    // static int i = 0;
    // if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
    // {
    //     HAL_Delay(50);
    //     if (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
    //     {
    //         Debug("Hello USB!\r\n");
    //         i++;
    //         HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    //         GPIO_SetAllInputs();
    //         GPIO_SetOutput(i);``
    //         HAL_Delay(100);
    //         HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    //         if (i > 72)
    //         {
    //             i = 0;
    //         }
    //     }
    //     while (HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin))
    //     {
    //     }
    // }
}
