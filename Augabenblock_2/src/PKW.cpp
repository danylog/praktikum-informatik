#include "PKW.h"
#include "Tempolimit.h"
#include <iostream>
#include "Verhalten.h"
#include "Weg.h"
#include "Simuclient.h"


PKW::PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen):
Fahrzeug(name, maxGeschwindigkeit),
		p_dVerbrauch(verbrauch),
		p_dTankvolumen(tankvolumen?tankvolumen:55),
		p_dTankinhalt(tankvolumen/2)
{

	std::cout<<"Constuctor fuer ein pkw gerufen" << std::endl;

}

void PKW::vAusgeben(std::ostream& os) const{
    Fahrzeug::vAusgeben(os);
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(10) << p_dVerbrauch << " "
              << std::setw(12) << p_dTankinhalt << " "
              << std::setw(12) << p_dTankvolumen;
}



double PKW::dTanken(double menge){
	double dGetankt = 0.0;
	if(menge < 0.0) return 0.0;
    if (menge == std::numeric_limits<double>::infinity()) {
        dGetankt = p_dTankvolumen - p_dTankinhalt;
        p_dTankinhalt = p_dTankvolumen;
    } else {
        dGetankt = std::min(menge, p_dTankvolumen - p_dTankinhalt);
        p_dTankinhalt += dGetankt;
    }

    return dGetankt;
}

double PKW::dGeschwindigkeit() const{
    if(p_dTankinhalt == 0){
    	return 0;
    }else{
        if (!p_pVerhalten) return p_dMaxGeschwindigkeit;

        Weg& weg = p_pVerhalten->getWeg();
        double tempLimit = weg.getTempolimit();


        return std::min(p_dMaxGeschwindigkeit, tempLimit);

    }
}

// In PKW.cpp
void PKW::vSimulieren() {
    double dDeltaTime = dGlobaleZeit - p_dZeit;

    if (dDeltaTime > 0) {
        // Consider fuel consumption
        if (p_dTankinhalt > 0) {
            // Calculate new position with actual speed
            double dActualSpeed = p_dMaxGeschwindigkeit;  // Can be modified by tank status
            double dDistance = dDeltaTime * dActualSpeed;

            // Update total distance
            p_dGesamtStrecke += dDistance;

            // Update fuel
            double dVerbrauch = dDistance * p_dVerbrauch / 100.0;
            p_dTankinhalt = std::max(0.0, p_dTankinhalt - dVerbrauch);
        }

        // Update last simulation time
        p_dZeit = dGlobaleZeit;
    }
}

void PKW::vZeichnen(const Weg& weg) const {
    double relativePosition = getAbschnittStrecke() / weg.getLength();

    // Call with correct parameters: PKWName, WegName, RelPosition, KmH, Tank
    bZeichnePKW(
        p_sName,                    // PKW name
        weg.getName(),              // Road name
        relativePosition,           // Relative position
        dGeschwindigkeit(),         // Current speed in KmH
        p_dTankinhalt              // Current tank level
    );
}
