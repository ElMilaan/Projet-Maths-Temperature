#pragma once

#include <iostream>
class Source
{
private:
    const double init_temperature{};
    double temperature{};

public:
    Source(double init_temperature);
    double getTemperature();
    double setTemperature();
};
