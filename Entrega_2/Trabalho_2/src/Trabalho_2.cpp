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
	Graph<Node> graph = loadGraph("Teste");
	cout << "Done!" << endl << endl;


	cout << "Removing useless edges..." << endl;
	removeUselessEdges(graph);
	cout << "Done!" << endl << endl;


	cout << "Building table..." << endl;
	Table table = buildDijkstraTable(graph);
    cout << "Done!" << endl << endl;


	cout << "Displaying graph..." << endl;
	GraphViewer* gv = displayGraph(graph, "black", 5);
	cout << "Done!" << endl << endl;

    for (Table::iterator it = table.begin(); it != table.end(); it++) {
        cout << "first vertex: " << it->first.first->getInfo().getID() << "   -   ";
        cout << "second vertex: " << it->first.second->getInfo().getID() << "\n";
        cout << "distance: " << it->second.first << "   -   ";
        cout << "path: " << it->second.second->getInfo().getID() << "\n\n";
    }


    Vertex<Node>* v1 = graph.findVertex(Node(7));
    Vertex<Node>* v2 = graph.findVertex(Node(2));

    cout << "Distance from 7 to 2: " << getDistFromTable(v1, v2, table) << endl;
    cout << "Distance from 2 to 7: " << getDistFromTable(v2, v1, table) << endl;
    cout << "Path from 7 to 2: " << getPathFromTable(v1, v2, table)->getInfo().getID() << endl;
    cout << "Path from 2 to 7: " << getPathFromTable(v2, v1, table)->getInfo().getID() << endl << endl;




#if defined(_WIN32) || defined(WIN32)
    system("pause");
#endif

    return 0;
}
