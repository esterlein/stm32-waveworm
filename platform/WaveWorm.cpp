#include <cstdint>

#include "IO.h"
#include "Clock.h"
#include "SDRAM.h"

#include "Painter.h"
#include "PerifLCD.h"


int main()
{
    auto& clock = IO::getClock();
    
    SDRAM::initSDRAM();

    auto& lcd = IO::getLCD();

    Painter painter{std::bind(&PerifLCD::drawPixel, lcd,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3),
                          LCD::WIDTH, LCD::HEIGHT};
    
    painter.fillScreen(LCDC::BLACK);
    
    // Test section

    painter.drawLine(50, 50, 150, 150, LCDC::WHITE);
    painter.drawCircle(100, 100, 50, LCDC::WHITE);
    painter.fillRect(75, 85, 60, 40, LCDC::BLUE);
    painter.fillCircle(200, 200, 90, LCDC::CYAN);

    lcd.showFrame();

    while(1);

    return 0;
}