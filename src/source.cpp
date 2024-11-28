#include <iostream>
#include "headers/source.hpp"

Source::Source(double init_temperature) : init_temperature(init_temperature), temperature(init_temperature) {}

Radiateur::Radiateur(double init_temperature) : Source(init_temperature) {}

Fenetre::Fenetre(double init_temperature) : Source(init_temperature) {}

double Source::getTemperature() const
{
    return this->temperature;
}