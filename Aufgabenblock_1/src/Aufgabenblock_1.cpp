//============================================================================
// Name        : Aufgabenblock_1.cpp
// Author      : Danylo Galytskyy
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
using namespace std;

class Fahrzeug{
private:
	string p_sName;
	const int p_iID;
	static int p_iMaxID;
public:
	Fahrzeug()
	: p_sName(""), p_iID(++p_iMaxID){
		cout << "Default Fahrzeug erstellt mit ID " << p_iID << endl;
	}
	Fahrzeug(const string name)
	: p_sName(name),  p_iID(++p_iMaxID){
		cout << "Fahrzeug " << p_sName << " erstellt mit ID " << p_iID << endl;
	}
	virtual ~Fahrzeug(){
		cout << "Fahrzeug mit Name: " << p_sName << " und ID: " << p_iID << " geloescht" << endl;
	}
};

int Fahrzeug::p_iMaxID = 0;

int main() {
    Fahrzeug f1;
    Fahrzeug f2("Schiff");
    Fahrzeug f3("Fahrrad");

    return 0;
}
