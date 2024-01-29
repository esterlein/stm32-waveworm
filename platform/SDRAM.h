#pragma once

#include <cstdint>

#define SDRAM_BASE_ADDRESS ((uint8_t *)(0xD0000000))


namespace SDRAM
{
    void initSDRAM();
}