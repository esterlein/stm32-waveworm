#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>


static void clockInit(void)
{
	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
}

static void gpioInit(void)
{
	rcc_periph_clock_enable(RCC_GPIOG);
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
}

static void buttonInit(void)
{
	rcc_periph_clock_enable(RCC_GPIOA);
	gpio_mode_setup(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_NONE, GPIO0);
}

int main(void)
{
    clockInit();
    gpioInit();
    buttonInit();

    int wait_count;
    while(1){
        
		gpio_toggle(GPIOG, GPIO13);

		if(gpio_get(GPIOA, GPIO0)){
			for(wait_count = 0; wait_count < 3000000; ++wait_count){
				__asm__("nop");
			}
		}

		for(wait_count = 0; wait_count < 3000000; ++wait_count){
			__asm__("nop");
		}
	}
    
    return 0;
}