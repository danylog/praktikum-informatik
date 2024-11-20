//============================================================================
// Name        : Aufgabenblock_1.cpp
// Author      : Danylo Galytskyy
// Version     :
//============================================================================

#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>

using namespace std;

double dGlobaleZeit = 0.0;

void vKopf(){
	cout << setw(0) << "ID" << setw(7) << "Name" << setw(25) << "MaxGeschwindigkeit" << setw(16) << "Geschwindigkeit" << setw(16) << "Gesamtstrecke" << setw(13) << "Verbrauch" << setw(12) << "Tankinhalt" << setw(16) << "Tankvolumen" << endl << "------------------------------------------------------------------------------------------"<<endl;
}


void vAufgabe1a(){
	vector<unique_ptr<Fahrzeug>> vecFahrzeuge;

	 vecFahrzeuge.push_back(make_unique<Fahrzeug>("fahrzeug1", 30.0));
	 vecFahrzeuge.push_back(make_unique<PKW>("audi", 240.0, 8.0));
	 vecFahrzeuge.push_back(make_unique<Fahrrad>("fahrrad1", 14.0));
	vKopf();

    const double dZeittakt = 0.5;
    const double dSimulationEnde = 5.0;

    while (dGlobaleZeit < dSimulationEnde) {
        dGlobaleZeit += dZeittakt;

        for (auto& fahrzeug : vecFahrzeuge) {
            fahrzeug->vSimulieren();
            fahrzeug->vAusgeben();
            cout << endl;
        }

        cout << "----------------------------------------------------------------------" << endl;
    }
}

int main() {
	vAufgabe1a();
return 0;
}



