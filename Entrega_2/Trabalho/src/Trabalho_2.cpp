//============================================================================
// Name        : Trabalho_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <map>
#include <utility>

#include "UserFunctions.h"
#include "graphviewer.h"
#include "GVFunctions.h"
#include "GraphFunctions.h"
#include "Node.h"
#include "Vehicle.h"
#include "Manager.h"
// #include "consoleColors.h"

using namespace std;

int main() {

    // clearScreen();
	string map = chooseMap();

	cout << "Building graph..." << endl;
	Graph<Node> graph = loadGraph(map);
    // setColor(CONSOLE_LIGHTGREEN);
    cout << "Done!" << endl << endl;
    // setColor(CONSOLE_LIGHTGRAY);


	cout << "Removing useless edges..." << endl;
	removeUselessEdges(graph);
    // setColor(CONSOLE_LIGHTGREEN);
    cout << "Done!" << endl << endl;
    // setColor(CONSOLE_LIGHTGRAY);


	cout << "Building table..." << endl;
	Table table = buildDijkstraTable(graph);
    // setColor(CONSOLE_LIGHTGREEN);
    cout << "Done!" << endl << endl;
    // setColor(CONSOLE_LIGHTGRAY);


//    for (Table::iterator it = table.begin(); it != table.end(); it++) {
//        cout << "first vertex: " << it->first.first->getInfo().getID() << "   -   ";
//        cout << "second vertex: " << it->first.second->getInfo().getID() << "\n";
//        cout << "distance: " << it->second.first << "   -   ";
//        cout << "path: " << it->second.second->getInfo().getID() << "\n\n";
//    }

//    Vertex<Node>* central = graph.findVertex(Node(5));
//    central->getInfo().setType(CENTRAL);
//
//    Vehicle* v1 = new Vehicle(1, BANK, central);
//    Vehicle* v2 = new Vehicle(2, BANK, central);
//    vector<Vehicle*> vehicles;
//    vehicles.push_back(v1);
//    vehicles.push_back(v2);
//
//    Delivery d1(1, graph.findVertex(Node(1)), graph.findVertex(Node(2)));
//    Delivery d2(2, graph.findVertex(Node(3)), graph.findVertex(Node(4)));
//    Delivery d3(3, graph.findVertex(Node(6)), graph.findVertex(Node(8)));
//    Delivery d4(4, graph.findVertex(Node(7)), graph.findVertex(Node(8)));
//    Delivery d5(5, graph.findVertex(Node(6)), graph.findVertex(Node(3)));
//    vector<Delivery> deliveries;
//    deliveries.push_back(d1);
//    deliveries.push_back(d2);
//    deliveries.push_back(d3);
//    deliveries.push_back(d4);
//    deliveries.push_back(d5);
//
//    for (auto delivery : deliveries) {
//        if (!assignDeliveryToVehicle(vehicles, delivery, table)) {
//            cout << "Assignment of delivery " << delivery.getID() << " to vehicles failed.\n";
//        }
//    }
//
//    for (auto vehicle : vehicles) {
//        cout << "For vehicle of id " << vehicle->getID() << ", the path is:\n";
//        for (auto vertex : vehicle->getVehiclePath()) {
//            cout << vertex->getInfo().getID() << ' ';
//        }
//        cout << '\n';
//        cout << "And the deliveries are:\n";
//        for (auto delivery : vehicle->getDeliveries()) {
//            cout << delivery.getID() << ' ';
//        }
//        cout << "\n\n";
//    }
//
//    for (auto vehicle : vehicles) {
//        vehicle->removeDuplicateNodes();
//    }
//
//    cout << "AFTER REMOVING THE DUPLICATES:\n\n";
//
//    for (auto vehicle : vehicles) {
//        cout << "For vehicle of id " << vehicle->getID() << ", the path is:\n";
//        for (auto vertex : vehicle->getVehiclePath()) {
//            cout << vertex->getInfo().getID() << ' ';
//        }
//        cout << '\n';
//        cout << "And the deliveries are:\n";
//        for (auto delivery : vehicle->getDeliveries()) {
//            cout << delivery.getID() << ' ';
//        }
//        cout << "\n\n";
//    }


    cout << "Displaying graph..." << endl;
    GraphViewer* gv = displayGraph(graph, "black", 5);
    cout << "Done!" << endl << endl;


 #if defined(_WIN32) || defined(WIN32)
    system("pause");
 #endif


    return 0;
}
