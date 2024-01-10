#pragma once

#include <cstdint>


namespace CLOCK
{
    void clockInit();
    
    void msleep(uint32_t);
    
    uint32_t mtime();
}