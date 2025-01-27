#ifndef FAHRAUSNAHME_H
#define FAHRAUSNAHME_H

#include <exception>
#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : public std::exception {
public:
    Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg)
        : p_pFahrzeug(fahrzeug), p_pWeg(weg) {}
    virtual ~Fahrausnahme() = default;
    virtual void vBearbeiten() = 0;

protected:
    Fahrzeug& p_pFahrzeug;
    Weg& p_pWeg;
};

#endif
