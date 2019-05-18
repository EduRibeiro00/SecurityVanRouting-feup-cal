/*
 * GraphFunctions.cpp
 *
 *  Created on: 17/05/2019
 *      Author: eduribeiro
 */

#include "GraphFunctions.h"

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <utility>

using namespace std;

Graph<Node> loadGraph(string folderName) {

	Graph<Node> graph;

	ifstream XYStream, edgeStream, tagsStream;
	XYStream.open("Mapas/" + folderName + "/T08_nodes_X_Y_" + folderName + ".txt");

	if(!XYStream) {
		cout << "Couldn't open XY file!" << endl;
		return graph;
	}

	edgeStream.open("Mapas/" + folderName + "/T08_edges_" + folderName + ".txt");

	if(!edgeStream) {
		cout << "Couldn't open edge file!" << endl;
		return graph;
	}

	tagsStream.open("Mapas/" + folderName + "/T08_tags_" + folderName + ".txt");

	if(!tagsStream) {
		cout << "Couldn't open tags file!" << endl;
		return graph;
	}


	// -----------
	// READS NODES
	// -----------

	int numNodes;
	XYStream >> numNodes;

	string line;

	// to clear the newline
	getline(XYStream, line);


	while(getline(XYStream, line)) {

		// gets rid of the parentheses
		size_t pos = line.find(')');
		if (pos != string::npos)
			line = line.substr(1, pos);

		// gets rid of the commas
		line.erase(remove(line.begin(), line.end(), ','), line.end());


		int id;
		double x, y;
		stringstream linestream(line);
		linestream >> id >> x >> y;


		// add node to vertex
		graph.addVertex(Node(id, x, y));
	}


	if(graph.getVertexSet().size() != numNodes) {
		cout << "Number of nodes in the graph is wrong! ";
		cout << graph.getVertexSet().size() << " instead of " << numNodes << "." << endl;
		return graph;
	}



	// -----------
	// READS EDGES
	// -----------

	int numEdges;
	edgeStream >> numEdges;

	// to clear the newline
	getline(edgeStream, line);


	while(getline(edgeStream, line)) {

		// gets rid of the parentheses
		size_t pos = line.find(')');
		if (pos != string::npos)
		    line = line.substr(1, pos);


		// gets rid of the commas
		line.erase(remove(line.begin(), line.end(), ','), line.end());

		int id1, id2;
		stringstream linestream(line);
		linestream >> id1 >> id2;

		// gets the two nodes from the graph
		Vertex<Node>* v1 = graph.findVertex(Node(id1));
		Vertex<Node>* v2 = graph.findVertex(Node(id2));

		// calculates the distance between the two nodes
		double distance = getDistance(v1->getInfo().getX(), v1->getInfo().getY(), v2->getInfo().getX(), v2->getInfo().getY());


		// adds the edges to the graph - BIDIRECTIONAL EDGES
		graph.addEdge(Node(id1), Node(id2), distance, true);
		graph.addEdge(Node(id2), Node(id1), distance, false);
	}

	int total = 0;

	for(auto v : graph.getVertexSet()) {
		total += v->getAdj().size();
	}

	if(total != (numEdges * 2)) {
		cout << "Number of edges in the graph is wrong! ";
		cout << total << " instead of " << numEdges * 2 << "." << endl;
		return graph;
	}

	// -----------
	// READS TAGS
	// -----------


	int numDifTags;
	tagsStream >> numDifTags;


	for(int i = 0; i < numDifTags; i++) {

		// extracts tag name
		tagsStream >> line;

		int numTags;
		tagsStream >> numTags;

		int id;

		for(int j = 0; j < numTags; j++) {

			tagsStream >> id;

			Vertex<Node>* v = graph.findVertex(Node(id));

			if(line == "amenity=bank")
				v->getInfo().setType(BANK);

			else if(line == "barrier=hedge_bank")
				v->getInfo().setType(BANK);

			else if(line == "amenity=financial_advice")
				v->getInfo().setType(FIN_ADVICE);

			else if(line == "amenity=atm")
				v->getInfo().setType(ATM);

			else if(line == "office=tax_advisor")
				v->getInfo().setType(TAX_ADVISOR);

			else if(line == "government=audit")
				v->getInfo().setType(AUDIT);

			else if(line == "shop=money_lender")
				v->getInfo().setType(MONEY_MOV);

			else if(line == "amenity=money_transfer")
				v->getInfo().setType(MONEY_MOV);

			else if(line == "shop=moneylender")
				v->getInfo().setType(MONEY_MOV);

		}

	}

	return graph;
}



double getDistance(double x1, double y1, double x2, double y2) {
	double value1 = (x2 - x1) * (x2 - x1);
	double value2 = (y2 - y1) * (y2 - y1);

	return sqrt(value1 + value2);
}



void removeUselessEdges(Graph<Node> graph) {

	for(auto v : graph.getVertexSet())
		for(int i = 0; i < v->getAdj().size(); i++)
			if(v->getAdj().at(i).getWeight() == 0) {
				v->removeEdge(i);
				i--;
			}

}


double getDistFromTable(Vertex<Node>* v1, Vertex<Node>* v2, Table table) {

	// se o par v1-v2 esta na tabela
	if(table.find(make_pair(v1, v2)) != table.end())
		return table.at(make_pair(v1, v2)).first;

	// se o par v2-v1 esta na tabela (arestas bidirecionais, logo distancia v1-v2 = distancia v2-v1)
	if(table.find(make_pair(v2, v1)) != table.end())
		return table.at(make_pair(v2, v1)).first;

	// nao ha caminho
	return -1;
}


Vertex<Node>* getPathFromTable(Vertex<Node>* v1, Vertex<Node>* v2, Table table) {

	// se o par v1-v2 esta na tabela
	if(table.find(make_pair(v1, v2)) != table.end())
		return table.at(make_pair(v1, v2)).second;

	// se o par v2-v1 esta na tabela
	if(table.find(make_pair(v2, v1)) != table.end()) {

		Vertex<Node>* vAux = table.at(make_pair(v2, v1)).second;

		if (vAux == v1)
			return vAux;
		else
			return getPathFromTable(vAux, v2, table);

	}

	// nao ha caminho
	return NULL;
}


Table buildDijkstraTable(Graph<Node> graph) {

    // uma vez que os grafos que nos foram dados pelos monitores
    // sao esparsos (nº de arestas e similar ao nº de vertices),
    // compensa mais utilizar o algoritmo de Dijkstra para todos
    // os vertices, do que usar o algoritmo de Floyd-Warshall.

    Table table;

    vector<Vertex<Node> * > vertexSet = graph.getVertexSet();

    for(auto v1 : vertexSet) {

        // calcula as distancias para os vertices acessiveis a partir do vertice atual
        graph.dijkstraShortestPathTable(table, v1->getInfo());

    }


    return table;
}




