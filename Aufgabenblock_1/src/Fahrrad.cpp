#include "Fahrrad.h"
#include <iostream>

Fahrrad::Fahrrad(const std::string& name, const double maxGeschwindigkeit)
    : Fahrzeug(name, maxGeschwindigkeit) {}

void Fahrrad::vSimulieren() {
    double dZeitschritt = dGlobaleZeit - p_dZeit;

    if (dZeitschritt > 0.0) {
        double dReduzierteGeschwindigkeit = p_dMaxGeschwindigkeit;
        if (p_dGesamtStrecke > 20.0) {
            dReduzierteGeschwindigkeit *= 0.9;
        }

        double dGefahreneStrecke = dReduzierteGeschwindigkeit * dZeitschritt;
        p_dGesamtStrecke += dGefahreneStrecke;
        p_dGesamtZeit += dZeitschritt;
        p_dZeit = dGlobaleZeit;
    }
}
