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

double dGlobaleZeit = 0.0;



//void vAufgabe1a(){
//	vector<unique_ptr<Fahrzeug>> vecFahrzeuge;
//	 vecFahrzeuge.push_back(make_unique<Fahrzeug>("fahrzeug1", 30.0));
//	 vecFahrzeuge.push_back(make_unique<PKW>("audi", 240.0, 8.0));
//	 vecFahrzeuge.push_back(make_unique<Fahrrad>("fahrrad1", 14.0));
//	Fahrzeug::vKopf();
//
//    const double dZeittakt = 0.5;
//    const double dSimulationEnde = 5.0;
//
//    while (dGlobaleZeit < dSimulationEnde) {
//        dGlobaleZeit += dZeittakt;
//
//        for (auto& fahrzeug : vecFahrzeuge) {
//            fahrzeug->vSimulieren();
//            fahrzeug->vAusgeben();
//            cout << endl;
//        }
//
//        cout << "----------------------------------------------------------------------" << endl;
//    }
//}

void vAufgabe2(){
	/*Fahrzeug ist eine Basisklasse, und die Funktionalität für spezialisierte Fahrzeuge wie PKW oder Fahrrad wird in den abgeleiteten Klassen implementiert.
	 Ein Fahrzeug-Objekt hätte keine spezifischen Funktionen oder Zustände von PKW oder Fahrrad, daher wäre es unflexibel und unbrauchbar für die Simulation. */
	int pkws, fahrraeder;
	std::cout << "Anzahl der PKWs: ";
	std::cin >> pkws;
	std::cout << "Anzahl der Fahrraeder: ";
	std::cin >> fahrraeder;

	std::cout << pkws << " " << fahrraeder << std::endl;

	std::vector<std::unique_ptr<Fahrzeug>> vecFahrzeuge;

//	vector<unique_ptr<Fahrzeug>)> vecFahrzeuge;
	const uint8_t verbrauch = 4;

	for(int i = 1; i <= pkws; i++){
		std::string name = "pkw" + std::to_string(i);
		double maxGeschwindigkeit = 150 +i*10;
		vecFahrzeuge.push_back(std::make_unique<PKW>(name, maxGeschwindigkeit, verbrauch));
	}
	for(int i = 1; i <= fahrraeder; i++){
		std::string name = "fahrrad" + std::to_string(i);
		double maxGeschwindigkeit = 15 +i*10;
		vecFahrzeuge.push_back(std::make_unique<Fahrrad>(name, maxGeschwindigkeit));
	}

    const double dZeittakt = 0.5;
    const double dSimulationEnde = 5.0;

    Fahrzeug::vKopf();

    while (dGlobaleZeit < dSimulationEnde) {
        dGlobaleZeit += dZeittakt;
        std::cout << "Zeittakt " << dGlobaleZeit << " von " << dSimulationEnde << std::endl;




        for (auto& fahrzeug : vecFahrzeuge) {
            fahrzeug->vSimulieren();
            std::cout << *fahrzeug;
            if(dGlobaleZeit == 3.0){
                if (auto pkw = dynamic_cast<PKW*>(fahrzeug.get())) {
                    double getankt = pkw->dTanken();
                    std::cout << std::endl << "PKW " << pkw->sName() << " hat " << getankt << " Liter getankt.";
                }
            }
            std::cout << std::endl;
        }
    }
}


void vAufgabe3() {
    Fahrzeug fahrzeug1("Fahrzeug1", 120.0);
    std::cout << "Fahrzeug " << fahrzeug1.sName()
              << ", MaxGeschwindigkeit = " << fahrzeug1.dMaxGeschwindigkeit()
              << ", ID = " << fahrzeug1.iID() << std::endl;

    Fahrzeug fahrzeug2("Fahrzeug2", 100.0);
    std::cout << "Fahrzeug " << fahrzeug2.sName()
              << ", MaxGeschwindigkeit = " << fahrzeug2.dMaxGeschwindigkeit()
              << ", ID = " << fahrzeug2.iID() << std::endl;

    fahrzeug2 = fahrzeug1;
    std::cout << "Nach Zuweisung: Fahrzeug " << fahrzeug2.sName()
              << ", MaxGeschwindigkeit = " << fahrzeug2.dMaxGeschwindigkeit()
              << ", ID = " << fahrzeug2.iID() << std::endl;
}




int main() {
	vAufgabe2();
	//vAufgabe1a();
	//vAufgabe3();
return 0;
}



