//============================================================================
// Name        : Trabalho_2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "graphviewer.h"
#include "GVFunctions.h"
#include "GraphFunctions.h"

using namespace std;

int main() {

	Graph<Node> graph = loadGraph("Mapas/Aveiro/T08_edges_Aveiro.txt",
								  "Mapas/Aveiro/T08_nodes_X_Y_Aveiro.txt",
								  "Mapas/Aveiro/T08_tags_Aveiro.txt");


	cout << graph.getVertexSet().size() << endl;

	cout << graph.getVertexSet().at(0)->getInfo().getID() << endl;
}
