#include <iostream>
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"


double dGlobaleZeit = 0.0;


void vAufgabe_5(){

	Weg autobahn("A1", 4000.0, Tempolimit::Autobahn);
	auto audi = std::make_unique<Fahrzeug>("audi", 160.0);
	auto vw = std::make_unique<Fahrzeug>("audi", 150.0);
	auto mercedes = std::make_unique<Fahrzeug>("mercedes", 165.0);

	Weg::vKopf(std::cout);

	autobahn.vAusgeben(std::cout);
	std::cout << std::endl;
    autobahn.vAnnahme(std::move(audi));
    autobahn.vAnnahme(std::move(vw));
    autobahn.vAnnahme(std::move(mercedes));
	autobahn.vAusgeben(std::cout);
	std::cout << std::endl;
    double dTakt = 0.3; // Time step in hours (18 minutes)
    std::cout << "\nSimulating..." << std::endl;

    for(int i = 0; i < 3; ++i) {
        dGlobaleZeit += dTakt;
        std::cout << "\nTime step " << i+1 << " (t = " << dGlobaleZeit << "h):" << std::endl;

        autobahn.vSimulieren();

        Weg::vKopf(std::cout);
        autobahn.vAusgeben(std::cout);
        std::cout << std::endl;
    }
}
int main() {
vAufgabe_5();
    return 0;
}
