#include <initializer_list>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "Clock.h"

#include "PerifLCD.h"
#include "PerifADC.h"
#include "PerifConsole.h"

#include "IO.h"
#include "Interrupt.h"


namespace IO
{
    Clock& getClock() {
        static Clock clock(std::initializer_list<rcc_periph_clken>{
                           static_cast<rcc_periph_clken>(
                           RCC_GPIOA | RCC_GPIOB | RCC_GPIOC | RCC_GPIOD |
                           RCC_GPIOE | RCC_GPIOF | RCC_GPIOG),
                           RCC_FSMC,
                           RCC_SPI5,
                           RCC_ADC1});
        ISR::clockInterruptHandler = std::bind(&Clock::irqHandler, &clock);
        return clock;
    }
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