#pragma once

#include <cstdint>

#include "PerifBase.h"


class PerifADC : public PerifBase
{
public:
    PerifADC() = delete;
    ~PerifADC() = default;

    PerifADC(uint32_t port, uint32_t pins, uint32_t adc);

private:
    const uint32_t m_ADC;

public:
    void irqHandler() override;
};