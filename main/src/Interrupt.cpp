#include "Interrupt.h"


void adc1_isr()
{
    ISR::irq_array[ISR::ADC1_NDX].instance->irqHandler();
}

void usart1_isr()
{
	ISR::irq_array[ISR::USART1_NDX].instance->irqHandler();
}