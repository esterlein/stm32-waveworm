#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/systick.h>

#include "IO.h"
#include "Clock.h"


Clock::Clock(std::initializer_list<rcc_periph_clken> peripherals)
{
    rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

    systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
    
    STK_CVR = 0;
    
    systick_set_reload(rcc_ahb_frequency / 1000);
    systick_counter_enable();
    systick_interrupt_enable();

    // Initialize microsecond timer

    rcc_periph_clock_enable(RCC_TIM6);
    timer_set_prescaler(TIM6, rcc_apb1_frequency / 1000000 - 1);
    timer_set_period(TIM6, 0xFFFF);
    timer_one_shot_mode(TIM6);

    // Initialize peripheral clock

    for(rcc_periph_clken perif : peripherals) {
        rcc_periph_clock_enable(perif);
    }

    // rcc_periph_reset_pulse(RST_ADC1);
}

void Clock::msleep(uint32_t delay_ms)
{
    s_delay_timer = delay_ms;
    while(s_delay_timer);
}

void Clock::usleep(uint32_t delay_us)
{
    TIM_ARR(TIM6) = delay_us;
    TIM_EGR(TIM6) = TIM_EGR_UG;
    TIM_CR1(TIM6) |= TIM_CR1_CEN;
    while(TIM_CR1(TIM6) & TIM_CR1_CEN);
}

uint32_t Clock::mtime() const
{
    return s_system_ms;
}

void Clock::irqHandler()
{
    ++s_system_ms;
    if(s_delay_timer)
        --s_delay_timer;
}