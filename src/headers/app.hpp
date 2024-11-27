#pragma once
#include <vector>
#include <algorithm>
#include "source.hpp"
#include "../headers/init.hpp"
#include "../headers/temperature.hpp"

class App
{
public:
    App();
    void setup();
    void update();
    void calculTemperature();
    RGB temperature_To_RGB(double temperature);
    void convert_all_temp_into_rgb();
    void writePPM(const std::string file_name, const std::string file_path);

    static const unsigned int IMAGE_WIDTH{256};
    static const unsigned int IMAGE_HEIGHT{128};
    static const unsigned int RATIO{32}; // 1 élément de la scene fait 32 pixels de côté

private:
    std::vector<double> temperatures{};
    std::vector<RGB> couleurs{};

    unsigned int largeur{};
    unsigned int hauteur{};
    double h{};
    double k{};
    double conductivite{};
    double densite{};
    double capacite{};

    std::vector<unsigned int> scene{};
    std::unordered_map<int, std::pair<int, Source>> sources{};
};