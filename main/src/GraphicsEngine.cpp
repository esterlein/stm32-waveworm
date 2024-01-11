#include <cmath>
#include <algorithm>

#include "GraphicsEngine.h"


GraphicsEngine::GraphicsEngine(const std::function<void(int, int, uint16_t)>& painter,
                               uint16_t width, uint16_t height)
                               : pixPainter{painter}
                               , m_width{width}
                               , m_height{height}
                               , m_rotation{0}
                               , m_rot_width{width}
                               , m_rot_height{height}
{}

void GraphicsEngine::fillScreen(uint16_t color)
{
    fillRect(0, 0, m_width, m_height, color);
}

void GraphicsEngine::drawPixel(int x, int y, uint16_t color)
{
    if(x < 0 || x >= m_width || y < 0 || y >= m_height) return;
    
    pixPainter(x, y, color);
}

void GraphicsEngine::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color)
{
    int16_t steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if(steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if(x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int16_t dx = x1 - x0;
    int16_t dy = std::abs(y1 - y0);
    int16_t err = dx / 2;
    int16_t y_step = y0 < y1 ? 1 : -1;

    for(; x0 <= x1; ++x0) {
        if(steep)
            drawPixel(y0, x0, color);
        else
            drawPixel(x0, y0, color);

        err -= dy;
        if(err < 0) {
            y0 += y_step;
            err += dx;
        }
    }
}

void GraphicsEngine::drawHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    drawLine(x, y, x + w - 1, y, color);
}

void GraphicsEngine::drawVLine(int16_t x, int16_t y, int16_t h, uint16_t color)
{
    drawLine(x, y, x, y + h - 1, color);
}

void GraphicsEngine::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    drawHLine(x, y, w, color);
    drawHLine(x, y + h - 1, w, color);
    drawVLine(x, y, h, color);
    drawVLine(x + w - 1, y, h, color);
}

void GraphicsEngine::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color)
{
    for(int i = x; i < x + w; ++i)
        drawVLine(i, y, h, color);
}

void GraphicsEngine::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    drawPixel(x0    , y0 + r, color);
    drawPixel(x0    , y0 - r, color);
    drawPixel(x0 + r, y0    , color);
    drawPixel(x0 - r, y0    , color);

    int16_t x = 0, y = r;
    int16_t decision = 1 - r;
    int16_t dec_x = 1, dec_y = -2 * r;

    while(x < y) {
        if(decision >= 0) {
            --y;
            decision += dec_y += 2;
        }
        ++x;
        decision += dec_x += 2;

        drawPixel(x0 + x, y0 + y, color);
        drawPixel(x0 - x, y0 + y, color);
        drawPixel(x0 + x, y0 - y, color);
        drawPixel(x0 - x, y0 - y, color);
        drawPixel(x0 + y, y0 + x, color);
        drawPixel(x0 - y, y0 + x, color);
        drawPixel(x0 + y, y0 - x, color);
        drawPixel(x0 - y, y0 - x, color);
    }
}

void GraphicsEngine::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
    drawVLine(x0, y0 - r, 2 * r + 1, color);
    roundFiller(x0, y0, r, 3, 0, color);
}

void GraphicsEngine::roundFiller(int16_t x0, int16_t y0, int16_t r, uint8_t corner,
                                 int16_t delta, uint16_t color)
{
    int16_t x = 0, y = r;
    int16_t decision = 1 - r;
    int16_t dec_x = 1, dec_y = -2 * r;

    while(x < y) {
        if(decision >= 0) {
            --y;
            decision += dec_y += 2;
        }
        ++x;
        decision += dec_x += 2;

        if(corner & 0x1) {
            drawVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
            drawVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
        }
        if(corner & 0x2) {
            drawVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
            drawVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
        }
    }
}

void GraphicsEngine::setRotation(uint8_t r)
{
    m_rotation = r & 3;
    switch(m_rotation) {
    case 0: case 2:
        m_rot_width  = m_width;
        m_rot_height = m_height;
        break;
    case 1: case 3:
        m_rot_width  = m_height;
        m_rot_height = m_width;
        break;
    }
}