#include "task_gpio.h"

// IO pin mapping table
static const GPIO_Pin_t IO_PINS[] = {
    {GPIOC, 8},  // IO0
    {GPIOC, 9},  // IO1
    {GPIOC, 10}, // IO2
    {GPIOC, 11}, // IO3
    {GPIOC, 12}, // IO4
    {GPIOD, 2},  // IO5
    {GPIOG, 2},  // IO6
    {GPIOG, 3},  // IO7
    {GPIOD, 7},  // IO8
    {GPIOA, 3},  // IO9
    {GPIOD, 6},  // IO10
    {GPIOC, 0},  // IO11
    {GPIOD, 5},  // IO12
    {GPIOC, 3},  // IO13
    {GPIOD, 4},  // IO14
    {GPIOF, 3},  // IO15
    {GPIOD, 3},  // IO16
    {GPIOF, 5},  // IO17
    {GPIOF, 10}, // IO18
    {GPIOE, 2},  // IO19
    {GPIOE, 4},  // IO20
    {GPIOE, 5},  // IO21
    {GPIOF, 2},  // IO22
    {GPIOE, 6},  // IO23
    {GPIOF, 1},  // IO24
    {GPIOE, 3},  // IO25
    {GPIOF, 0},  // IO26
    {GPIOF, 8},  // IO27
    {GPIOF, 7},  // IO28
    {GPIOD, 0},  // IO29
    {GPIOF, 9},  // IO30
    {GPIOD, 1},  // IO31
    {GPIOG, 1},  // IO32
    {GPIOG, 0},  // IO33
    {GPIOB, 11}, // IO34
    {GPIOE, 0},  // IO35
    {GPIOB, 10}, // IO36
    {GPIOB, 0},  // IO37
    {GPIOE, 15}, // IO38
    {GPIOE, 14}, // IO39
    {GPIOE, 12}, // IO40
    {GPIOG, 4},  // IO41
    {GPIOD, 11}, // IO42
    {GPIOE, 10}, // IO43
    {GPIOD, 12}, // IO44
    {GPIOD, 13}, // IO45
    {GPIOE, 7},  // IO46
    {GPIOE, 8},  // IO47
    {GPIOG, 9},  // IO48
    {GPIOB, 2},  // IO49
    {GPIOG, 14}, // IO50
    {GPIOB, 6},  // IO51
    {GPIOF, 15}, // IO52
    {GPIOF, 4},  // IO53
    {GPIOE, 13}, // IO54
    {GPIOC, 2},  // IO55
    {GPIOF, 14}, // IO56
    {GPIOB, 1},  // IO57
    {GPIOE, 11}, // IO58
    {GPIOE, 9},  // IO59
    {GPIOF, 13}, // IO60
    {GPIOF, 12}, // IO61
    {GPIOB, 4},  // IO62
    {GPIOD, 15}, // IO63
    {GPIOA, 4},  // IO64
    {GPIOD, 14}, // IO65
    {GPIOB, 3},  // IO66
    {GPIOA, 7},  // IO67
    {GPIOB, 5},  // IO68
    {GPIOA, 6},  // IO69
    {GPIOC, 7},  // IO70
    {GPIOA, 5},  // IO71
};

/**
 * @brief (private) Configure a single pin as input with pull-down
 *
 * @param port
 * @param pin
 */

static GPIO_Pin_t get_port_and_pin_from_io_number(uint8_t io_number)
{
    return IO_PINS[io_number];
}

static void configure_pin_input_pulldown(GPIO_Pin_t gpio)
{
    GPIO_TypeDef *port = gpio.port;
    uint8_t pin = gpio.pin;

    // Set mode to input (00)
    port->MODER &= ~(0x3 << (pin * 2));

    // Set pull-down resistor (10)
    port->PUPDR &= ~(0x3 << (pin * 2));
    port->PUPDR |= (0x2 << (pin * 2));
}

// Configure a single pin as output push-pull
static void configure_pin_output_high(GPIO_Pin_t gpio)
{
    GPIO_TypeDef *port = gpio.port;
    uint8_t pin = gpio.pin;

    // Set mode to output (01)
    port->MODER &= ~(0x3 << (pin * 2));
    port->MODER |= (0x1 << (pin * 2));

    // Set output type to push-pull (0)
    port->OTYPER &= ~(0x1 << pin);

    // Set speed to medium (01) - adjust as needed
    port->OSPEEDR &= ~(0x3 << (pin * 2));
    port->OSPEEDR |= (0x0 << (pin * 2));

    // No pull-up/pull-down (00)
    port->PUPDR &= ~(0x3 << (pin * 2));

    // Set pin to output state HIGH
    port->BSRR = (1 << pin);
}

uint8_t GPIO_GetID()
{
    uint8_t id = 255;
    id = HAL_GPIO_ReadPin(ID0_GPIO_Port, ID0_Pin);       // 1
    id += HAL_GPIO_ReadPin(ID1_GPIO_Port, ID1_Pin) << 1; // 2
    id += HAL_GPIO_ReadPin(ID2_GPIO_Port, ID2_Pin) << 2; // 4
    id += HAL_GPIO_ReadPin(ID3_GPIO_Port, ID3_Pin) << 3; // 8
    id += HAL_GPIO_ReadPin(ID4_GPIO_Port, ID4_Pin) << 4; // 16
    id += HAL_GPIO_ReadPin(ID5_GPIO_Port, ID5_Pin) << 5; // 32
    id += HAL_GPIO_ReadPin(ID6_GPIO_Port, ID6_Pin) << 6; // 64
    return id;
}

/**
 * @brief Sets a circuit card pin (from 1-72) to OUTPUT HIGH
 *
 * @param io_number
 */
void GPIO_SetOutput(uint8_t io_number)
{
    configure_pin_output_high(get_port_and_pin_from_io_number(io_number - 1));
}

void GPIO_BlinkLED(uint8_t blink_led_x_times)
{
    static uint32_t last_blink_time = 0;
    static uint8_t led_blink_counter = 0;
    static uint8_t busy_flag = 0;
    if (blink_led_x_times > 0 && !busy_flag)
    {
        led_blink_counter = blink_led_x_times * 2;
        busy_flag = 1;
    }
    if (HAL_GetTick() - 50 > last_blink_time && led_blink_counter > 0)
    {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        last_blink_time = HAL_GetTick();
        led_blink_counter--;
        if (led_blink_counter < 1)
        {
            busy_flag = 0;
        }
    }
}

/**
 * @brief Set all GPIO pins to input mode with pulldown
 *
 */
void GPIO_SetAllInputs()
{
    // Set all pins to input with pulldown
    for (uint8_t i = 0; i < NUM_IO_PINS; i++)
    {
        configure_pin_input_pulldown(IO_PINS[i]);
    }
}

/**
 * @brief Read all IO pins and return their states in an array
 *
 * @param states
 */
void GPIO_ReadAllPins(uint8_t *states)
{
    for (uint8_t i = 0; i < NUM_IO_PINS; i++)
    {
        GPIO_TypeDef *port = IO_PINS[i].port;
        uint8_t pin = IO_PINS[i].pin;

        states[i] = (port->IDR & (1 << pin)) ? 1 : 0;
    }
}