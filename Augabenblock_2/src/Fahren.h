#ifndef FAHREN_H
#define FAHREN_H

#include "Verhalten.h"
#include "Streckenende.h"

class Fahren : public Verhalten {
public:
    Fahren(Weg& weg) : Verhalten(weg) {}

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override {
        double dMaxStrecke = p_rWeg.getLength() - aFzg.getAbschnittStrecke();  // Changed from getGesamtStrecke
        double dFahrbareStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;

        if (dFahrbareStrecke > dMaxStrecke) {
            throw Streckenende(aFzg, p_rWeg);
        }
        return dFahrbareStrecke;
    }

    std::string sBeschreibung() const override {
        return "Fahrend";
    }
};

#endif
