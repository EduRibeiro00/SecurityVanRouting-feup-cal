/*
 * GraphFunctions.cpp
 *
 *  Created on: 17/05/2019
 *      Author: eduribeiro
 */

#include "GraphFunctions.h"

#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include "GVFunctions.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cmath>

using namespace std;

Graph<Node> loadGraph(string edgeFile, string XYFile, string tagsFile) {

	Graph<Node> graph;

	ifstream XYStream, edgeStream, tagsStream;
	XYStream.open(XYFile);

	if(!XYStream) {
		cout << "Couldn't open XY file!" << endl;
		return graph;
	}

	edgeStream.open(edgeFile);

	if(!edgeStream) {
		cout << "Couldn't open edge file!" << endl;
		return graph;
	}

	tagsStream.open(tagsFile);

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
		line = line.substr(1, line.size() - 3);

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
		line = line.substr(1, line.size() - 3);

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


		// adds the edge to the graph
		graph.addEdge(Node(id1), Node(id2), distance);
	}

	int total = 0;

	for(auto v : graph.getVertexSet()) {
		total += v->getAdj().size();
	}

	if(total != numEdges) {
		cout << "Number of edges in the graph is wrong! ";
		cout << total << " instead of " << numEdges << "." << endl;
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


