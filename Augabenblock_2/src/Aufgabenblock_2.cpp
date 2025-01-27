#include <iostream>
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"
#include <iomanip>
#include <memory>
#include "PKW.h"
#include "Fahrausnahme.h"
#include "Simuclient.h"

double dGlobaleZeit = 0.0;


//void vAufgabe_5_5(){
//    Weg autobahn("A1", 1000.0, Tempolimit::Autobahn);
//
//    auto bmw = std::make_unique<PKW>("BMW", 160.0);
//    auto vw = std::make_unique<PKW>("VW", 130.0);
//    auto audi = std::make_unique<PKW>("AUDI", 140.0);
//
//    autobahn.vAnnahme(std::move(bmw));
//    autobahn.vAnnahme(std::move(vw), 0.2);
//    autobahn.vAnnahme(std::move(audi), 2.0);
//
//    double dTakt = 0.5;
//    for(int i = 0; i < 20; ++i) {
//        dGlobaleZeit += dTakt;
//        std::cout << "\nTime step " << i+1 << " (t = " << dGlobaleZeit << "h):" << std::endl;
//        autobahn.vSimulieren();
//        autobahn.vAusgeben(std::cout);
//
//        std::cout << std::endl;
//    }
//
//
//
//}
//
//void vAufgabe_5(){
//
//    Weg autobahn("A1", 1000.0, Tempolimit::Autobahn);
//
//    // Create vehicles
//    auto bmw = std::make_unique<PKW>("BMW", 160.0);
//    auto vw = std::make_unique<PKW>("VW", 130.0);
//    auto audi = std::make_unique<PKW>("AUDI", 140.0);
//
//    // Add vehicles to the road - some driving, some parking
//    autobahn.vAnnahme(std::move(bmw));  // Driving
//    autobahn.vAnnahme(std::move(vw), 1.0);  // Parked, starts at t=1.0h
//    autobahn.vAnnahme(std::move(audi), 2.0);  // Parked, starts at t=2.0h
//
//    std::cout << "\nInitial state (t = " << dGlobaleZeit << "):" << std::endl;
//    Weg::vKopf(std::cout);
//    autobahn.vAusgeben(std::cout);
//    std::cout << std::endl;
//
//    // Simulate for several time steps
//    double dTakt = 0.5; // Time step in hours (30 minutes)
//    for(int i = 0; i < 5; ++i) {
//        dGlobaleZeit += dTakt;
//        std::cout << "\nTime step " << i+1 << " (t = " << dGlobaleZeit << "h):" << std::endl;
//
//        autobahn.vSimulieren();
//
//        Weg::vKopf(std::cout);
//        autobahn.vAusgeben(std::cout);
//        std::cout << std::endl;
//    }
//}

void vAufgabe6(){
	bInitialisiereGrafik(1100,1100);

	Weg landstrasse("L1", 500.0, Tempolimit::Landstrasse);    // 100 km/h
	    Weg autobahn("A1", 1000.0, Tempolimit::Autobahn);         // No limit
	    int k1[] = {10, 100, static_cast<int>(10+landstrasse.getLength()), 100};
	    int k2[] = {10, 300, static_cast<int>(10+autobahn.getLength()), 300};
	    bZeichneStrasse(landstrasse.getName(), "1", landstrasse.getLength(), 2, k1);
	    bZeichneStrasse(autobahn.getName(), "2", landstrasse.getLength(), 2, k2);


	    // Create vehicles (PKWs with different max speeds)
	    auto vw = std::make_unique<PKW>("VW", 130.0, 0.1);        // Max 130 km/h
	    auto porsche = std::make_unique<PKW>("Porsche", 180.0, 0.01, 55.0); // Max 180 km/h
	    auto bmw = std::make_unique<PKW>("BMW", 160.0, 0.1);      // Max 160 km/h

	    PKW* vwptr = bmw.get();
	    // Add vehicles to roads
	    landstrasse.vAnnahme(std::move(vw));
	    autobahn.vAnnahme(std::move(porsche));
	    landstrasse.vAnnahme(std::move(bmw));

	    double dTakt = 0.5;
	    for(int i = 0; i < 1000; ++i) {
	    	vSetzeZeit(dGlobaleZeit);

	        dGlobaleZeit += dTakt;
	        std::cout << "\nTime step " << i+1 << " (t = " << dGlobaleZeit << "h):" << std::endl;

	        std::cout << "\nLandstrasse (Speed limit 100 km/h):" << std::endl;
	        landstrasse.vSimulieren();
	        landstrasse.vAusgeben(std::cout);

	        std::cout << "\nAutobahn (No speed limit):" << std::endl;
	        autobahn.vSimulieren();
	        autobahn.vAusgeben(std::cout);
	        vSleep(500);
	    }


}

void vAufgabe7(){


}
int main() {
	//vAufgabe5();
//vAufgabe_5_5();
	vAufgabe6();
	//vAufgabe7();
    return 0;
}
