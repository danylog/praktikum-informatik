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

using namespace std;

double dGlobaleZeit = 0.0;

void vKopf(){
	cout << setw(0) << "ID" << setw(7) << "Name" << setw(25) << "MaxGeschwindigkeit" << setw(16) << "Gesamtstrecke" << endl << "----------------------------------------------------"<<endl;
}

int main() {
    Fahrzeug f1;
    Fahrzeug f2("Schiff", 20);
    Fahrzeug f3("Fahrrad", 10);

    PKW pkw("audi", 200);


    vKopf();
    pkw.vAusgeben();
    std::cout << std::endl;
    f1.vAusgeben();
    std::cout << std::endl;
    f2.vAusgeben();
    std::cout << std::endl;
    f3.vAusgeben();
    std::cout << std::endl;

    return 0;
}


