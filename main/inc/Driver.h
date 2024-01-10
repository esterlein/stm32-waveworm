#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>

#include "PerifLCD.h"
#include "PerifADC.h"
#include "PerifConsole.h"


namespace Driver
{
    PerifLCD& getLCD();
    
    PerifADC& getADC1();
    
    PerifConsole& getUSART1();
}

namespace D = Driver;