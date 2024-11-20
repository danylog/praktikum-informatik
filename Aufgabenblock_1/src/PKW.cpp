#include "PKW.h"

PKW::PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen):
Fahrzeug(name, maxGeschwindigkeit),
		p_dVerbrauch(verbrauch),
		p_dTankvolumen(tankvolumen?tankvolumen:55),
		p_dTankinhalt(tankvolumen/2)
{

	std::cout<<"Constuctor fuer ein pkw gerufen" << std::endl;

}

void PKW::vAusgeben() {
    Fahrzeug::vAusgeben();
    std::cout << std::fixed << std::setprecision(2)
              << std::setw(12) << p_dVerbrauch << " "
              << std::setw(12) << p_dTankinhalt << " "
              << std::setw(12) << p_dTankvolumen << std::endl;
}



double PKW::dTanken(double menge){
	double dGetankt = 0.0;
    if (menge == std::numeric_limits<double>::infinity()) {
        dGetankt = p_dTankvolumen - p_dTankinhalt;
        p_dTankinhalt = p_dTankvolumen;
    } else {
        dGetankt = std::min(menge, p_dTankvolumen - p_dTankinhalt);
        p_dTankinhalt += dGetankt;
    }

    return dGetankt;
}

double PKW::dSpeed(){
    return (p_dTankinhalt > 0) ? p_dMaxGeschwindigkeit : 0; // Return speed based on tank state
}

void PKW::vSimulieren() {
    if (p_dTankinhalt > 0.0) {
        double dZeitschritt = dGlobaleZeit - p_dZeit;

        if (dZeitschritt > 0.0) {
            double dFahrbareStrecke = dSpeed() * dZeitschritt;
            double dMaxStreckeMitTank = (p_dTankinhalt / p_dVerbrauch) * 100.0;

            double dTatsaechlicheStrecke = std::min(dFahrbareStrecke, dMaxStreckeMitTank);
            double dVerbrauch = (dTatsaechlicheStrecke / 100.0) * p_dVerbrauch;

            p_dGesamtStrecke += dTatsaechlicheStrecke;
            p_dTankinhalt -= dVerbrauch;

            p_dGesamtZeit += dZeitschritt;
            p_dZeit = dGlobaleZeit;
        }
    } else {
        std::cout << p_sName << " Hat keinen Stoff und kann nicht bewegen\n";
    }}
