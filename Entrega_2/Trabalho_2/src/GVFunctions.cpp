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
#include <vector>

using namespace std;

void displayGraph(Graph<Node> graph){

		int maxX = 0;
		int maxY = 0;

		for(unsigned i = 0; i < graph.getVertexSet().size(); i++){
			Node node = graph.getVertexSet().at(i)->getInfo();
			if(node.getX() > maxX)
				maxX = node.getX();

			if(node.getY() > maxY)
				maxY = node.getY();

		}


		GraphViewer *gv = new GraphViewer(maxX + 50, maxY + 50, false);
		gv->setBackground("b84.png");
		gv->createWindow(600, 600);
		gv->defineVertexColor("blue");
		gv->defineEdgeColor("black");


		int id = 0;

		for(unsigned i = 0; i < graph.getVertexSet().size(); i++){
			Node node = graph.getVertexSet().at(i)->getInfo();
			gv->addNode(node.getID(), node.getX(), node.getY());

		}

		for(unsigned i = 0; i < graph.getVertexSet().size(); i++){

			Node init_node = graph.getVertexSet().at(i)->getInfo();
			vector<Edge<Node>> edges = graph.getVertexSet().at(i)->getAdj();

			for(unsigned j = 0; j < edges.size(); j++){
				gv->addEdge(id, init_node.getID(), edges.at(j).getDest()->getInfo().getID(), EdgeType::DIRECTED);
				id++;
			}

		}





		gv->rearrange();
}

