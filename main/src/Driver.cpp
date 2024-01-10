#include "Interrupt.h"
#include "Driver.h"


namespace Driver
{
    PerifLCD& getLCD() {
        static PerifLCD lcd;
        return lcd;
    }
    PerifADC& getADC1() {
        static PerifADC adc{GPIOA, GPIO0, ADC1};
        ISR::irq_array[ISR::ADC1_NDX].instance = &adc;
        return adc;
    }
    PerifConsole& getUSART1() {
        static PerifConsole usart{GPIOA, GPIO9 | GPIO10, USART1, 115200, 8};
        ISR::irq_array[ISR::USART1_NDX].instance = &usart;
        return usart;
    }
}