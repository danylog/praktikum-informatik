#ifndef PKW_H
#define PKW_H

#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>

class PKW : public Fahrzeug {
public:
    PKW(const std::string& name, double maxGeschwindigkeit)
        : Fahrzeug(name, maxGeschwindigkeit) {}


    virtual void vAusgeben() override {
        Fahrzeug::vAusgeben();
    }
};

#endif
