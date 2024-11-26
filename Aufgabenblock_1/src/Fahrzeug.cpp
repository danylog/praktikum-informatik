#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"

#include <iostream>
#include <iomanip>

using namespace std;

int Fahrzeug::p_iMaxID = 0;

//double dGlobaleZeit = 0.0;

Fahrzeug::Fahrzeug() : p_iID(++p_iMaxID), p_sName(""), p_dMaxGeschwindigkeit(0.0) {			//CONSTRUCTORS
    cout << "Default Fahrzeug erstellt mit ID " << p_iID << endl;
}

Fahrzeug::Fahrzeug(const string& name) :  p_iID(++p_iMaxID), p_sName(name), p_dMaxGeschwindigkeit(0.0) {
    cout << "Fahrzeug " << p_sName << " erstellt mit ID " << p_iID << endl;
}

Fahrzeug::Fahrzeug(const std::string& name, const double maxGeschwindigkeit):  p_iID(++p_iMaxID),p_sName(name), p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit : 0) {

}

Fahrzeug::~Fahrzeug() {
    cout << "Fahrzeug mit Name: " << p_sName << " und ID: " << p_iID << " geloescht" << endl;
}

void Fahrzeug::vAusgeben(ostream& os){																	//FUNKTIONEN
os << setw(4) << p_iID << " "
		<< setw(9) << setiosflags(std::ios::left)<< p_sName << resetiosflags(std::ios::left)<< " "
		<< setw(19)  << setiosflags(std::ios::fixed) << setprecision(2) << p_dMaxGeschwindigkeit << " "
		<< setw(15) << setprecision(2) << dGeschwindigkeit() << " "
		<< setw(14) << p_dGesamtStrecke;
}


double Fahrzeug::dTanken(double menge) {
    return 0.0;
}

void Fahrzeug::vSimulieren() {
    if (p_dZeit < dGlobaleZeit) {
        double dZeitschritt = dGlobaleZeit - p_dZeit;
        double dGefahreneStrecke = dGeschwindigkeit() * dZeitschritt;

        p_dGesamtStrecke += dGefahreneStrecke;
        p_dGesamtZeit += dZeitschritt;
        p_dZeit = dGlobaleZeit;
    }
}

ostream& operator<<(ostream& os, Fahrzeug& f) { //'<<' operator (ueberladet)
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
