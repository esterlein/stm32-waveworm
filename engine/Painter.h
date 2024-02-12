#pragma once

#include <cstdint>
#include <functional>


class Painter
{
public:
    Painter() = delete;
    Painter(const std::function<void(int, int, uint16_t)>& painter,
                   uint16_t width, uint16_t height);

    void fillScreen(uint16_t color);

    void putPixel(int x, int y, uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

    void drawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    void drawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);

    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);

    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

    void setRotation(uint8_t r);

private:
    std::function<void(int, int, uint16_t)> pixPainter;

    void roundFiller(int16_t x0, int16_t y0, int16_t r, uint8_t corner,
                     int16_t delta, uint16_t color);

    const uint16_t m_width;
    const uint16_t m_height;

    uint8_t m_rotation;
    uint16_t m_rot_width;
    uint16_t m_rot_height;
};