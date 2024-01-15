#include <libopencm3/stm32/spi.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include "Clock.h"
#include "SDRAM.h"
#include "PerifConsole.h"

#include "PerifLCD.h"


namespace LCD_INIT
{
    static constexpr uint32_t SPI = SPI5;
    
    static constexpr uint8_t cmd_args[] = {

        0x00, 0x1B,
        0x0A, 0xA2,
        0x10,
        0x10,
        0x45, 0x15,
        0x90,
        0x08,
        0xC2,
        0x55,
        0x0A, 0xA7, 0x27, 0x04,
        0x00, 0x00, 0x00, 0xEF,
        0x00, 0x00, 0x01, 0x3F,
        0x01, 0x00, 0x00,
        0x01,
        0x0F, 0x29, 0x24, 0x0C, 0x0E,
        0x09, 0x4E, 0x78, 0x3C, 0x09,
        0x13, 0x05, 0x17, 0x11, 0x00,
        0x00, 0x16, 0x1B, 0x04, 0x11,
        0x07, 0x31, 0x33, 0x42, 0x05,
        0x0C, 0x0A, 0x28, 0x2F, 0x0F,
    };

    static constexpr LCD::Command init_array[] = {

        {   0, 0xB1, 2  },
        {   0, 0xB6, 2  },
        {   0, 0xC0, 1  },
        {   0, 0xC1, 1  },
        {   0, 0xC5, 2  },
        {   0, 0xC7, 1  },
        {   0, 0x36, 1  },
        {   0, 0xB0, 1  },
        {   0, 0x3A, 1  },
        {   0, 0xB6, 4  },
        {   0, 0x2A, 4  },
        {   0, 0x2B, 4  },
        {   0, 0xF6, 3  },
        { 200, 0x2C, 0  },
        {   0, 0x26, 1  },
        {   0, 0xE0, 15 },
        {   0, 0xE1, 15 },
        { 200, 0x11, 0  },
        {   0, 0x29, 0  },
        {   0,    0, 0  }
    };
}

PerifLCD::PerifLCD()
    : m_curr_frame{nullptr}
    , m_display_frame{nullptr}
{
    gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO2);
    gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);

    gpio_mode_setup(GPIOF, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO7 | GPIO9);
    gpio_set_af(GPIOF, GPIO_AF5, GPIO7 | GPIO9);

    m_curr_frame = reinterpret_cast<uint16_t*>(SDRAM_BASE_ADDRESS);
    m_display_frame = m_curr_frame + LCD::FRAME_SIZE;
    
    spi_init_master(LCD_INIT::SPI, SPI_CR1_BAUDRATE_FPCLK_DIV_4,
                    SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
                    SPI_CR1_CPHA_CLK_TRANSITION_1,
                    SPI_CR1_DFF_8BIT,
                    SPI_CR1_MSBFIRST);
    
    spi_enable_ss_output(LCD_INIT::SPI);
    spi_enable(LCD_INIT::SPI);

    int offset = 0;

    for(auto command : LCD_INIT::init_array) {
        
        spiCommand(command, &LCD_INIT::cmd_args[offset]);
        
        offset += command.n_args;
    }

    testImage();
    showFrame();
}

void PerifLCD::spiCommand(const LCD::Command& command, const uint8_t* args)
{
    gpio_clear(GPIOC, GPIO2);
    (void) spi_xfer(LCD_INIT::SPI, command.cmd);

    uint32_t n_args = command.n_args;
    
    if(n_args) {
        gpio_set(GPIOD, GPIO13);

        for(uint32_t i = 0; i < n_args; ++i) {
            (void) spi_xfer(LCD_INIT::SPI, *(args + i));
        }
    }
    gpio_set(GPIOC, GPIO2);
    gpio_clear(GPIOD, GPIO13);
    
    if(command.delay) {
        Clock::msleep(command.delay);
    }
}

// Optimize with DMA 

void PerifLCD::drawPixel(int x, int y, uint16_t color)
{
    if(x >= LCD::WIDTH || y >= LCD::HEIGHT) return;
    *(m_curr_frame + x + y * LCD::WIDTH) = color;
}

void PerifLCD::showFrame()
{
    uint16_t* temp = m_display_frame;
    m_display_frame = m_curr_frame;
    m_curr_frame = temp;
    
    spiCommand({ 0, 0x2A, 4 }, &LCD::size_W[0]);
    spiCommand({ 0, 0x2B, 4 }, &LCD::size_H[0]);
    spiCommand({ 0, 0x2C, LCD::FRAME_SIZE_BYTES}, reinterpret_cast<const uint8_t*>(m_display_frame));
}

void PerifLCD::testImage()
{
    uint16_t pixel;

    for(int x = 0; x < LCD::WIDTH; ++x) {
        for(int y = 0; y < LCD::HEIGHT; ++y) {
            
            pixel = 0;
            
            if(x % 16 == 0) {
                pixel = 0xFFFF;
            }
            if(y % 16 == 0) {
                pixel = 0xFFFF;
            }
            drawPixel(x, y, pixel);
        }
    }
}

void PerifLCD::irqHandler()
{
    
}