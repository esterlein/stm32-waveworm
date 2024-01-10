#include <cstdint>

#include "Clock.h"
#include "SDRAM.h"
#include "Driver.h"

#include "GraphicsEngine.h"


int main(void)
{
    CLOCK::clockInit();
    SDRAM::sdramInit();

    auto& lcd = D::getLCD();
    auto& usart = D::getUSART1();

    GraphicsEngine engine{std::bind(&PerifLCD::drawPixel, lcd,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                          LCD::WIDTH, LCD::HEIGHT};
    
    engine.fillScreen(LCD::Color::BLACK);
    
    lcd.showFrame();

    while(1);

    return 0;
}