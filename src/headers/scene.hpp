#pragma once
#include "temperature.hpp"
#include "source.hpp"

#include <iostream>

class Scene
{
private:
public:
    Temperature T;
    Source src;
    Scene();
    ~Scene();
};
