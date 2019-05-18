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
	Table table = buildDijkstraTable(graph);
    cout << "Done!" << endl << endl;


	cout << "Displaying graph..." << endl;
	displayGraph(graph, "black", 5);

#if defined(_WIN32) || defined(WIN32)
    system("pause");
#endif

	cout << "Done!" << endl << endl;


	return 0;
}
