#ifndef PKW_H
#define PKW_H

#include "Fahrzeug.h"
#include <iostream>
#include <iomanip>

class PKW : public Fahrzeug {
public:
	PKW(const std::string& name,
	        double maxGeschwindigkeit,
	        double verbrauch,
	        double tankvolumen = 55.0);

	    // Overriding the vAusgeben function
	    virtual void vAusgeben() override;
	    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	    virtual void vSimulieren() override;
private:
    const double p_dVerbrauch;
    const double p_dTankvolumen;
    double p_dTankinhalt;

};

#endif
