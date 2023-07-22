#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "stm32f4xx_hal.h"
#include "gpio_helper.h"

// You can turn these off to save codespace or processing power
// By setting them to 0
#define ERROR_HANDLING 1
#define WARNING_HANDLING 1

// Only use this function for fatal errors, runtime warnings should be
// Handled differently
#if ERROR_HANDLING == 1
#define ERROR_HANDLER(msg) error_handler(msg, sizeof(msg), __FILE__, __LINE__)
#elif ERROR_HANDLING == 0
#define ERROR_HANDLER(msg) 
#endif

// Only use this function for hints at the programmer, incase something 
// Goes wrong that doesnt neccesarily break the system
#if WARNING_HANDLING == 1
#define WARNING_HANDLER(msg) warning_handler(msg, sizeof(msg), __FILE__, __LINE__)
#elif WARNING_HANDLING == 0
#define WARNING_HANDLER(msg) 
#endif

#define ERROR_LED_PORT GPIOC
#define ERROR_LED_PIN 13

// Do not use these 2 Functions directly, only call it over its macro
// Or do but thats more work for you and confuses everyone else
void error_handler(char* msg, uint32_t msg_len, char* file, uint32_t line);
void warning_handler(char* msg, uint32_t msg_len, char* file, uint32_t line);

#endif