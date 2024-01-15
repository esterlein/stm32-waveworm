#pragma once

class Clock;
class PerifLCD;
class PerifADC;
class PerifConsole;


namespace IO
{
    inline Clock& getClock();

    inline PerifLCD& getLCD();
    
    inline PerifADC& getADC1();
    
    inline PerifConsole& getUSART1();
}