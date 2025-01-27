#ifndef STRECKENENDE_H
#define STRECKENENDE_H

#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fahrzeug, Weg& weg)
        : Fahrausnahme(fahrzeug, weg) {}

    virtual void vBearbeiten() override {
        std::cout << "Streckenende-Exception: Fahrzeug "
                 << p_pFahrzeug.getName()
                 << " hat Ende des Weges "
                 << p_pWeg.getName() << " erreicht." << std::endl;
    }
};

#endif
