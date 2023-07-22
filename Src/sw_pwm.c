#include "sw_pwm.h"

// Array to keep track of the Pins and add a
// Limit to it, knowing the hardware.
// If anyone ever sees this and thinks this is a horrible
// Idea, tell me
volatile static PwmPin* sw_pwm_module_array[SW_PWM_MAX_PINS];
volatile static uint32_t sw_pwm_array_index;

static void sw_pwm_update_pin(PwmPin* pwmpin);
static void sw_pwm_update_all();

void TIM3_IRQHandler(void)
{
    TIM3->SR &= ~(1 << TIM_SR_UIF);
    sw_pwm_update_all();
}

/**
 * @brief Updates a specific pwm_pin, only should be
 * used by sw_pwm_update_all()
 * @param pwmpin, the pwmpin thats to update
*/
static void sw_pwm_update_pin(PwmPin* pwmpin)
{
    // Since this function only gets called by
    // sw_pwm_update_all(), which doesnt accept extra parameters
    // and sw_pwm_add_pin() ensures the pwmpins in the list
    // arent NULL, we can save the error_handling here
    // Since this needs to be super fast
    // Pls optimize it if you have ideas :D

    tTime passed_time = timer_time_passed(pwmpin->last_update);
    GPIO_TypeDef* port = pwmpin->port;

    // If already past the period time set the pin high
    if(passed_time >= pwmpin->pwm_period)
    {
        port->BSRR = (1 << pwmpin->pin);
        pwmpin->last_update = timer_get_ticks();
    }
    // If not past the period time but past the high period
    // set the pin low
    else if(passed_time >= pwmpin->high_period)
    {
        port->BSRR = (1 << (pwmpin->pin + 16));
    }
}

/**
 * @brief iterates through all added Pwm Pins and
 * updates their status
*/
static void sw_pwm_update_all()
{
    for(uint8_t i = 0; i < sw_pwm_array_index; i++)
    {
        PwmPin* current_pin = sw_pwm_module_array[i];
        
        sw_pwm_update_pin(current_pin);
    }
}


void sw_pwm_init(void)
{
    __disable_irq();

    // Init Timer3
    __HAL_RCC_TIM3_CLK_ENABLE();
    TIM3->CR1 = 0;
    TIM3->CR2 = 0;
    TIM3->PSC = TIMER3_PRESCALER;
    TIM3->ARR = SW_PWM_POLL_TIME * TIMER3_MICROSECOND;
    TIM3->DIER = 0;
    TIM3->EGR = TIM_EGR_UG;
    TIM3->CR1 = TIM_CR1_CEN;

    // Init Timer3 to interrupt at Overflow
    TIM3->CR1 |= (1 << TIM_CR1_URS);
    TIM3->DIER |= (1 << TIM_DIER_UIE);

    HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(TIM3_IRQn);

    __enable_irq();
}

PwmPin sw_pwm_create_pin(GPIO_TypeDef* port, uint8_t pin, uint32_t freq, uint8_t duty_cycle)
{
    if(port == NULL)
    {
        ERROR_HANDLER("Port is null");
    }
    else if(pin > 15)
    {
        ERROR_HANDLER("Invalid Pin, each Port only has PIN0-PIN15");
    } 
    else if(duty_cycle > 100)
    {
        ERROR_HANDLER("Duty cycle has to be 0-100");
    }
    else if(freq > (SystemCoreClock / 100))
    {
        WARNING_HANDLER("Set Frequency might be too high to handle");
    }

    // due to calculating with ticks we convert it first
    uint32_t pwm_period = (TIMER2_SECOND / freq);

    // duty_cycle parameter is already received 100 times larger
    // than the percentage, so we just calculate with that and
    // divide at the end
    uint32_t high_period = (pwm_period * duty_cycle) / 100;

    PwmPin temp;
    temp.port = port;
    temp.pin = pin;
    temp.pwm_period = pwm_period;
    temp.high_period = high_period;
    temp.last_update = 0;

    return temp;
}

void sw_pwm_change_freq(PwmPin* pwmpin, uint32_t new_freq)
{
    if(pwmpin == NULL)
    {
        ERROR_HANDLER("pwmpin is null");
    }
    else if(new_freq > (SystemCoreClock / 100))
    {
        WARNING_HANDLER("Set Frequency might be too high to handle");
    }

    // due to calculating with ticks we convert it first
    uint32_t pwm_period = (TIMER2_SECOND / new_freq);

    pwmpin->pwm_period = pwm_period;
}

void sw_pwm_change_duty_cycle(PwmPin* pwmpin, uint8_t new_duty_cycle)
{   
    if(pwmpin == NULL)
    {
        ERROR_HANDLER("pwmpin is null");
    }
    else if(new_duty_cycle > 100)
    {
        ERROR_HANDLER("Duty cycle has to be 0-100");
    }

    // duty_cycle parameter is already received 100 times larger
    // than the percentage, so we just calculate with that and
    // divide at the end
    uint32_t high_period = (pwmpin->pwm_period * new_duty_cycle) / 100;

    pwmpin->high_period = high_period;
}

void sw_pwm_add_pin(PwmPin* pwmpin)
{
    if(pwmpin == NULL)
    {
        ERROR_HANDLER("pwmpin is null");
    }
    else if(sw_pwm_array_index == SW_PWM_MAX_PINS)
    {
        WARNING_HANDLER("Trying to add more pwmpins than possible, try to increase SW_PWM_MAX_PINS");
    }
    else
    {
        for(uint8_t i = 0; i < sw_pwm_array_index; i++)
        {
            if(sw_pwm_module_array[i] == pwmpin)
            {
                WARNING_HANDLER("Trying to add a pwmpin thats already added");
                return;
            }
        }
        sw_pwm_module_array[sw_pwm_array_index] = pwmpin;
        sw_pwm_array_index++;
    }
}