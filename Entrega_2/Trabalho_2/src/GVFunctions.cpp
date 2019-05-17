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


	int numNodes;
	XYStream >> numNodes;

	string line;

	// to clear the newline
	getline(XYStream, line);

	int i = 0;

	while(getline(XYStream, line)) {

		// gets rid of the parentheses
		line = line.substr(1, line.size() - 3);

		// gets rid of the commas
		line.erase(remove(line.begin(), line.end(), ','), line.end());

		int id;
		double x, y;
		stringstream linestream(line);
		linestream >> id >> x >> y;

		graph.addVertex(Node(id, x, y));
	}

	return graph;
}
