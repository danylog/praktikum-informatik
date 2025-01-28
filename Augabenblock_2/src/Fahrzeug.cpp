#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Verhalten.h"
#include "Fahren.h"
#include "Parken.h"
#include <iostream>
#include <iomanip>



//double dGlobaleZeit = 0.0;


Fahrzeug::Fahrzeug(const std::string& name, const double maxGeschwindigkeit):  Simulationsobjekt(name), p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit : 0) {

}

Fahrzeug::~Fahrzeug() {
    std::cout << "Fahrzeug mit Name: " << p_sName << " geloescht" << std::endl;
}

void Fahrzeug::vAusgeben(std::ostream& os) const{																	//FUNKTIONEN
os << std::setw(4) << " "
		<< std::setw(9) << std::setiosflags(std::ios::left)<< p_sName << std::resetiosflags(std::ios::left)<< " "
		<< std::setw(19)  << std::setiosflags(std::ios::fixed) << std::setprecision(2) << p_dMaxGeschwindigkeit << " "
		<< std::setw(15) << std::setprecision(2) << dGeschwindigkeit() << " "
		<< std::setw(14) << p_dGesamtStrecke;
}


double Fahrzeug::dTanken(double menge) {
    return 0.0;
}

void Fahrzeug::vSimulieren() {
    // Calculate time difference since last update
    double dDeltaTime = dGlobaleZeit - p_dZeit;

    if (dDeltaTime > 0) {
        // Update position
        double dNewPosition = p_dGesamtStrecke + dDeltaTime * p_dMaxGeschwindigkeit;
        p_dGesamtStrecke = dNewPosition;

        // Update last simulation time
        p_dZeit = dGlobaleZeit;
    }
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
    p_dAbschnittStrecke = 0.0;
std::cout << "neuestrecke" << std::endl;
        p_pVerhalten = std::make_unique<Fahren>(weg);

}

void Fahrzeug::vNeueStrecke(Weg& weg, double startzeit) {
    p_dAbschnittStrecke = 0.0;

        p_pVerhalten = std::make_unique<Parken>(weg, startzeit);

}

std::ostream& operator<<(std::ostream& os, Fahrzeug& f) { //'<<' operator (ueberladet)
    f.vAusgeben(os);
    return os;
}

void Fahrzeug::vKopf(){  //kopffunktion
	std::cout << std::setw(0) << "ID"
			<< std::setw(7) << "Name"
			<< std::setw(25) << "MaxGeschwindigkeit"
			<< std::setw(16) << "Geschwindigkeit"
			<< std::setw(15) << "Gesamtstrecke"
			<< std::setw(10) << "Verbrauch"
			<< std::setw(13) << "Tankinhalt"
			<< std::setw(14) << "Tankvolumen"
			<< std::endl << "-----------------------------------------------------------------------------------------------------"<<std::endl;

}
