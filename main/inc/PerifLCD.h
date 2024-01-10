#pragma once

#include <cstdint>

#include "PerifBase.h"


namespace LCD
{
    namespace Color
    {
        inline constexpr uint16_t BLACK   = 0x0000;
        inline constexpr uint16_t BLUE    = 0x1F00;
        inline constexpr uint16_t RED     = 0x00F8;
        inline constexpr uint16_t GREEN   = 0xE007;
        inline constexpr uint16_t CYAN    = 0xFF07;
        inline constexpr uint16_t MAGENTA = 0x1FF8;
        inline constexpr uint16_t YELLOW  = 0xE0FF;
        inline constexpr uint16_t GREY    = 0xC339;
        inline constexpr uint16_t WHITE   = 0xFFFF;
    }

    inline constexpr uint16_t WIDTH  = 240;
    inline constexpr uint16_t HEIGHT = 320;

    inline constexpr uint32_t FRAME_SIZE = WIDTH * HEIGHT;
    inline constexpr uint32_t FRAME_SIZE_BYTES = FRAME_SIZE * 2;

    struct Command
    {
        uint16_t delay;
	    uint8_t  cmd;
	    uint32_t n_args;
    };

    inline constexpr uint8_t size_W[] = {
        0,
        0,
        (WIDTH >> 8) & 0xFF,
        WIDTH & 0xFF
    };

    inline constexpr uint8_t size_H[] = {
        0,
        0,
        (HEIGHT >> 8) & 0xFF,
        HEIGHT & 0xFF
    };
}


class PerifLCD : public PerifBase
{
public:
    PerifLCD();
    ~PerifLCD() = default;

    void showFrame();
    void drawPixel(int x, int y, uint16_t color);

    //int printDec(int dec);
    //int printHex(int hex);

private:
    void spiCommand(const LCD::Command& command, const uint8_t* args);
    void testImage();

    uint16_t* m_curr_frame;
    uint16_t* m_display_frame;

public:
    void irqHandler() override;
};