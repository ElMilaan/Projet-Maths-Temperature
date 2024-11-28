#include <iostream>
#include "headers/temperature.hpp"
#include "headers/source.hpp"
#include "headers/init.hpp"
#include "headers/app.hpp"
#include <chrono>
#include <thread>
#include <string>

using namespace std;

int main()
{
    // Init_info infos{};
    // std::cout << infos;
    // FileSC::readFile(infos);
    // std::cout << infos;

    // infos.displayDispo(); // Affiche la disposition mise à jour après l'itération

    // infos.displayDispo();

    App *app = new App();

    unsigned int cpt_file{0};
    while (true)
    {
        // Obtenir l'heure de début
        auto start = std::chrono::steady_clock::now();

        app->update();
        std::string file_name = "scene_" + std::to_string(cpt_file) + ".ppm";
        std::string file_path = "src/ppm/" + file_name;
        app->writePPM(file_name, file_path);
        cpt_file++;

        // Boucle qui dure 3 secondes
        while (true)
        {
            app->update();
            // Obtenir l'heure actuelle
            auto now = std::chrono::steady_clock::now();
            // Calculer la durée écoulée
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - start);
            // Quitter la boucle après 3 secondes
            if (elapsed.count() >= 3)
            {
                break;
            }
        }
    }

    // Radiateur rad{40};
    // cout << rad.getTemperature() << std::endl;
    // Temperature temp;
    // float temperature;

    // std::cout << "Entrez une température (-10 à 50 °C) : ";
    // std::cin >> temperature;

    // RGB color = temp.temperature_To_RGB(temperature);

    // std::cout << "Couleur RGB pour " << temperature << " °C : "
    //           << "R: " << (int)color.R << ", G: " << (int)color.G << ", B: " << (int)color.B << std::endl;

    // return 0;
}
