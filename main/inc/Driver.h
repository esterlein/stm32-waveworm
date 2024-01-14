#pragma once

class PerifLCD;
class PerifADC;
class PerifConsole;


namespace Driver
{
    PerifLCD& getLCD();
    
    PerifADC& getADC1();
    
    PerifConsole& getUSART1();
}

namespace D = Driver;