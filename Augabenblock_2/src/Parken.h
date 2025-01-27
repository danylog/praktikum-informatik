#ifndef PARKEN_H
#define PARKEN_H

#include "Verhalten.h"
#include "Losfahren.h"

class Parken : public Verhalten {
public:
    Parken(Weg& weg, double startzeit)
        : Verhalten(weg), p_dStartzeit(startzeit) {}

    double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override {
        if (dGlobaleZeit < p_dStartzeit) {
            return 0.0;
        }

        if (dGlobaleZeit >= p_dStartzeit) {
            throw Losfahren(aFzg, p_rWeg);
        }

        return 0.0;
    }

    std::string sBeschreibung() const override {
        return "Parkend";
    }

private:
    const double p_dStartzeit;
};

#endif
