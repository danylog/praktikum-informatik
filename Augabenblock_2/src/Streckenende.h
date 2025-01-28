// Streckenende.h
#ifndef STRECKENENDE_H
#define STRECKENENDE_H

#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Kreuzung.h"
#include "Weg.h"
#include "PKW.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fahrzeug, Weg& weg)
        : Fahrausnahme(fahrzeug, weg) {}

    void vBearbeiten() const override {
        std::cout << "Streckenende-Exception: Fahrzeug "
                  << p_pFahrzeug.getName()
                  << " hat Ende des Weges "
                  << p_pWeg.getName() << " erreicht." << std::endl;

        // If vehicle is a PKW, try to refuel
        if (auto* pkw = dynamic_cast<PKW*>(&p_pFahrzeug)) {
            if (auto zielKreuzung = p_pWeg.getZielKreuzung()) {
                double tankvolumen = pkw->getTankinhalt();  // Use existing getter
                if (tankvolumen < pkw->getTankvolumen()) {  // Use existing getter
                    double benoetigteMenge = pkw->getTankvolumen() - tankvolumen;
                    double getankteMenge = zielKreuzung->dTanken(benoetigteMenge);
                    pkw->dTanken(getankteMenge);
                }
            }
        }

        // Get next road
        if (Weg* nextWeg = p_pWeg.getRandomNextWeg()) {
            // Move vehicle to new road
            std::unique_ptr<Fahrzeug> fahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);
            if (fahrzeug) {
                nextWeg->vAnnahme(std::move(fahrzeug));
            }
        }
    }
};

#endif
