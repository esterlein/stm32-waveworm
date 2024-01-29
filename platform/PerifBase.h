#pragma once


class PerifBase
{
public:
    PerifBase() = default;
    virtual ~PerifBase() = default;

    PerifBase(const PerifBase&) = default;
    
    PerifBase& operator=(const PerifBase&) = delete;
    
    PerifBase(PerifBase&&) noexcept = delete;
    PerifBase& operator=(PerifBase&&) noexcept = delete;
    
    virtual void irqHandler() = 0;
};