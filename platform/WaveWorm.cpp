#include <cstdint>

#include "IO.h"
#include "Clock.h"
#include "SDRAM.h"

#include "Vec2D.h"
#include "Vec3D.h"
#include "Vec4D.h"
#include "Mtx3x3.h"
#include "Mtx4x4.h"

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

    Vec2D<float> vec4;
    Vec2D<float> vec5(0.5f, 0.5f);
    Vec2D<float> vec6 = vec4 + vec5;

    Mtx3x3<float> mtx1;
    Mtx4x4<float> mtx2;

    Vec4D<float> vec7;
    Vec4D<float> vec8(0.5f, 0.5f, 0.5f);
    Vec4D<float> vec9 = vec7 + vec8;

    Mesh<Vec3D<float>, 10> mesh;

    painter.drawLine(50, 50, 150, 150, LCDC::WHITE);
    painter.drawCircle(100, 100, 50, LCDC::WHITE);
    painter.fillRect(75, 85, 60, 40, LCDC::BLUE);
    painter.fillCircle(200, 200, 90, LCDC::CYAN);

    lcd.showFrame();

    while(1);

    return 0;
}