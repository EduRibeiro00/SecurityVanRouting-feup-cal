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
	vector<Vertex<Node>* > accessNodes; // nós que podemos aceder a partir da central

	bool graphDefined = false;
	bool displayAccessible = false;
	Table table;
	string map;

    int width = 0, height = 0;

    int option;

	while((option = chooseMenuOption()) != 6) {

	  switch(option) {

		case 0:
			if(gvMain != NULL) {
				gvMain->closeWindow();
				gvMain = NULL;
			}
			if(gvAccess != NULL) {
				gvAccess->closeWindow();
				gvAccess = NULL;
			}

			table.clear();
			vehicles.clear();
			deliveries.clear();
			accessNodes.clear();
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

		    break;

		case 1:
			if(!graphDefined) {
				cout << "Cannot do operation! Graph is not defined." << endl;
				break;
			}

			displayAccessible = true;
			central = NULL;

			vehicles = readCentralAndVehicles(graph, central);

		    cout << "Calculating accessible nodes..." << endl;
		    accessNodes = calculateAccessNodesDisplayCoords(graph, central, width, height);
		    cout << "Done!" << endl << endl;

		    table = buildTable(graph, accessNodes);
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
				cout << "Cannot do operation! Graph is not defined." << endl << endl;
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
	    	cout << "Calculating and displaying access graph..." << endl;
	    	if(!displayAccessible) {
	    		accessNodes = calculateAccessNodesDisplayCoords(graph, central, width, height);
	    		displayAccessible = true;
	    	}
	    	gvAccess = displayAccessibleGraph(accessNodes, width, height);
	    	cout << "Done!" << endl << endl;

	    	break;

		case 4:
			if(!graphDefined) {
				cout << "Cannot do operation! Graph is not defined." << endl << endl;
				break;
			}

			if(gvAccess == NULL) {
				cout << "Accessible graph is not being displayed! Please select option 3 first." << endl << endl;
				break;
			}

			if(central == NULL) {
				cout << "Cannot do operation! Central is not defined." << endl << endl;
				break;
			}

			cout << "Calculating and displaying articulated points..." << endl;
			gvAccess = displayArticulatedPoints(gvAccess, graph, central, "pink");
			cout << "Done! The art. points are being displayed in pink." << endl << endl;
			break;


		case 5:
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


		    if(!displayAccessible) {
	    		accessNodes = calculateAccessNodesDisplayCoords(graph, central, width, height);
	    		displayAccessible = true;
		    }

		    cout <<	"Verifying the graph's conectivity and if all deliveries are possible..." << endl;
		    pathExists(accessNodes, deliveries);
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

		    int secondOption;

		    while ((secondOption = chooseDeliveryMenuOption()) != 3) {

                vector<Vehicle*> auxVehicles;

                switch (secondOption) {
		            case 0:
		                auxVehicles = vehicles;
		                break;
                    case 1:
                        auxVehicles = getVehiclesFromUserType(vehicles);
                        break;
                    case 2:
                        auxVehicles = userChosenVehicles(vehicles);
                        break;
		            default:
                        break;
                }

                if (secondOption == 3) break;

                cout << "Vehicles selected: ";
                for (auto vehicle : auxVehicles) {
                    cout << vehicle->getID() << " ";
                }
                cout << endl;

                cout << "Calculating and displaying the paths for the vehicles..." << endl;


                if(gvVehicle != NULL) {
                    gvVehicle->closeWindow();
                    gvVehicle = NULL;
                }

                gvVehicle = displayVehiclePaths(graph, auxVehicles, table, "black", width, height);
                cout << "Done!" << endl << endl;

            }

		    vehicles = resetVehicles(vehicles);

			break;

		default:
			break;

	  }

	}

    cout << "Thank you!" << endl;

    return 0;
}
