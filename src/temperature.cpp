#include <iostream>
#include "headers/temperature.hpp"
#include <algorithm>

// template<typename T>
// T clamp(T value, T min, T max) {
//     if (value < min) return min;
//     if (value > max) return max;
//     return value;
// }

void Temperature::temperature_To_RGB(float temperature, int &r, int &g, int &b) {
    // Limiter la température entre -10 et 50 degrés
    temperature = std::clamp(temperature, -10.0f, 50.0f); // Clamp entre -10 et 50 degrés

    // Définir des valeurs limites
    if (temperature <= -10) {
        // Bleu pur à -10 °C
        r = 0; g = 0; b = 255;
    } else if (temperature >= 50) {
        // Rouge pur à 50 °C
        r = 255; g = 0; b = 0;
    } else {
        // Interpolation entre le bleu et le rouge
        float ratio = (temperature + 10) / 60.0f; // Normaliser la température dans la plage de 0 à 1

        if (ratio < 0.5f) {
            // De -10 à 20, passe du bleu au vert
            r = 0;
            g = static_cast<int>(255 * (ratio * 2)); // Le vert augmente
            b = 255; // Bleu constant jusqu'à 20
        } else {
            // De 20 à 50, passe du vert au rouge
            r = static_cast<int>(255 * ((ratio - 0.5f) * 2)); // Le rouge augmente
            g = static_cast<int>(255 * (1 - (ratio - 0.5f) * 2)); // Le vert diminue
            b = 0; // Bleu devient 0 à 50
        }
    }
}