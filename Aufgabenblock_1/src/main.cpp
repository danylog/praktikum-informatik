#include <iostream>
#include "Fahrzeug.h"

using namespace std;

void vAufgabe_1(){
	const int iConstInteger = 10;
	const double dPi = 3.14;

	const int* iDynInteger = new int (33);
	delete iDynInteger;

	auto pUnique_ptr1 = make_unique<Fahrzeug>();
	auto pUnique_ptr2 = make_unique<Fahrzeug>("Auto1");

	auto pShared_ptr1 = make_shared<Fahrzeug>("Auto2");
	auto pShared_ptr2 = make_shared<Fahrzeug>("Auto3");

	cout << pShared_ptr1.use_count() << endl;

	auto pShared_ptr3 = pShared_ptr1;

	cout << pShared_ptr1.use_count() << endl;

	vector<shared_ptr<Fahrzeug>> fahrzeuge = {pShared_ptr1, pShared_ptr2};


	//wird mit uniqueptr nicht kompilieren


    for (const auto& fahrzeug : fahrzeuge) {
       cout << fahrzeug << endl; //displayes the memory addresses
    }


    fahrzeuge.push_back(make_shared<Fahrzeug>("Move-konstruktor"));

    shared_ptr<Fahrzeug> temp = make_shared<Fahrzeug>("Kopie-konstruktor");
    fahrzeuge.push_back(temp);

    fahrzeuge.clear();



}

int main(){
vAufgabe_1();
return 0;

}
