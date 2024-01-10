#include "PerifBase.h"


namespace ISR
{
    inline constexpr int ADC1_NDX   = 0;
    inline constexpr int USART1_NDX = 1;

    struct IRQDescriptor
    {
        PerifBase* instance = nullptr;
        int irq_type{0};
    }
    irq_array[16];
}

// libopencm-generated symbols should not be touched by g++
extern "C" void adc1_isr();
extern "C" void usart1_isr();