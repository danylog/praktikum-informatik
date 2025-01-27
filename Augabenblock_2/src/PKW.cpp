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

void PKW::vSimulieren() {
    if (p_dTankinhalt > 0.0) {
        double dZeitschritt = dGlobaleZeit - p_dZeit;

        if (p_pVerhalten) {
            // Get the distance we'll drive in this step
            double dGefahreneStrecke = p_pVerhalten->dStrecke(*this, dZeitschritt);

            // Calculate fuel consumption for this distance
            double dVerbrauch = (dGefahreneStrecke / 100.0) * p_dVerbrauch;

            // Only move if we have enough fuel
            if (dVerbrauch <= p_dTankinhalt) {
                p_dGesamtStrecke += dGefahreneStrecke;
                p_dAbschnittStrecke += dGefahreneStrecke;
                p_dTankinhalt -= dVerbrauch;
            } else {
                // Not enough fuel for full distance
                double dMoeglicheStrecke = (p_dTankinhalt * 100.0) / p_dVerbrauch;
                p_dGesamtStrecke += dMoeglicheStrecke;
                p_dAbschnittStrecke += dMoeglicheStrecke;
                p_dTankinhalt = 0;
            }
        }

        p_dGesamtZeit += dZeitschritt;
        p_dZeit = dGlobaleZeit;
    } else {
        std::cout << p_sName << " Hat keinen Stoff und kann nicht bewegen\n";
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
