#pragma once

#include <iostream>

struct RGB
{
    unsigned char R{255};
    unsigned char G{255};
    unsigned char B{255};
};

class Temperature
{
private:
public:
    RGB temperature_To_RGB(float temperature);
};
