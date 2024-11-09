#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include "source.hpp"

class Init_info
{
public:
    unsigned int largeur{0};
    unsigned int hauteur{0};
    double h{0};
    double k{0};
    double conductivite{0};
    double densite{0};
    double capacite{0};
    unsigned int nb_sources{0};
    std::unordered_map<int, std::pair<int, Source>> sources{};
    std::vector<unsigned int> disposition{};

    void displayDispo();
};

std::ostream &operator<<(std::ostream &os, Init_info infos);
void displayDispo(const std::vector<unsigned int> vec, const unsigned int gap);

namespace FileSC
{
    const std::string PATH{"src/sc/scene.sc"};

    void readFile(Init_info &infos);
    void writeFile();
};
