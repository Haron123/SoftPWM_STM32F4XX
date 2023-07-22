#include "timer.h"

void timer_init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();
    TIM2->CR1 = 0;
    TIM2->CR2 = 0;
    TIM2->PSC = TIMER2_PRESCALER;
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->DIER = 0;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->CR1 = TIM_CR1_CEN;
}

inline tTime timer_get_ticks()
{
    return TIM2->CNT;
}

tTime timer_us_to_ticks(uint32_t us)
{
    return (us * TIMER2_MICROSECOND);
}

tTime timer_ms_to_ticks(uint32_t ms)
{
    return (ms * TIMER2_MILLISECOND);
}

void timer_delay_us(uint32_t time)
{
    tTime now = timer_get_ticks();
    time = timer_us_to_ticks(time);

    while(timer_time_passed(now) < time)
    {
        // do nothing
    }
}

void timer_delay_ms(uint32_t time)
{
    tTime now = timer_get_ticks();
    time = timer_ms_to_ticks(time);

    while(timer_time_passed(now) < time)
    {
        // do nothing
    }
}


tTime timer_time_passed(tTime since)
{
    tTime now = timer_get_ticks();

	if(now >= since)
	{
		return (now - since);
	}
	else
	{
		// rollover has occured
		return (now + (1 + MAX_TIME - since));
	}
}