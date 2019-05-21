/*
 * UserFunctions.cpp
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */


#include "UserFunctions.h"


int chooseMenuOption() {

	cout << "----------------------------------------------" << endl;
	cout << "             CHOOSE AN OPTION" << endl;
	cout << "----------------------------------------------" << endl << endl;

	unsigned int i;

	do {
		cout << "0: Load new graph and generate new table" << endl;
		cout << "1: Read new vehicle file" << endl;
		cout << "2: Display graph" << endl;
		cout << "3: Display accesible graph from the central" << endl;
		cout << "4: Read delivery file and calculate vehicle paths" << endl;
		cout << "5: Exit program" << endl;
		cout << "Option: ";
		cin >> i;
		cout << endl << endl;

		if(i > 5)
			cout << "Invalid option. Please try again." << endl << endl;

	} while(i > 5);

	return i;
}

int chooseDeliveryMenuOption() {
    cout << "----------------------------------------------" << endl;
    cout << "             CHOOSE AN OPTION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    unsigned int i;

    do {
        cout << "0: View all deliveries" << endl;
        cout << "1: View deliveries for a type of transport" << endl;
        cout << "2: View custom group of deliveries" << endl;
        cout << "3: Exit" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl << endl;

        if(i > 3)
            cout << "Invalid option. Please try again." << endl << endl;

    } while (i > 3);

    return i;
}

vector<Vehicle*> getVehiclesFromUserType(vector<Vehicle*> vehicles) {
    cout << "----------------------------------------------" << endl;
    cout << "             CHOOSE AN OPTION" << endl;
    cout << "----------------------------------------------" << endl << endl;

    unsigned int i;

    do {
        cout << "0: Bank" << endl;
        cout << "1: Financial Advice" << endl;
        cout << "2: ATM" << endl;
        cout << "3: Tax Advisor" << endl;
        cout << "4: Audit" << endl;
        cout << "5: Money Movement" << endl;
        cout << "Option: ";
        cin >> i;
        cout << endl << endl;

        if(i >= OTHER)
            cout << "Invalid option. Please try again." << endl << endl;

    } while (i >= OTHER);

    vector<Vehicle*> ret;

    for (auto vehicle : vehicles) {
        if (vehicle->getType() == i) {
            ret.push_back(vehicle);
        }
    }

    return ret;

}

vector<Vehicle*> userChosenVehicles(vector<Vehicle*> vehicles) {
    cout << "----------------------------------------------" << endl;
    cout << "            CHOOSE YOUR OPTIONS" << endl;
    cout << "----------------------------------------------" << endl << endl;

    vector<Vehicle*> ret;

    unsigned int i;

    do {
        cout << "0: Done!" << endl;
        for (auto vehicle : vehicles) {
            cout << vehicle->getID() << ": Vehicle " << vehicle->getID() << endl;
        }
        cout << "Option: ";
        cin >> i;
        cout << endl << endl;

        bool invalid = true;
        for (int j = 0; j < vehicles.size(); j++) {
            auto vehicle = vehicles.at(j);
            if (vehicle->getID() == i) {
                ret.push_back(vehicle);
                cout << "Vehicle with ID " << i << " added!" << endl << endl;
                vehicles.erase(vehicles.begin() + j);
                j--;
                invalid = false;
                break;
            }
        }

        if (i != 0 && invalid)
            cout << "Invalid option. Please try again." << endl << endl;

    } while (i != 0 && !vehicles.empty());

    return ret;
}

string chooseMap() {

	cout << "----------------------------------------------" << endl;
	cout << "                 Choose Map" << endl;
	cout << "----------------------------------------------" << endl << endl;

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



vector<Vehicle*> readCentralAndVehicles(Graph<Node> graph, Vertex<Node>* &central) {

    cout << "----------------------------------------------" << endl;
	cout << "          Central and Vehicle File" << endl;
    cout << "----------------------------------------------" << endl << endl;

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

	central = graph.findVertex(Node(centralID));

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



vector<Delivery> readDeliveries(Graph<Node> graph, Vertex<Node>* central) {

    cout << "----------------------------------------------" << endl;
	cout << "               Deliveries File" << endl;
    cout << "----------------------------------------------" << endl << endl;

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

		Delivery d(id, origin, dest, central);

		// os valores passados sao validos, se id != -1
		if(d.getID() != -1)
			deliveries.push_back(d);

	}


	if(numDeliveries != deliveries.size())
		cout << "Couldn't read all deliveries!" << endl;

	return deliveries;
}



void displayResults(vector<Vehicle*> vehicles, vector<Delivery> deliveries) {

	for (auto vehicle : vehicles) {
        cout << "For vehicle of id " << vehicle->getID() << ", the path is:\n";
        for (auto vertex : vehicle->getVehiclePath()) {
            cout << vertex->getInfo().getID() << ' ';
        }
        cout << '\n';
        cout << "And the deliveries are:\n";
        if (vehicle->getDeliveries().empty())
            cout << "-" << endl;

        for (auto delivery : vehicle->getDeliveries()) {
            cout << delivery.getID() << ' ';
        }
        cout << "\n\n";
    }


    cout << "And the deliveries that couldn't be made were:" << endl;
	if (deliveries.empty())
	    cout << "-" << endl;

    for(auto d : deliveries) {
 	   cout << d.getID() << " ";
    }


    cout << endl << endl;
}

