/*
 * UserFunctions.cpp
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */


#include "UserFunctions.h"
// #include "consoleColors.h"

string chooseMap() {

    // setColor(CONSOLE_YELLOW, CONSOLE_BLACK);
	cout << "----------------------------------------------" << endl;
	cout << "                 Choose Map" << endl;
	cout << "----------------------------------------------" << endl;

	cout << endl;

	unsigned int i;

	do {
        // setColor(CONSOLE_LIGHTGREEN);
		cout << "Please select the desired map:" << endl;
		// setColor(CONSOLE_LIGHTGRAY);
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



vector<Vehicle*> readCentralAndVehicles(Graph<Node> graph) {

	cout << "--------------------------" << endl;
	cout << "Central and Vehicle File" << endl;
	cout << "--------------------------" << endl << endl;

	string fileName;
	ifstream stream;

	do {
		cout << "Please insert the central and vehicles file name:" << endl;
		cin >> fileName;

		stream.open(fileName);
		if(!stream)
			cout << "Couldn't open file! Please insert another one." << endl;

	} while(!stream);


	string line;


	int centralID;
	stream >> centralID;

	Vertex<Node>* central = graph.findVertex(Node(centralID));

	central->getInfo().setType(CENTRAL);

	// limpa o resto da linha
	getline(stream, line);



	int numVehicles;
	stream >> numVehicles;

	// limpa o resto da linha
	getline(stream, line);


	vector<Vehicle*> vehicles;

	while(getline(stream, line)) {

		stringstream ss(line);

		int id;
		string typeStr;

		ss >> id >> typeStr;

		TYPE type;

		if(typeStr == "BANK")
			type = BANK;
		else if(typeStr == "FIN_ADVICE")
			type = FIN_ADVICE;
		else if(typeStr == "ATM")
			type = ATM;
		else if(typeStr == "TAX_ADVISOR")
			type = TAX_ADVISOR;
		else if(typeStr == "AUDIT")
			type = AUDIT;
		else if(typeStr == "MONEY_MOV")
			type = MONEY_MOV;

		vehicles.push_back(new Vehicle(id, type, central));
	}

	if(vehicles.size() != numVehicles)
		cout << "Couldn't read all vehicles!" << endl;


	return vehicles;
}



vector<Delivery> readDeliveries(Graph<Node> graph) {

	cout << "--------------------------" << endl;
	cout << "Deliveries File" << endl;
	cout << "--------------------------" << endl << endl;

	string fileName;
	ifstream stream;

	do {
		cout << "Please insert the deliveries file name:" << endl;
		cin >> fileName;

		stream.open(fileName);
		if(!stream)
			cout << "Couldn't open file! Please insert another one." << endl;

	} while(!stream);


	string line;

	int numDeliveries;
	stream >> numDeliveries;

	// limpa o resto da linha
	getline(stream, line);

	vector<Delivery> deliveries;

	while(getline(stream, line)) {

		stringstream ss(line);

		int id, originId, destId;
		ss >> id >> originId >> destId;

		Vertex<Node>* origin = graph.findVertex(Node(originId));
		Vertex<Node>* dest = graph.findVertex(Node(destId));

		Delivery d(id, origin, dest);

		// os valores passados sao validos, se id != -1
		if(id != -1)
			deliveries.push_back(d);

	}


	if(numDeliveries != deliveries.size())
		cout << "Couldn't read all deliveries!" << endl;

	return deliveries;
}

