#ifndef GPIO_HELPER_H
#define GPIO_HELPER_H

#include "stm32f4xx_hal.h"
#include "error_handler.h"

#ifndef NULL
#define NULL 0
#endif

// Defines for the Port mode register
#define INPUT 0
#define OUTPUT 1
#define ALTERNATE 2
#define ANALOG 3

// Defines for the output type register
#define PUSH_PULL 0
#define OPEN_DRAIN 1

// Defines for output speed register
#define LOW_SPEED 0
#define MEDIUM_SPEED 1
#define HIGH_SPEED 2
#define VERY_HIGH_SPEED 3

// Defines for pullup/pulldown register setup
#define NO_PULL 0
#define PULL_UP 1
#define PULL_DOWN 2
#define RESERVED 3

/**
 * @brief sets up the a gpio in a basic way, by just telling it to be an input or output
 * Non specified registers will get the following default values :
 * PURPDR / Pull-Type will be No Pull, meaning its left floating
 * OTYPER / Output-Type will be Push-Pull
 * OSPEEDR / Output-Speed will be Low Speed
 * 
 * @param port, GPIO_Typedef port from the STM32 HAL
 * @param pin, the pin thats to configure
 * @param port_mode, can either be OUTPUT or INPUT to indicate the mode for the pin
*/
void gpio_setup_basic(GPIO_TypeDef* port, uint16_t pin, uint8_t port_mode);

/**
 * @brief sets up the a gpio in a simple way
 * Non specified registers will get the following default values :
 * OTYPER / Output-Type will be Push-Pull
 * OSPEEDR / Output-Speed will be Low Speed
 * 
 * @param port, GPIO_Typedef port from the STM32 HAL
 * @param pin, the pin thats to configure
 * @param port_mode, can either be OUTPUT or INPUT to indicate the mode for the pin
 * @param pull_type, can either be NO_PULL, PULL_UP, PULL_DOWN to indicate the pull_type for the pin
*/
void gpio_setup_normal(GPIO_TypeDef* port, uint16_t pin, uint8_t port_mode, uint8_t pull_type);

/**
 * @brief sets up the a gpio fully
 * @param port, GPIO_Typedef port from the STM32 HAL
 * @param pin, the pin thats to configure
 * @param port_mode, can either be OUTPUT or INPUT to indicate the mode for the pin
 * @param pull_type, can either be NO_PULL, PULL_UP, PULL_DOWN to indicate the pull_type for the pin
 * @param speed, choose between LOW_SPEED, MEDIUM_SPEED, HIGH_SPEED, VERY_HIGH_SPEED to indicate
 * the speed of the pin
*/
void gpio_setup_full(GPIO_TypeDef* port, uint16_t pin, uint8_t port_mode, uint8_t pull_type, uint8_t output_type, uint8_t speed);

#endif



