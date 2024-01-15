#pragma once

class Clock;
class PerifLCD;
class PerifADC;
class PerifConsole;


namespace IO
{
    Clock& getClock();

    PerifLCD& getLCD();
    
    PerifADC& getADC1();
    
    PerifConsole& getUSART1();
}