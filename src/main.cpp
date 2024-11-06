#include <iostream>
#include "headers/temperature.hpp"
#include "headers/source.hpp"
#include "headers/init.hpp"
using namespace std;

int main()
{
    Init_info infos{};
    std::cout << infos;
    FileSC::readFile(infos);
    std::cout << infos;
    Radiateur rad{40};
    cout << rad.getTemperature();
    Temperature temp;
    int r, g, b;
    float temperature;

    std::cout << "Entrez une température (-10 à 50 °C) : ";
    std::cin >> temperature;

    temp.temperature_To_RGB(temperature, r, g, b);

    std::cout << "Couleur RGB pour " << temperature << " °C : "
              << "R: " << r << ", G: " << g << ", B: " << b << std::endl;

    return 0;
}
