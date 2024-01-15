#include <csetjmp>

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/iwdg.h>
#include <libopencm3/cm3/scb.h>
#include <libopencm3/cm3/cortex.h>

#include "Clock.h"

#include "PerifConsole.h"


PerifConsole::PerifConsole(uint32_t port, uint32_t pins, uint32_t usart, uint32_t baudrate, uint32_t bits) 
    : m_console_USART{usart}
    , m_recv_Curr{0}
    , m_recv_Next{0}
{
    gpio_mode_setup(port, GPIO_MODE_AF, GPIO_PUPD_NONE, pins);
    gpio_set_af(port, GPIO_AF7, pins);

    usart_set_baudrate(m_console_USART, baudrate);
    usart_set_databits(m_console_USART, bits);
    usart_set_stopbits(m_console_USART, USART_STOPBITS_1);
    usart_set_mode(m_console_USART, USART_MODE_TX_RX);
    usart_set_parity(m_console_USART, USART_PARITY_NONE);
    usart_set_flow_control(m_console_USART, USART_FLOWCONTROL_NONE);
    usart_enable(m_console_USART);

    nvic_enable_irq(NVIC_USART1_IRQ);
    usart_enable_rx_interrupt(m_console_USART);
}

char PerifConsole::readChar(int wait)
{
    while((wait && m_recv_Curr) == m_recv_Next);

    char c = 0;
    if(m_recv_Curr != m_recv_Next) {
        c = m_recv_Buffer[m_recv_Curr];
        m_recv_Curr = (m_recv_Curr + 1) % s_recv_Buf_Size;
    }
    return c;
}

void PerifConsole::writeChar(char c)
{
    uint32_t reg;

    do {
        reg = USART_SR(m_console_USART);
    }
    while((reg & USART_SR_TXE) == 0);

    USART_DR(m_console_USART) = static_cast<uint32_t>(c) & 0xFF;
}

int PerifConsole::readString(char* str, int len)
{
    char c;
    char* temp = str;
    *temp = '\000';

    while((c = readChar(1)) != '\r') {
        
        if(c == '\010' || c == '\127') {
            if(temp > str) {
                writeString("\010 \010");
                --temp;
            }
        }
        else {
            *temp = c;
            writeChar(c);
            
            if(temp - str < len) {
                ++temp;
            }
        }
        *temp = '\000';
    }
    return temp - str;
}

void PerifConsole::writeString(const char* str)
{
    while(*str != '\000') {
        writeChar(*str);

        if(*str == '\n') {
            writeChar('\r');
        }
        ++str;
    }
}

void PerifConsole::irqHandler()
{
    int	buff_ndx;
    uint32_t reg;

    do{
        reg = USART_SR(m_console_USART);
        
        if(reg & USART_SR_RXNE) {
            m_recv_Buffer[m_recv_Next] = USART_DR(m_console_USART);

            buff_ndx = (m_recv_Next + 1) % s_recv_Buf_Size;
            
            if(buff_ndx != m_recv_Curr) {
                m_recv_Next = buff_ndx;
            }
        }
    }
    while((reg & USART_SR_RXNE) != 0);
}