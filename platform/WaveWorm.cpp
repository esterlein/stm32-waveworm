#include <cstdint>

#include "IO.h"
#include "Clock.h"
#include "SDRAM.h"

#include "Vec3D.h"
#include "Mesh.h"

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

    Vec3D<float> vec1;
    Vec3D<float> vec2(0.5f, 0.5f, 0.5f);
    Vec3D<float> vec3 = vec1 + vec2;

    Mesh<Vec3D<float>, 10> mesh;

    painter.drawLine(50, 50, 150, 150, LCDC::WHITE);
    painter.drawCircle(100, 100, 50, LCDC::WHITE);
    painter.fillRect(75, 85, 60, 40, LCDC::BLUE);
    painter.fillCircle(200, 200, 90, LCDC::CYAN);

    lcd.showFrame();

    while(1);

    return 0;
}