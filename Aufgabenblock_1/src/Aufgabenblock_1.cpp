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

void vAufgabe2(){
	/*Fahrzeug ist eine Basisklasse, und die Funktionalität für spezialisierte Fahrzeuge wie PKW oder Fahrrad wird in den abgeleiteten Klassen implementiert.
	 Ein Fahrzeug-Objekt hätte keine spezifischen Funktionen oder Zustände von PKW oder Fahrrad, daher wäre es unflexibel und unbrauchbar für die Simulation. */
	int pkws, fahrraeder;
	cout << "Anzahl der PKWs: ";
	cin >> pkws;
	cout << "Anzahl der Fahrraeder: ";
	cin >> fahrraeder;

	cout << pkws << " " << fahrraeder << endl;

	std::vector<std::unique_ptr<Fahrzeug>> vecFahrzeuge;

//	vector<unique_ptr<Fahrzeug>)> vecFahrzeuge;
	const uint8_t verbrauch = 4;

	for(int i = 1; i <= pkws; i++){
		string name = "pkw" + to_string(i);
		double maxGeschwindigkeit = 150 +i*10;
		vecFahrzeuge.push_back(make_unique<PKW>(name, maxGeschwindigkeit, verbrauch));
	}
	for(int i = 1; i <= fahrraeder; i++){
		string name = "fahrrad" + to_string(i);
		double maxGeschwindigkeit = 15 +i*10;
		vecFahrzeuge.push_back(make_unique<Fahrrad>(name, maxGeschwindigkeit));
	}

    const double dZeittakt = 0.5;
    const double dSimulationEnde = 5.0;

    vKopf();

    while (dGlobaleZeit < dSimulationEnde) {
        dGlobaleZeit += dZeittakt;
        	cout << "Zeittakt " << dGlobaleZeit << " von " << dSimulationEnde << endl;




        for (auto& fahrzeug : vecFahrzeuge) {
            fahrzeug->vSimulieren();
            fahrzeug->vAusgeben();
            if(dGlobaleZeit == 3.0){
                if (auto pkw = dynamic_cast<PKW*>(fahrzeug.get())) {
                    double getankt = pkw->dTanken();
                    cout << endl << "PKW " << pkw->sName() << " hat " << getankt << " Liter getankt.";
                }
            }
            cout << endl;

        }


    }



}


int main() {
	vAufgabe2();
	//vAufgabe1a();
return 0;
}



