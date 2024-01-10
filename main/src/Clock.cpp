#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/systick.h>

#include "Clock.h"


namespace CLOCK
{
	static volatile uint32_t system_millis;
	static volatile uint32_t delay_timer;

	void delayInit()
	{
		rcc_periph_clock_enable(RCC_TIM6);
		timer_set_prescaler(TIM6, rcc_apb1_frequency / 1000000 - 1);
		timer_set_period(TIM6, 0xFFFF);
		timer_one_shot_mode(TIM6);
	}

	void clockInit()
	{
		rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

		systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
		
		STK_CVR = 0;
		
		systick_set_reload(rcc_ahb_frequency / 1000);
		systick_counter_enable();
		systick_interrupt_enable();

		delayInit();
	}

	void delayUs(uint32_t us)
	{
		TIM_ARR(TIM6) = us;
		TIM_EGR(TIM6) = TIM_EGR_UG;
		TIM_CR1(TIM6) |= TIM_CR1_CEN;
		while (TIM_CR1(TIM6) & TIM_CR1_CEN);
	}

	void msleep(uint32_t delay)
	{
		delay_timer = delay;
		while(delay_timer);
	}

	uint32_t mtime()
	{
		return system_millis;
	}
}

// interrupt
extern "C" void sys_tick_handler()
{
	++CLOCK::system_millis;
	if(CLOCK::delay_timer > 0) {
		--CLOCK::delay_timer;
	}
}