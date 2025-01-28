#include "PKW.h"
#include "Tempolimit.h"
#include <iostream>
#include "Verhalten.h"
#include "Weg.h"
#include "Simuclient.h"
#include "Kreuzung.h"


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



double PKW::dTanken(double menge) {
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

        const Weg& weg = p_pVerhalten->getWeg();
        double tempLimit = weg.getTempolimit();


        return std::min(p_dMaxGeschwindigkeit, tempLimit);

    }
}

// In PKW.cpp
void PKW::vSimulieren() {

    if (p_dTankinhalt > 0) {
        double timeDelta = dGlobaleZeit - p_dZeit;
        if (timeDelta > 0) {
            double oldDistance = p_dGesamtStrecke;
            Fahrzeug::vSimulieren();

            // Calculate and subtract fuel consumption
            double distance = p_dGesamtStrecke - oldDistance;
            double consumption = (distance / 100.0) * p_dVerbrauch;

            if (consumption > p_dTankinhalt) {
                // Not enough fuel for complete distance
                double possibleDistance = (p_dTankinhalt / p_dVerbrauch) * 100.0;
                p_dGesamtStrecke = oldDistance + possibleDistance;
                p_dAbschnittStrecke = oldDistance + possibleDistance;
                p_dTankinhalt = 0;
            } else {
                p_dTankinhalt -= consumption;
            }
        }
    }
}

// In PKW class
void PKW::vKreuzungErreicht() {
    // Get a reference to the road
    const Weg& weg = p_pVerhalten->getWeg();

    // Get the target intersection
    if (auto zielKreuzung = weg.getZielKreuzung()) {
        double tankinhalt = getTankinhalt();  // Use your existing getter
        if (tankinhalt < getTankvolumen()) {  // Use your existing getter
            double benoetigteMenge = getTankvolumen() - tankinhalt;
            double getankteMenge = zielKreuzung->dTanken(benoetigteMenge);
            dTanken(getankteMenge);
        }
    }
}

void PKW::vZeichnen(const Weg& weg) const {
    // Implementation for drawing the PKW on the road


    	double relativePosition = p_dAbschnittStrecke / weg.getLength();


    // Draw the PKW using the SimuClient functions
    bZeichnePKW(getName(),  // vehicle name
                weg.getName(),  // road name
                relativePosition,  // relative position on the road (0.0 to 1.0)
                dGeschwindigkeit(),  // current speed
                getTankinhalt());  // current fuel level
}
