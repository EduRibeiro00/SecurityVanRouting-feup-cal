//============================================================================
// Name        : Trabalho_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <utility>

#include "graphviewer.h"
#include "GVFunctions.h"
#include "GraphFunctions.h"
#include "Node.h"
#include "Vehicle.h"

using namespace std;

int main() {

	cout << "Building graph..." << endl;
	Graph<Node> graph = loadGraph("Braga");
	cout << "Done!" << endl << endl;


	cout << "Removing useless edges..." << endl;
	removeUselessEdges(graph);
	cout << "Done!" << endl << endl;


	cout << "Building table..." << endl;
	vector<vector< pair<double, Vertex<Node>* > > > table = buildDijkstraTable(graph);
	cout << "Done!" << endl << endl;






	cout << "Displaying graph..." << endl;
	displayGraph(graph, "black", 5);
	cout << "Done!" << endl << endl;


	return 0;
}
