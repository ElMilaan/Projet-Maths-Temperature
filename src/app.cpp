#include "headers/app.hpp"
#include <string>
#include <fstream>

App::App()
{
    setup();
}

void App::setup()
{
    Init_info infos{};
    FileSC::readFile(infos);
    largeur = infos.largeur;
    hauteur = infos.hauteur;
    h = infos.h;
    k = infos.k;
    conductivite = infos.conductivite;
    densite = infos.densite;
    capacite = infos.capacite;
    scene = infos.disposition;
    temperatures = std::vector<double>(scene.size());
    couleurs = std::vector<RGB>(scene.size() * 32 * 32);
}

void App::update()
{
    unsigned int cpt_file{0};
    calculTemperature();
    convert_all_temp_into_rgb();
}

void App::calculTemperature()
{
    float alpha = conductivite / (densite * capacite);
    float coeff = alpha * k / (h * h);

    // Boucle sur chaque point de la grille
    for (unsigned int i = 0; i < hauteur; i++)
    {
        for (unsigned int j = 0; j < largeur; j++)
        {
            int index = i * largeur + j;

            if (sources.count(scene[index]) > 0) // Vérification si le point est une source (radiateur ou fenêtre)
            {
                auto source = sources.at(scene[index]); // Si c'est une source, on laisse la température fixe
                temperatures[index] = source.second.getTemperature();
            }
            else
            {
                float sumNeighbors = 0.0f;
                int neighborCount = 0;

                for (int di = -1; di <= 1; di += 2) // On suppose que la température du mur est la même que celle du point voisin
                {
                    if (i + di < 0 || i + di >= hauteur) // Parcourt les voisins haut (di=-1) et bas (di=+1)
                    {
                        sumNeighbors += scene[index]; // Si le point est sur le bord, on prend la température du point voisin
                    }
                    else
                    {
                        sumNeighbors += scene[index + di * largeur]; // Sinon, voisin classique
                    }
                    ++neighborCount;
                }

                for (int dj = -1; dj <= 1; dj += 2)
                {
                    if (j + dj < 0 || j + dj >= largeur)
                    {
                        sumNeighbors += scene[index]; // Si le point est sur le bord, on prend la température du point voisin
                    }
                    else
                    {
                        sumNeighbors += scene[index + dj]; // Sinon, voisin classique
                    }
                    ++neighborCount;
                }

                // Calcul du changement de température
                float deltaT = coeff * (sumNeighbors - neighborCount * scene[index]);
                temperatures[index] = scene[index] + deltaT;
            }
        }
    }
}

RGB App::temperature_To_RGB(double temperature)
{
    // Limiter la température entre -10 et 50 degrés
    temperature = std::clamp((float)temperature, -10.0f, 50.0f); // Clamp entre -10 et 50 degrés
    unsigned char r, g, b;
    // Définir des valeurs limites
    if (temperature <= -10)
    {
        // Bleu pur à -10 °C
        r = 0;
        g = 0;
        b = 255;
    }
    else if (temperature >= 50)
    {
        // Rouge pur à 50 °C
        r = 255;
        g = 0;
        b = 0;
    }
    else
    {
        // Interpolation entre le bleu et le rouge
        float ratio = (temperature + 10) / 60.0f; // Normaliser la température dans la plage de 0 à 1

        if (ratio < 0.5f)
        {
            float t = ratio * 2;
            // De -10 à 20, passe du bleu au blanc
            r = (unsigned char)(255 * t);
            g = (unsigned char)(255 * t);
            b = 255; // Bleu constant jusqu'à 20
        }
        else
        {
            // De 20 à 50, passe du blanc au rouge
            r = 255;                                             // Le rouge augmente
            g = (unsigned char)(255 * (1 - (ratio - 0.5f) * 2)); // Le vert diminue
            b = (unsigned char)(255 * ((ratio - 0.5f) * 2));     // Bleu devient 0 à 50
        }
    }
    return {r, g, b};
}

void App::convert_all_temp_into_rgb()
{
    size_t index{0};
    for (size_t i{0}; i < temperatures.size(); i++)
    {
        for (unsigned int j{0}; j < RATIO; j++)
        {
            couleurs[index] = temperature_To_RGB(temperatures[i]);
            index++;
        }
    }
}

void App::writePPM(const std::string file_name, const std::string file_path)
{
    // Ouvrir le fichier en mode écriture
    std::ofstream ppmFile(file_path, std::ios::binary);
    if (!ppmFile)
    {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << file_name << std::endl;
        return;
    }

    ppmFile << "P6\n";
    ppmFile << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n";
    ppmFile << "255\n";

    for (RGB couleur : couleurs)
    {
        ppmFile << couleur.R << " " << couleur.G << " " << couleur.B << "\n";
    }
    std::cout << std::endl;

    // Fermer le fichier
    ppmFile.close();
    std::cout << "Fichier PPM ecrit avec succes dans : " << file_path << std::endl;
}