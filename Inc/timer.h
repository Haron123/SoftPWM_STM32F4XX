#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "stm32f4xx_hal.h"


#define MAX_TIME ((1ULL << (sizeof(tTime) * 8)) - 1)

#define TIMER2_CLOCK SystemCoreClock
#define TIMER2_PRESCALER 0

#if TIMER2_PRESCALER > 0
#define TIMER2_SECOND (TIMER2_CLOCK / TIMER2_PRESCALER)
#else
#define TIMER2_SECOND (TIMER2_CLOCK)
#endif

#define TIMER2_MILLISECOND (TIMER2_SECOND / 1000)
#define TIMER2_MICROSECOND (TIMER2_MILLISECOND / 1000)


// KEEP THIS UPDATED IF YOU CHANGE THE CONFIG : 
// Current settings suggest an overflow occurs every 212 microseconds

// Simplifies the transition to different value ranges and aids in clarity
// tTime always represents ticks
typedef uint32_t tTime;

/**
 * @brief Initializes the system tick timer.
 * The system tick starts running as soon as this function is executed.
 * It is used to work with time without using an additional timer.
 */
void timer_init(void);

/**
 * @brief Converts a time in microseconds to system ticks.
 * @param us The time to be converted, specified in microseconds.
 * @retval The specified microseconds as system ticks.
 */
tTime timer_us_to_ticks(uint32_t us);

/**
 * @brief Converts a time in millisecond to system ticks.
 * @param ms The time to be converted, specified in millisecond.
 * @retval The specified millisecond as system ticks.
 */
tTime timer_ms_to_ticks(uint32_t ms);

/**
 * @brief Pauses the system for the specified amount of time.
 * @param us The time to wait, specified in microseconds.
 * @retval None
 */
void timer_delay_us(uint32_t time);

/**
 * @brief Pauses the system for the specified amount of time.
 * @param ms The time to wait, specified in millisecond.
 * @retval None
 */
void timer_delay_ms(uint32_t time);

/**
 * @brief Retrieves the current value of the system tick and returns it.
 * @retval The current value of the system tick.
 */
tTime timer_get_ticks();

/**
 * @brief Compares the current time to a specified time.
 * @retval The time to be compared.
 */
tTime timer_time_passed(tTime since);

#endif
