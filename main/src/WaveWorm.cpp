#include <cstdint>

#include "IO.h"
#include "Clock.h"
#include "SDRAM.h"

#include "PerifLCD.h"
#include "GraphicsEngine.h"


int main()
{
    auto& clock = IO::getClock();
    
    SDRAM::initSDRAM();

    auto& lcd = IO::getLCD();

    GraphicsEngine engine{std::bind(&PerifLCD::drawPixel, lcd,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                          LCD::WIDTH, LCD::HEIGHT};
    
    engine.fillScreen(LCDC::BLACK);
    
    // Test section

    engine.drawLine(50, 50, 150, 150, LCDC::WHITE);
    engine.drawCircle(100, 100, 50, LCDC::WHITE);
    engine.fillRect(75, 85, 60, 40, LCDC::BLUE);
    engine.fillCircle(200, 200, 90, LCDC::CYAN);

    lcd.showFrame();

    while(1);

    return 0;
}