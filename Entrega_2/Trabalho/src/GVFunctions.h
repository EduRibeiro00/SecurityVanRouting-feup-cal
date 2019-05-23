/*
 * GVFunctions.h
 *
 *  Created on: 16/05/2019
 *      Author: eduribeiro
 */

#ifndef GVFUNCTIONS_H_
#define GVFUNCTIONS_H_

#include <string>

#include "Graph.h"
#include "Node.h"
#include "Vehicle.h"

/**
 * Funcao que desenha o grafo.
 *
 * @param graph Grafo a ser desenhado
 * @param edgeColor Cor a dar as arestas
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayGraph(Graph<Node>& graph, string edgeColor);


/**
 * Funcao que desenha no grafo dos nos ligados a central os pontos de articulacao. Estes ficam com uma cor diferente.
 *
 * @param gv Pointer para objeto GraphViewer, ja inicializado
 * @param graph Grafo com nos e arestas
 * @param central Vertice que representa a central dos veiculos
 * @param vertexColor Cor a dar aos vertices que sao pontos de articulacao
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayArticulatedPoints(GraphViewer* gv, Graph<Node> graph, Vertex<Node>* central, string vertexColor);


/**
 * Funcao que indica, no grafo desenhado, as origens e destinos de cada entrega.
 *
 * @param deliveries Vetor com as entregas que irao ser feitas (em principio) pelos veiculos
 * @param gv Pointer para objeto GraphViewer, ja inicializado
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayDeliveryNodes(vector<Delivery> deliveries, GraphViewer* gv);



/**
 * Funcao que calcula as coordenadas de display dos nos que sao acessiveis a partir da central. Retorna tambem um vetor contendo esses mesmos nos.
 *
 * @param graph Grafo previamente inicializado, com nos e arestas
 * @param central Vertice que representa a central
 * @param width Comprimento da janela do GraphViewer (retornado pela funcao)
 * @param height Altura da janela do GraphViewer (retornado pela funcao)
 *
 * @return Vetor com os nos acessiveis a partir da central dos veiculos
 */
vector<Vertex<Node>* > calculateAccessNodesDisplayCoords(Graph<Node> graph, Vertex<Node>* central, int& width, int& height);


/**
 * Funcao que desenha o grafico com os nos que sao acessiveis a partir da central definida anteriormente.
 * Os vertices sao calculados atraves de uma pesquisa em profundidade a partir da central.
 *
 * @param accessNodes Vetor com os nos acessiveis a partir da central
 * @param width Comprimento da janela do GraphViewer
 * @param height Altura da janela do GraphViewer
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayAccessibleGraph(vector<Vertex<Node>* > accessNodes, int width, int height);



/**
 * Funcao que calcula qual o percurso exato que cada veiculo tera de fazer para fazer as
 * entregas que lhe foram atribuidas, desenhando esses trajetos com o GraphViewer.
 *
 * @param graph Grafo, com nos e arestas
 * @param vehicles Vetor de veiculos, com entregas atribuidas a cada um
 * @param table Tabela contendo as distancias entre nos, e outras informacoes necessarias para o calculo dos trajetos
 * @param edgeColor Cor a dar as arestas
 * @param width Comprimento a dar a janela do GraphViewer (ja calculado anteriormente)
 * @param height Comprimento a dar a janela do GraphViewer (ja calculado anteriormente)
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayVehiclePaths(Graph<Node>& graph, vector<Vehicle*> vehicles, Table table, string edgeColor, int width, int height);

#endif /* GVFUNCTIONS_H_ */
