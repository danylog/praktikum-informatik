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

	void vKreuzungErreicht();
	    virtual void vAusgeben(std::ostream& os) const override;
	    virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) override;
	    virtual void vSimulieren() override;
	    virtual double dGeschwindigkeit() const override;
	    void vZeichnen(const Weg& weg) const override;
	    double getTankinhalt() const {return p_dTankinhalt;}


	    double getTankvolumen() const {return p_dTankvolumen;}
private:
    const double p_dVerbrauch;
    const double p_dTankvolumen;
    double p_dTankinhalt;

};

#endif
