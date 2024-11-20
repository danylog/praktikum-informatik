#ifndef FAHRRAD_H
#define FAHRRAD_H

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug {
public:
    Fahrrad(const std::string& name, const double maxGeschwindigkeit);
    virtual void vSimulieren() override;
    virtual double dSpeed() override;
};

#endif
