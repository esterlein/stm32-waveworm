#pragma once

#include <cstdint>

#include "PerifBase.h"


class PerifConsole : public PerifBase
{
public:
    PerifConsole() = delete;
    ~PerifConsole() = default;
    PerifConsole(uint32_t port, uint32_t pins, uint32_t uart, uint32_t baudrate, uint32_t bits);

    char readChar(int wait);
    void writeChar(char c);

    int readString(char* str, int len);
    void writeString(const char* str);

private:
    static constexpr int s_recv_Buf_Size = 128;
    char m_recv_Buffer[s_recv_Buf_Size];
    
    const uint32_t m_console_USART;

    volatile int m_recv_Next;
    volatile int m_recv_Curr;

public:
    void irqHandler() override;
};