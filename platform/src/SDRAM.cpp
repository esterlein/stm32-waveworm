#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/fsmc.h>

#include "Clock.h"

#include "SDRAM.h"


namespace SDRAM
{
    static constexpr struct {
        uint32_t port;
        uint16_t pins;
    }
    sdram_pins[6] = {

        {GPIOB, GPIO5 | GPIO6},
        {GPIOC, GPIO0},
        {GPIOD, GPIO0 | GPIO1 | GPIO8 | GPIO9 | GPIO10 | GPIO14 | GPIO15},
        {GPIOE, GPIO0 | GPIO1 | GPIO7 | GPIO8 | GPIO9  | GPIO10 | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15},
        {GPIOF, GPIO0 | GPIO1 | GPIO2 | GPIO3 | GPIO4  | GPIO5  | GPIO11 | GPIO12 | GPIO13 | GPIO14 | GPIO15},
        {GPIOG, GPIO0 | GPIO1 | GPIO4 | GPIO5 | GPIO8  | GPIO15}
    };

    static constexpr struct sdram_timing timing = {
        
        .trcd = 2,	/* RCD Delay */
        .trp  = 2,	/* RP Delay */
        .twr  = 2,	/* Write Recovery Time */
        .trc  = 7,	/* Row Cycle Delay */
        .tras = 4,	/* Self Refresh Time */
        .txsr = 7,	/* Exit Self Refresh Time */
        .tmrd = 2,	/* Load to Active Delay */
    };
}

void SDRAM::initSDRAM()
{
    for(auto gpio : sdram_pins) {
        gpio_mode_setup(gpio.port, GPIO_MODE_AF, GPIO_PUPD_NONE, gpio.pins);
        gpio_set_output_options(gpio.port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, gpio.pins);
        gpio_set_af(gpio.port, GPIO_AF12, gpio.pins);
    }

    uint32_t ctrl_reg, timg_reg;

    ctrl_reg  = FMC_SDCR_RPIPE_1CLK;
    ctrl_reg |= FMC_SDCR_SDCLK_2HCLK;
    ctrl_reg |= FMC_SDCR_CAS_3CYC;
    ctrl_reg |= FMC_SDCR_NB4;
    ctrl_reg |= FMC_SDCR_MWID_16b;
    ctrl_reg |= FMC_SDCR_NR_12;
    ctrl_reg |= FMC_SDCR_NC_8;

    FMC_SDCR1 |= ctrl_reg & FMC_SDCR_DNC_MASK;
    FMC_SDCR2  = ctrl_reg;

    timg_reg = sdram_timing(const_cast<struct sdram_timing*>(&timing));
    FMC_SDTR1 |= timg_reg & FMC_SDTR_DNC_MASK;
    FMC_SDTR2  = timg_reg;

    sdram_command(SDRAM_BANK2, SDRAM_CLK_CONF, 1, 0);

    Clock::msleep(1);

    sdram_command(SDRAM_BANK2, SDRAM_PALL, 1, 0);
    sdram_command(SDRAM_BANK2, SDRAM_AUTO_REFRESH, 4, 0);
    
    timg_reg = SDRAM_MODE_BURST_LENGTH_2            |
                SDRAM_MODE_BURST_TYPE_SEQUENTIAL    |
                SDRAM_MODE_CAS_LATENCY_3            |
                SDRAM_MODE_OPERATING_MODE_STANDARD  |
                SDRAM_MODE_WRITEBURST_MODE_SINGLE;

    sdram_command(SDRAM_BANK2, SDRAM_LOAD_MODE, 1, timg_reg);

    // Set the refresh timer register	

    FMC_SDRTR = 0x000002AB;
}