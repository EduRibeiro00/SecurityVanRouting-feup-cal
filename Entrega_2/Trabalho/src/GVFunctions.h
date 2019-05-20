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
 * @param width Comprimento da janela do grafo (sera calculado e retornado)
 * @param height Altura da janela do grafo (sera calculado e retornado)
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayGraph(Graph<Node>& graph, string edgeColor,int& width, int& height);


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
 * Funcao que calcula qual o percurso exato que cada veiculo tera de fazer para fazer as
 * entregas que lhe foram atribuidas, desenhando esses trajetos com o GraphViewer.
 *
 * @param graph Grafo, com nos e arestas
 * @param vehicles Vetor de veiculos, com entregas atribuidas a cada um
 * @param table Tabela contendo as distancias entre nos, e outras informacoes necessarias para o calculo dos trajetos
 * @param width Comprimento da janela do grafo (ja calculado anteriormente)
 * @param height Altura da janela do grafo (ja calculado anteriormente)
 * @param edgeColor Cor a dar as arestas
 *
 * @return Pointer para o objeto GraphViewer.
 */
GraphViewer* displayVehiclePaths(Graph<Node>& graph, vector<Vehicle*> vehicles, Table table, int width, int height, string edgeColor);

#endif /* GVFUNCTIONS_H_ */
