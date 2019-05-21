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
#include <limits>

#include "UserFunctions.h"
#include "graphviewer.h"
#include "GVFunctions.h"
#include "GraphFunctions.h"
#include "Node.h"
#include "Vehicle.h"
#include "Manager.h"

using namespace std;

int main() {

	Graph<Node> graph;
	GraphViewer* gvMain = NULL, *gvAccess = NULL, *gvVehicle = NULL;
	Vertex<Node>* central = NULL;
	vector<Vehicle*> vehicles;
	vector<Delivery> deliveries;

	bool graphDefined = false;
	bool displayAccessible = false;
	Table table;
	string map;

    int width = 0, height = 0;

    int option;

	while((option = chooseMenuOption()) != 5) {

	  switch(option) {

		case 0:
			if(gvMain != NULL) {
				gvMain->closeWindow();
				gvMain = NULL;
			}
			vehicles.clear();
			deliveries.clear();
			graphDefined = true;
			displayAccessible = false;
			central = NULL;
			map = chooseMap();

			cout << "Building graph..." << endl;
			graph = loadGraph(map);
			cout << "Done!" << endl << endl;

			cout << "Removing useless edges..." << endl;
			removeUselessEdges(graph);
			cout << "Done!" << endl << endl;

		    cout << "Building table..." << endl;
		    table = buildDijkstraTable(graph);
		    cout << "Done!" << endl << endl;

		    break;

		case 1:
			if(!graphDefined) {
				cout << "Cannot do operation! Graph is not defined." << endl;
				break;
			}

			displayAccessible = false;
			central = NULL;
		    vehicles = readCentralAndVehicles(graph, central);
		    cout << "Done!" << endl << endl;

		    break;

		case 2:
			if(!graphDefined) {
				cout << "Cannot do operation! Graph is not defined." << endl;
				break;
			}


			if(gvMain != NULL) {
				gvMain->closeWindow();
				gvMain = NULL;
			}
		    cout << "Displaying graph..." << endl;
		    gvMain = displayGraph(graph, "black");
		    cout << "Done!" << endl << endl;

		    break;

		case 3:
			if(!graphDefined) {
				cout << "Cannot do operation! Graph is not defined." << endl;
				break;
			}

			if(central == NULL) {
				cout << "Cannot do operation! Central is not defined." << endl << endl;
				break;
			}

			if(gvAccess != NULL) {
				gvAccess->closeWindow();
				gvAccess = NULL;
			}
	    	displayAccessible = true;
	    	cout << "Calculating and displaying access graph..." << endl;
	    	gvAccess = displayAccessibleGraph(graph, central, width, height);
	    	cout << "Done!" << endl << endl;

	    	break;

		case 4:
			if(!graphDefined) {
				cout << "Cannot do operation! Graph is not defined." << endl;
				break;
			}

			if(central == NULL) {
				cout << "Cannot do operation! Central is not defined." << endl << endl;
				break;
			}

			if(vehicles.empty()) {
				cout << "Cannot do operation! There are no vehicles." << endl << endl;
				break;
			}

			deliveries = readDeliveries(graph, central);
		    if(gvMain != NULL) {
		    	cout << endl;
		    	gvMain = displayDeliveryNodes(deliveries, gvMain);
		    	cout << endl << "The delivery nodes can be seen in the main graph." << endl;
		    }

		    cout <<	"Verifying the graph's conectivity and if all deliveries are possible..." << endl;
		    pathExists(central, deliveries, table);
		    cout << "Done!" << endl << endl;

		    cout << "Assigning deliveries to vehicles..." << endl;
		    assignDeliveries(vehicles, deliveries, table);

		    for (auto vehicle : vehicles)
			   vehicle->removeDuplicateNodes();

		    cout << "Done!" << endl << endl;


		    displayResults(vehicles, deliveries);

		    cout << "To display the path of the vehicles, please press ENTER." << endl;
		    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
		    cin.ignore(std::numeric_limits<streamsize>::max(),'\n');

		    cout << "Displaying calculated paths for the vehicles..." << endl;

		     // in order to know the position to give each one of the nodes, in the GraphViewer window
		     // (if the variable is true, that means the nodes already have the positions assigned to them,
		     // and the function doesn't need to be called again).
		     if(!displayAccessible) {
		     	calculateAccessNodesDisplayCoords(graph, central, width, height);
		     	displayAccessible = true;
		     }

		     if(gvVehicle != NULL) {
		    	 gvVehicle->closeWindow();
		    	 gvVehicle = NULL;
		     }
		     gvVehicle = displayVehiclePaths(graph, vehicles, table, "black", width, height);
		     cout << "Done!" << endl << endl;


		     vehicles = resetVehicles(vehicles);

			break;

		default:
			break;

	  }

	}

    cout << "Thank you!" << endl;

    return 0;
}
