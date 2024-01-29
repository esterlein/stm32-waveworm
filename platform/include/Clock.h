#pragma once

#include <atomic>
#include <cstdint>
#include <initializer_list>

#include <libopencm3/stm32/rcc.h>

#include "IO.h"


class Clock
{
protected:
    Clock(std::initializer_list<rcc_periph_clken> peripherals);

public:
    Clock() = delete;
    ~Clock() = default;

    Clock(Clock&) = delete;
    Clock(Clock&&) noexcept = delete;

    void operator=(const Clock&) = delete;
    void operator=(Clock&&) noexcept = delete;

private:
    static inline std::atomic<uint32_t> s_system_ms;
    static inline std::atomic<uint32_t> s_delay_timer;

public:
    static void msleep(uint32_t delay_ms);
    static void usleep(uint32_t delay_us);

    uint32_t mtime() const;

    friend Clock& IO::getClock();

    void irqHandler();
};