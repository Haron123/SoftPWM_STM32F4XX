#ifndef SW_PWM_H
#define SW_PWM_H

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "timer.h"
#include "error_handler.h"

/* TIMER CONFIG */
#define TIMER3_CLOCK SystemCoreClock
#define TIMER3_PRESCALER 0

#if TIMER3_PRESCALER > 0
    #define TIMER3_SECOND (TIMER3_CLOCK / TIMER3_PRESCALER)
#else
    #define TIMER3_SECOND (TIMER3_CLOCK)
#endif

#define TIMER3_MILLISECOND (TIMER3_SECOND / 1000)
#define TIMER3_MICROSECOND (TIMER3_MILLISECOND / 1000)
/* TIMER CONFIG */

// Due to each added Pin slowing down the system
// the maximum should be determined
#define SW_PWM_MAX_PINS 5

// The Time it waits before
// The Interrupt updates the Pwm Pins
// Lower numbers make the PWM more accurate butS
// slow down the overall system
// Time is given in Microseconds
#define SW_PWM_POLL_TIME 100

/*s
pwm_period is the period of the pwm, determining the frequency
duty cycle is the period of the pwm_period where the pin should be high
lasT_update keeps track of the updates it got
*/
typedef struct PwmPin
{
    GPIO_TypeDef* port;
    uint8_t pin;

    tTime high_period;
    tTime pwm_period;
    tTime last_update;
} PwmPin;

/**
 * @brief sets the Timer and Interrupt used to control the Pwm Pins
*/
void sw_pwm_init(void);

/**
 * @brief Creates a PWM Pin, automatically calculates the pwm_period
 * and high_period with the given parameters
 * 
 * @param port the Port the pwm pin is on
 * @param pin the pin you wanna pulse
 * @param freq the frequency of the signal. Be aware of the 
 * upper frequency limit set in the macros
 * @param duty_cycle the percentage of the time, the Pin is High
 * can be 0-100 representing 0% to 100%. Be aware of the 
 * lower duty_cycle limit set in the macros
*/
PwmPin sw_pwm_create_pin(GPIO_TypeDef* port, uint8_t pin, uint32_t freq, uint8_t duty_cycle);

/**
 * @brief changes the frequency of a created pwm_pin, automatically
 * calculates the pwm_period
 * 
 * @param pwmpin the PwmPin you want to change the frequency of
 * @param new_freq the new frequency to set the pwmpin to
*/
void sw_pwm_change_freq(PwmPin* pwmpin, uint32_t new_freq);

/**
 * @brief changes the duty_cycle of a created pwm_pin, automatically
 * calculates the high_period
 * 
 * @param pwmpin the PwmPin you want to change the frequency of
 * @param new_duty_cycle the new duty_cycle to set the pwmpin to
*/
void sw_pwm_change_duty_cycle(PwmPin* pwmpin, uint8_t new_duty_cycle);

/**
 * @brief adds the specified pin to the Modules Array of pins,
 * that get iterated through, the more pins you add the more time
 * it needs to iterate, adding to the system latency.
 * Be aware of the maximum amount of allowed Pins.
 * 
 * @param pwmpin the PwmPin you wanna add to the Array
*/
void sw_pwm_add_pin(PwmPin* pwmpin);

#endif