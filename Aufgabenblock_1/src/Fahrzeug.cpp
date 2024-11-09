#include "Fahrzeug.h"

#include <iostream>

using namespace std;

int Fahrzeug::p_iMaxID = 0;

Fahrzeug::Fahrzeug() : p_sName(""), p_iID(++p_iMaxID) {
    cout << "Default Fahrzeug erstellt mit ID " << p_iID << endl;
}

Fahrzeug::Fahrzeug(const string& name) : p_sName(name), p_iID(++p_iMaxID) {
    cout << "Fahrzeug " << p_sName << " erstellt mit ID " << p_iID << endl;
}

Fahrzeug::~Fahrzeug() {
    cout << "Fahrzeug mit Name: " << p_sName << " und ID: " << p_iID << " geloescht" << endl;
}
