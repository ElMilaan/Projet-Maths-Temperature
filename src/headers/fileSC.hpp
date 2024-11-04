#pragma once

#include <iostream>
#include <map>

class FileSC
{
private:
    std::string path{};

public:
    void readFile();
    void writeFile();
};
