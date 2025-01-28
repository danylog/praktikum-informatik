#include "Weg.h"
#include "Fahrzeug.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "Fahrausnahme.h"
#include "Losfahren.h"
#include "Streckenende.h"
#include <vector>
#include "Kreuzung.h"
#include <random>
//std::string& defaultname = "DefaultWeg";


Weg::Weg() : Simulationsobjekt("weg"), p_dLaenge(100), p_eTempolimit(Tempolimit::Autobahn){};

Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit)
    : Simulationsobjekt(name),
      p_dLaenge(laenge),
      p_eTempolimit(tempolimit) {}


Weg::~Weg(){}

// In Weg.cpp


void Weg::vSimulieren() {
    p_pFahrzeuge.vAktualisieren();

    // Make a copy of the vehicles to process
    std::vector<Fahrzeug*> fahrzeuge_to_process;
    for (const auto& fahrzeug : p_pFahrzeuge) {
        fahrzeuge_to_process.push_back(fahrzeug.get());
    }

    // Process each vehicle
    for (Fahrzeug* fahrzeug : fahrzeuge_to_process) {
        try {
            // Find the corresponding unique_ptr in the list
            auto it = std::find_if(p_pFahrzeuge.begin(), p_pFahrzeuge.end(),
                [fahrzeug](const std::unique_ptr<Fahrzeug>& ptr) {
                    return ptr.get() == fahrzeug;
                });

            if (it != p_pFahrzeuge.end()) {
                (*it)->vSimulieren();
                (*it)->vZeichnen(*this);
            }
        }
        catch (const Streckenende& ausnahme) {
            ausnahme.vBearbeiten();
            // Vehicle will be removed in vAktualisieren()
        }
        catch (const Losfahren& ausnahme) {
            ausnahme.vBearbeiten();
            // Vehicle's behavior is updated, but stays in the list
        }
    }

    p_pFahrzeuge.vAktualisieren();
}




void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
    fahrzeug->vNeueStrecke(*this);  // Set behavior first
    p_pFahrzeuge.push_back(std::move(fahrzeug));
    p_pFahrzeuge.vAktualisieren();
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    fahrzeug->vNeueStrecke(*this, startzeit);  // Set parking behavior first
    p_pFahrzeuge.push_front(std::move(fahrzeug));
    p_pFahrzeuge.vAktualisieren();
}
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fahrzeug) {
    std::unique_ptr<Fahrzeug> result = nullptr;

    for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {
        if (it->get() == &fahrzeug) {
            // Transfer ownership to result
            result = std::move(*it);
            // Mark for removal from list
            p_pFahrzeuge.erase(it);
            break;
        }
    }

    // Process the removal
    p_pFahrzeuge.vAktualisieren();
    return result;
}

void Weg::vAusgeben(std::ostream& out) const {
    Simulationsobjekt::vAusgeben(out);
    out << std::setw(20) << p_sName
        << std::setw(20) << p_dLaenge << std::endl;

    // List all vehicles on this road
    for (const auto& fahrzeug : p_pFahrzeuge) {
        out << *fahrzeug << std::endl;
    }
}

void Weg::vKopf(std::ostream& os) {
    os << std::setw(5) << "ID"
       << " | " << std::setw(10) << "Name"
       << " | " << std::setw(10) << "Laenge"
       << " | " << "Fahrzeuge" << "\n"
       << std::string(50, '-') << "\n"; // @suppress("Symbol is not resolved")
}

std::shared_ptr<Weg> Weg::getRandomNextWeg() const {
    if (!p_pZielKreuzung || p_pZielKreuzung->getWege().empty()) {
        return nullptr;
    }

    // Create random number generator
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Get list of outgoing roads from target intersection
    const auto& wege = p_pZielKreuzung->getWege();

    // Create distribution for the size of the roads list
    std::uniform_int_distribution<> dis(0, wege.size() - 1);

    // Get random index
    auto it = wege.begin();
    std::advance(it, dis(gen));

    return *it;
}

void vAufgabe_8() {
    // Create intersections with different gas station volumes
    auto kreuzung1 = std::make_shared<Kreuzung>("Kreuzung1", 1000);  // Large gas station
    auto kreuzung2 = std::make_shared<Kreuzung>("Kreuzung2");        // No gas station
    auto kreuzung3 = std::make_shared<Kreuzung>("Kreuzung3", 500);   // Medium gas station
    auto kreuzung4 = std::make_shared<Kreuzung>("Kreuzung4", 300);   // Small gas station

    // Connect intersections with roads
    Kreuzung::vVerbinde("W12", "W21", 100, kreuzung1, kreuzung2, Tempolimit::Landstrasse);
    Kreuzung::vVerbinde("W23", "W32", 150, kreuzung2, kreuzung3, Tempolimit::Innerorts);
    Kreuzung::vVerbinde("W34", "W43", 80,  kreuzung3, kreuzung4, Tempolimit::Autobahn);
    Kreuzung::vVerbinde("W41", "W14", 120, kreuzung4, kreuzung1, Tempolimit::Landstrasse);

    // Create vehicles with different tank volumes
    auto pkw1 = std::make_unique<PKW>("BMW", 120, 60);    // Speed 120, tank 60
    auto pkw2 = std::make_unique<PKW>("Audi", 150, 55);   // Speed 150, tank 55
    auto pkw3 = std::make_unique<PKW>("VW", 100, 40);     // Speed 100, tank 40
    auto fahrrad = std::make_unique<Fahrrad>("Rad1", 30); // Speed 30

    // Get first road from Kreuzung1 to start vehicles
    auto startWeg = kreuzung1->getWege().front();

    // Start vehicles at different times
    startWeg->vAnnahme(std::move(pkw1));
    startWeg->vAnnahme(std::move(pkw2), 2);  // Starts after 2 time units
    startWeg->vAnnahme(std::move(pkw3), 4);  // Starts after 4 time units
    startWeg->vAnnahme(std::move(fahrrad));

    // Simulation loop
    for (double time = 0; time < 24; time += 0.25) {
        std::cout << "\n\nZeit: " << time << " Stunden\n";
        std::cout << "==============================\n";

        // Simulate all intersections
        kreuzung1->vSimulieren();
        kreuzung2->vSimulieren();
        kreuzung3->vSimulieren();
        kreuzung4->vSimulieren();

        // Print gas station status
        std::cout << "\nTankstellen-Status:\n";
        std::cout << "Kreuzung1: " << kreuzung1->getTankstellenInhalt() << " L\n";
        std::cout << "Kreuzung3: " << kreuzung3->getTankstellenInhalt() << " L\n";
        std::cout << "Kreuzung4: " << kreuzung4->getTankstellenInhalt() << " L\n";

        // Increment global time
        dGlobaleZeit += 0.25;
    }
}


Weg* Weg::getRandomNextWeg() const {
           // Lock the weak_ptr to get a shared_ptr
           if (auto zielKreuzung = p_pZielKreuzung.lock()) {
               if (zielKreuzung->getWege().empty()) {
                   return nullptr;
               }

               static std::random_device rd;
               static std::mt19937 gen(rd());

               const auto& wege = zielKreuzung->getWege();
               std::uniform_int_distribution<> dis(0, wege.size() - 1);

               auto it = wege.begin();
               std::advance(it, dis(gen));

               return it->get();
           }
           return nullptr;
       }


std::ostream& operator<<(std::ostream& os, const Weg& weg) {
    weg.vAusgeben(os); // Call the vAusgeben function
    return os; // Return the stream reference
}

