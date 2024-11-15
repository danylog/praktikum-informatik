#include "Fahrzeug.h"

#include <iostream>
#include <iomanip>

using namespace std;

int Fahrzeug::p_iMaxID = 0;

extern double dGlobaleZeit;

Fahrzeug::Fahrzeug() : p_sName(""), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(0.0) {
    cout << "Default Fahrzeug erstellt mit ID " << p_iID << endl;
}

Fahrzeug::Fahrzeug(const string& name) : p_sName(name), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit(0.0) {
    cout << "Fahrzeug " << p_sName << " erstellt mit ID " << p_iID << endl;
}

Fahrzeug::Fahrzeug(const std::string& name, const double maxGeschwindigkeit): p_sName(name), p_iID(++p_iMaxID), p_dMaxGeschwindigkeit((maxGeschwindigkeit > 0) ? maxGeschwindigkeit : 0) {

}

Fahrzeug::~Fahrzeug() {
    cout << "Fahrzeug mit Name: " << p_sName << " und ID: " << p_iID << " geloescht" << endl;
}

void Fahrzeug::vAusgeben(){
cout << setw(4) << p_iID << " "
		<< setw(9) << setiosflags(std::ios::left)<< p_sName << resetiosflags(std::ios::left)<< " "
		<< setw(19)  << setiosflags(std::ios::fixed) << setprecision(2) << p_dMaxGeschwindigkeit << " "
		<< setw(16) << p_dGesamtStrecke;
}


