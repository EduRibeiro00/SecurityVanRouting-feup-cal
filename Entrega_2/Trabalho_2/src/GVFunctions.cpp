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

void displayGraph(Graph<Node> graph){

		GraphViewer *gv = new GraphViewer(600, 600, false);
		//gv->setBackground("b84.png");
		gv->createWindow(600, 600);
		gv->defineVertexColor("blue");
		gv->defineEdgeColor("black");

		/*for(unsigned i = 0; i < graph.vertexSet.size(); i++){
			Node node = graph.vertexSet.at(i)->getInfo();
			gv->addNode(node.getID(), node.getX(), node.getY());

		}

		for(unsigned i = 0; i < graph.vertexSet.size(); i++){
			Node node = graph.vertexSet.at(i)->getInfo();

		}*/





		gv->rearrange();
}
