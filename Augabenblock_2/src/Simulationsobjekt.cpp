#include "Simulationsobjekt.h"

#include <iostream>


int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt() : p_iID(++p_iMaxID), p_sName(""){
	std::cout << "Default simulationsobjekt erstellt mit id " << p_iID <<std::endl;
}

Simulationsobjekt::Simulationsobjekt(const std::string& name) : p_iID(++p_iMaxID), p_sName(name){
	std::cout << "Simulationsobjekt " << p_sName << " erstellt mit ID " << p_iID << std::endl;
}

Simulationsobjekt::~Simulationsobjekt(){
	std::cout << "wird geloescht" << std::endl;
}

// Gemeinsame Ausgabe-Methode
void Simulationsobjekt::vAusgeben(std::ostream& os) const {
    os << "Name: " << p_sName << ", ID: " << p_iID << ", Simulationszeit: " << p_dZeit;
}
