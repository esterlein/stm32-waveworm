#pragma once

#include "PerifBase.h"


namespace ISR
{
    inline constexpr int CLOCK_NDX  = 0;
    inline constexpr int ADC1_NDX   = 1;
    inline constexpr int USART1_NDX = 2;

    inline static struct IRQDescriptor
    {
        PerifBase* instance = nullptr;
        int irq_type{0};
    }
    irq_array[16];
}

// libopencm-generated symbols should not be touched by g++
extern "C" void adc1_isr();
extern "C" void usart1_isr();
extern "C" void sys_tick_handler();