#ifndef FAHREN_H
#define FAHREN_H

#include "Verhalten.h"
#include "Weg.h"
#include "Fahrzeug.h"

class Fahren : public Verhalten {
public:
    Fahren(Weg& weg) : Verhalten(weg) {}

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override {
        double dMaxStrecke = p_rWeg.getLength() - aFzg.getAbschnittStrecke();
        double dFahrbareStrecke = aFzg.dGeschwindigkeit() * dZeitIntervall;

        if (dFahrbareStrecke > dMaxStrecke) {
            return dMaxStrecke; // Stop at the end of the road
        }
        return dFahrbareStrecke;
    }

    std::string sBeschreibung() const override {
        return "Driving behavior";
    }
};

#endif
