/*
 * UserFunctions.cpp
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */


#include "UserFunctions.h"


string chooseMap() {

	cout << "-----------------------" << endl;
	cout << "Choose Map" << endl;
	cout << "-----------------------" << endl << endl;

	unsigned int i;

	do {

		cout << "Please select the desired map:" << endl;
		cout << "0 -> Aveiro" << endl;
		cout << "1 -> Braga" << endl;
		cout << "2 -> Coimbra" << endl;
		cout << "3 -> Ermesinde" << endl;
		cout << "4 -> Fafe" << endl;
		cout << "5 -> Gondomar" << endl;
		cout << "6 -> Lisboa" << endl;
		cout << "7 -> Maia" << endl;
		cout << "8 -> Porto" << endl;
		cout << "9 -> Portugal" << endl;
		cout << "10 -> Viseu" << endl;
		cout << "11 -> Teste" << endl << endl;

		cout << "Value: ";

		cin >> i;
		cout << endl;

		if(i > 11)
			cout << "Invalid map number!" << endl;

	} while(i > 11);


	string maps[12] = {"Aveiro", "Braga", "Coimbra", "Ermesinde", "Fafe", "Gondomar",
					   "Lisboa", "Maia", "Porto", "Portugal", "Viseu", "Teste"};

	cin.ignore(100, '\n');

	return maps[i];
}


