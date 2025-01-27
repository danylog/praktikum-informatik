#ifndef LOSFAHREN_H
#define LOSFAHREN_H

#include "Fahrausnahme.h"
#include <iostream>

class Losfahren : public Fahrausnahme {
public:
    Losfahren(Fahrzeug& fahrzeug, Weg& weg)
        : Fahrausnahme(fahrzeug, weg) {}

    void vBearbeiten() const override {  // Removed const
        std::cout << "Losfahren-Exception: Fahrzeug "
                  << p_pFahrzeug.getName()
                  << " startet auf Weg "
                  << p_pWeg.getName() << " erreicht." << std::endl;

        std::unique_ptr<Fahrzeug> fahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);
        if (fahrzeug) {
            p_pWeg.vAnnahme(std::move(fahrzeug));
        }
    }
};

#endif
