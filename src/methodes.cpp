#include "headers/init.hpp"
#include <vector>

std::vector<double> calculTemperature(Init_info &infos)
{
    double alpha = infos.conductivite / (infos.densite * infos.capacite);
    double coeff = alpha * infos.k / (infos.h * infos.h);

    // Création d'une copie pour stocker les nouvelles températures
    std::vector<double> newTemps(infos.disposition.size(), 19.0f); // Initialiser avec 19°C (température initiale de la pièce)

    // Boucle sur chaque point de la grille
    for (int i = 0; i < infos.hauteur; ++i)
    {
        for (int j = 0; j < infos.largeur; ++j)
        {
            int index = i * infos.largeur + j;

            // Vérification si le point est une source (radiateur ou fenêtre)
            if (infos.sources.count(infos.disposition[index]) > 0)
            {
                // Si c'est une source, on laisse la température fixe
                auto source = infos.sources.at(infos.disposition[index]);
                newTemps[index] = static_cast<double>(source.second.getTemperature());
            } // La température de la source
            else
            {
                double sumNeighbors = 0.0f;
                int neighborCount = 0;

                // Cas des bords : on suppose que la température du mur est la même que celle du point voisin
                for (int di = -1; di <= 1; di += 2)
                { // Parcourt les voisins haut (di=-1) et bas (di=+1)
                    if (i + di < 0 || i + di >= infos.hauteur)
                    { // Si le point est sur le bord, on prend la température du point voisin
                        sumNeighbors += infos.disposition[index];
                    }
                    else
                    {
                        sumNeighbors += infos.disposition[index + di * infos.largeur]; // Sinon, voisin classique
                    }
                    ++neighborCount;
                }

                for (int dj = -1; dj <= 1; dj += 2)
                { // Parcourt les voisins gauche (dj=-1) et droit (dj=+1)
                    if (j + dj < 0 || j + dj >= infos.largeur)
                    { // Si le point est sur le bord, on prend la température du point voisin
                        sumNeighbors += infos.disposition[index];
                    }
                    else
                    {
                        sumNeighbors += infos.disposition[index + dj]; // Sinon, voisin classique
                    }
                    ++neighborCount;
                }

                // Calcul du changement de température
                double deltaT = coeff * (sumNeighbors - neighborCount * infos.disposition[index]);
                newTemps[index] = infos.disposition[index] + deltaT;
            }
        }
    }

    // On retourne les nouvelles temperatures de chaque partie de la scene
    return newTemps;
}