//============================================================================
// Name        : Trabalho_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>

#include "graphviewer.h"
#include "GVFunctions.h"
#include "GraphFunctions.h"
#include "Node.h"
#include "Vehicle.h"

using namespace std;

int main() {

	cout << "Building graph..." << endl;
	Graph<Node> graph = loadGraph("Aveiro");
	cout << "Done!" << endl << endl;

	vector<Vehicle> vehicles;

	cout << "Displaying graph..." << endl;
	displayGraph(graph, "black", 5);
	cout << "Done!" << endl << endl;


	return 0;
}
