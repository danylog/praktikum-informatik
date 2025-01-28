// Kreuzung.cpp
#include "Kreuzung.h"
#include "PKW.h"

Kreuzung::Kreuzung(const std::string& name, double tankstelle)
    : Simulationsobjekt(name), p_dTankstelle(tankstelle) {}

void Kreuzung::vVerbinde(const std::string& hinweg,
                        const std::string& rueckweg,
                        double laenge,
                        std::shared_ptr<Kreuzung> kreuzung1,
                        std::shared_ptr<Kreuzung> kreuzung2,
                        Tempolimit tempolimit) {
    // Create forward road (Hinweg)
    auto hinWeg = std::make_shared<Weg>(hinweg, laenge, tempolimit);

    // Create return road (Rückweg)
    auto rueckWeg = std::make_shared<Weg>(rueckweg, laenge, tempolimit);

    // Connect the roads to their respective intersections
    kreuzung1->vAnnahmeWeg(hinWeg);
    kreuzung2->vAnnahmeWeg(rueckWeg);
}



void Kreuzung::vSimulieren() {
    // Simulate all outgoing roads
    for (const auto& weg : p_pWege) {
        weg->vSimulieren();
    }
}

double Kreuzung::dTanken(double dMenge) {
    if (p_dTankstelle > 0.0) {
        // If there's enough fuel in the station
        if (p_dTankstelle >= dMenge) {
            p_dTankstelle -= dMenge;
            return dMenge;
        } else {
            // Return remaining fuel (with reserve for the last car)
            double restTankstelle = p_dTankstelle;
            p_dTankstelle = 0.0;
            return restTankstelle;
        }
    }
    return 0.0;  // No fuel available
}

void Kreuzung::vAnnahmeWeg(std::shared_ptr<Weg> weg) {
    p_pWege.push_back(weg);
}
