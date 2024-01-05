#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#include "delay.h"


void delayInit(void)
{
	rcc_periph_clock_enable(RCC_TIM6);
	timer_set_prescaler(TIM6, rcc_apb1_frequency / 1000000 - 1);
	timer_set_period(TIM6, 0xffff);
	timer_one_shot_mode(TIM6);
}

void delayUs(uint16_t us)
{
	TIM_ARR(TIM6) = us;
	TIM_EGR(TIM6) = TIM_EGR_UG;
	TIM_CR1(TIM6) |= TIM_CR1_CEN;
	while (TIM_CR1(TIM6) & TIM_CR1_CEN);
}