#include "main.h"
#include "usbd_cdc_if.h"
#include "task_gpio.h"
#include "task_usb.h"
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

extern USBD_HandleTypeDef hUsbDeviceFS;

// This function should be called from the CDC_Receive_FS function in usbd_cdc_if.c
void CDC_ReceiveCallback(uint8_t *buf, uint32_t len)
{
    ParseCommand(buf, len);
}

/**
 * @brief Extracts a 1 or 2 digit number from a string
 *
 * @param buf string
 * @return uint8_t
 */
uint8_t ExtractNumber(uint8_t *buf)
{
    uint8_t num;
    unsigned char possible_digits[] = {buf[0], buf[1], '\0'};
    if (isdigit(possible_digits[0]))
    {
        if (isdigit(possible_digits[1]))
        {
            // Extract the two ASCII characters into a number
            sscanf((char *)possible_digits, "%hhu", &num);
        }
        else
        {
            // Extract only the first ASCII character into a number, deleting the second character
            possible_digits[1] = '\0';
            sscanf((char *)possible_digits, "%hhu", &num);
        }
    }
    else
    {
        Error_Handler();
    }
    return num;
}

void ParseCommand(uint8_t *buf, uint32_t len)
{
    uint8_t rc = 99;
    uint32_t end_flag_len = strlen(END_FLAG);

    //-id
    if (strncmp((char *)buf, "-id", 3) == 0 && len == 3 + end_flag_len)
    {
        uint8_t id = GPIO_GetID();
        // Send back command success code with id
        rc = 1;
        uint8_t data[] = {id};
        SendResponse(rc, data, 1);
    }
    //-sp XX
    else if (strncmp((char *)buf, "-sp", 3) == 0 && len > 4 + end_flag_len)
    {
        // uint8_t io_number = ExtractNumber(buf + 4);
        uint8_t io_number = buf[4];
        GPIO_SetOutput(io_number);

        // Send back command success code with pin number confirmation
        rc = 1;
        uint8_t data[] = {io_number};
        SendResponse(rc, data, 1);
    }
    //-rst
    else if (strncmp((char *)buf, "-rst", 4) == 0 && len == 4 + end_flag_len)
    {
        GPIO_SetAllInputs();
        rc = 1;
        SendResponse(rc, NULL, 0);
    }
    //-blink
    else if (strncmp((char *)buf, "-blink", 6) == 0 && len == 6 + end_flag_len)
    {
        rc = 1;
        SendResponse(rc, NULL, 0);
        GPIO_BlinkLED(5);
    }
    //-led X (enable = 1, disable = 0)
    else if (strncmp((char *)buf, "-led", 4) == 0 && len == 6 + end_flag_len)
    {
        uint8_t led_state = buf[5];
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, led_state);
        rc = 1;
        uint8_t data[] = {led_state};
        SendResponse(rc, data, 1);
    }
    //-read
    else if (strncmp((char *)buf, "-read", 5) == 0 && len == 5 + end_flag_len)
    {
        uint8_t data[NUM_IO_PINS];
        GPIO_ReadAllPins(data);
        rc = 1;
        SendResponse(rc, data, NUM_IO_PINS);
    }
}

/**
 * @brief Generates and sends an outgoing message over USB
 *
 * @param status status code
 * @param data data to send within the message
 * @param len data buffer length
 */
void SendResponse(uint8_t status, uint8_t *data, uint16_t len)
{
    uint8_t response[MAX_BUFFER_LENGTH] = {0};
    response[0] = status;
    uint16_t respLen = 1;

    if (data != NULL && len > 0)
    {
        memcpy(&response[1], data, len);
        respLen += len;
    }

    char end_flag_string[] = END_FLAG;
    memcpy(&(response[respLen]), end_flag_string, strlen(END_FLAG)); // serial termination characters
    respLen += strlen(END_FLAG);

    CDC_Transmit_FS(response, respLen);
}

/**
 * @brief Pipes printf to USB_CDC
 *
 * @param file
 * @param ptr
 * @param len
 * @return int
 */
int _write(int file, char *ptr, int len)
{
    (void)file;
    CDC_Transmit_FS((uint8_t *)ptr, len);
    return len;
}

/**
 * @brief De-initalizes the USB peripheral
 *
 */
void Task_USBD_DeInit()
{
    // Stop USB device
    USBD_Stop(&hUsbDeviceFS);

    // Deinitialize USB device
    USBD_DeInit(&hUsbDeviceFS);

    // Disable USB interrupts (if you've set them up separately)
    HAL_NVIC_DisableIRQ(OTG_FS_IRQn); // or USB_LP_IRQn, depending on your specific STM32
}