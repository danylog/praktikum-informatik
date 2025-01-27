#ifndef STRECKENENDE_H
#define STRECKENENDE_H

#include "Fahrausnahme.h"
#include "Weg.h"
#include "Fahrzeug.h"

class Streckenende : public Fahrausnahme {
public:
    Streckenende(Fahrzeug& fahrzeug, Weg& weg)
        : Fahrausnahme(fahrzeug, weg) {}

    virtual void vBearbeiten() const override {
        std::cout << "Streckenende-Exception: Fahrzeug "
                 << p_pFahrzeug.getName()
                 << " hat Ende des Weges "
                 << p_pWeg.getName() << " erreicht." << std::endl;

        p_pWeg.pAbgabe(p_pFahrzeug);
    }
};

#endif
