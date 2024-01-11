#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>

#include "Clock.h"

#include "PerifADC.h"


PerifADC::PerifADC(uint32_t port, uint32_t pins, uint32_t adc) 
    : m_ADC{adc}
{
    adc_power_off(m_ADC);

    gpio_mode_setup(port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, pins);
    
    /*rcc_periph_clock_enable(RCC_ADC1);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_reset_pulse(RST_ADC1);

    adc_disable_scan_mode(m_ADC);
    adc_set_right_aligned(m_ADC);

    adc_set_sample_time_on_all_channels(m_ADC, ADC_SMPR_SMP_3CYC);

    adc_set_regular_sequence(m_ADC, channel_lenght, (uint8_t*)chanlist);
    adc_set_resolution(m_ADC, ADC_RESOLUTION_12BIT);
    
    adc_enable_dma(m_ADC);
    
    adc_reset_calibration(m_ADC);
    adc_calibrate(m_ADC);*/
    
    adc_power_on(m_ADC);
}

void PerifADC::irqHandler()
{
    
}