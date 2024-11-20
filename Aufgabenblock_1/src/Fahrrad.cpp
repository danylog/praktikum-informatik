#include "Fahrrad.h"
#include <iostream>
#include <cmath>

Fahrrad::Fahrrad(const std::string& name, const double maxGeschwindigkeit)
    : Fahrzeug(name, maxGeschwindigkeit) {}

void Fahrrad::vSimulieren() {
    double dZeitschritt = dGlobaleZeit - p_dZeit;

    if (dZeitschritt > 0.0) {


        double dGefahreneStrecke = dSpeed() * dZeitschritt;
        p_dGesamtStrecke += dGefahreneStrecke;
        p_dGesamtZeit += dZeitschritt;
        p_dZeit = dGlobaleZeit;
    }
}

double Fahrrad::dSpeed(){
	const int iGefahren = p_dGesamtStrecke/20;
//	std::cout << pow(0.9, iGefahren);
	if(iGefahren >0){
		return p_dMaxGeschwindigkeit*(pow(0.9, iGefahren)) < 12 ? 12 : p_dMaxGeschwindigkeit*(pow(0.9, iGefahren));
	}else{
		return p_dMaxGeschwindigkeit;
	}

}
