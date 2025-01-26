#ifndef PARKEN_H
#define PARKEN_H

#include "Verhalten.h"

class Parken : public Verhalten {
public:
    Parken(Weg& weg) : Verhalten(weg) {}

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override {
        return 0.0; // No movement, parked vehicle
    }

    std::string sBeschreibung() const override {
        return "Parking behavior";
    }
};

#endif
