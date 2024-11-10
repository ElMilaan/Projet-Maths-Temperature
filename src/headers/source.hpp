#pragma once
#include <iostream>

class Source
{
protected:
    const double init_temperature{};
    double temperature{};

public:
    Source(double init_temperature);
    virtual double getTemperature() const;
    virtual void setTemperature(double temperature);
    int nb_sources;
};

class Radiateur : public Source
{
public:
    Radiateur(double init_temperature);
};

class Fenetre : public Source
{
public:
    Fenetre(double init_temperature);
};
