#ifndef LOSFAHREN_H
#define LOSFAHREN_H

#include "Fahrausnahme.h"

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fahrzeug, Weg& weg)
        : Fahrausnahme(fahrzeug, weg) {}

    virtual void vBearbeiten() override {
        std::cout << "Losfahren-Exception: Fahrzeug "
                 << p_pFahrzeug.getName()
                 << " auf Weg " << p_pWeg.getName()
                 << " startet." << std::endl;
    }
};

#endif
