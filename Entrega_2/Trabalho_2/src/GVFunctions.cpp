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

GraphViewer* displayGraph(Graph<Node> graph, string edgeColor, int vertexSize) {

		double maxX = 0, maxY = 0, minX = 9999999999, minY = 9999999999;

		for(unsigned i = 0; i < graph.getVertexSet().size(); i++) {

			Node node = graph.getVertexSet().at(i)->getInfo();
			double currentX = node.getX();
			double currentY = node.getY();

			if(currentX > maxX)
				maxX = currentX;

			if(currentX < minX)
				minX = currentX;

			if(currentY > maxY)
				maxY = currentY;

			if(currentY < minY)
				minY = currentY;
		}


		// --------
		// CALCULO DE DIMENSOES
		// --------

		int defaultHeight = 800;
		double gravWidth = maxX - minX;
		double gravHeight = maxY - minY;

		// uso de uma regra de tres simples para calcular o comprimento ideal para a janela
		int width = max(defaultHeight, (int) (defaultHeight * gravHeight / gravWidth));


		GraphViewer *gv = new GraphViewer(width, defaultHeight, false);
		gv->createWindow(width, defaultHeight);
		gv->defineEdgeColor(edgeColor);

		gv->defineVertexSize(vertexSize);
		gv->defineEdgeCurved(false);

		// --------
		// VERTICES
		// --------

		for(auto v : graph.getVertexSet()) {

			Node node = v->getInfo();

			double displayX = (node.getX() - minX ) * width / gravWidth * 0.95;
			double displayY = (node.getY() - minY ) * defaultHeight / gravHeight * 0.95;

			displayX += (0.025 * width);
			displayY += (0.025 * defaultHeight);

			gv->addNode(node.getID(), (int) displayX, (int) displayY);

			// TIRAR DPS
			stringstream ss;
			ss << node.getID();
			gv->setVertexLabel(node.getID(), ss.str());


			switch(node.getType()) {

				case BANK:
					gv->setVertexColor(node.getID(), "BLUE");
					break;

				case FIN_ADVICE:
					gv->setVertexColor(node.getID(), "RED");
					break;

				case ATM:
					gv->setVertexColor(node.getID(), "GREEN");
					break;

				case TAX_ADVISOR:
					gv->setVertexColor(node.getID(), "WHITE");
					break;

				case AUDIT:
					gv->setVertexColor(node.getID(), "ORANGE");
					break;

				case MONEY_MOV:
					gv->setVertexColor(node.getID(), "YELLOW");
					break;

				case OTHER:
					gv->setVertexColor(node.getID(), "LIGHT_GRAY");
					break;

				case CENTRAL:
					gv->setVertexColor(node.getID(), "BLACK");
					break;

				default:
					break;
			}
		}


		// --------
		// ARESTAS
		// --------

		int idAresta = 1;


		for(unsigned i = 0; i < graph.getVertexSet().size(); i++){

			Node init_node = graph.getVertexSet().at(i)->getInfo();
			vector<Edge<Node> > edges = graph.getVertexSet().at(i)->getAdj();

			for(unsigned j = 0; j < edges.size(); j++){
				if(edges.at(j).shouldBeDisplayed()) {
					gv->addEdge(idAresta, init_node.getID(), edges.at(j).getDest()->getInfo().getID(), EdgeType::UNDIRECTED);

					// TIRAR DPS
					stringstream ss;
					ss << idAresta << " - " << fixed << setprecision(5) << edges.at(j).getWeight();
					gv->setEdgeLabel(idAresta, ss.str());

                    idAresta++;
				}
			}

		}


		gv->rearrange();

		return gv;
}

