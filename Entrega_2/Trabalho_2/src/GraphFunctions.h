/*
 * GraphFunctions.h
 *
 *  Created on: 17/05/2019
 *      Author: eduribeiro
 */

#ifndef GRAPHFUNCTIONS_H_
#define GRAPHFUNCTIONS_H_

#include <string>

#include "Graph.h"
#include "Node.h"
#include "Delivery.h"

/**
 * Funcao que le, de certos ficheiros txt, informacao de modo a gerar um grafo.
 *
 * @param folderName Nome do ficheiro que tem a informacao sobre o grafo
 *
 * @return Grafo gerado com a informacao dada.
 */
Graph<Node> loadGraph(string folderName);


/**
 * Funcao que calcula a distancia entre dois pontos, de modo a serem usados para gerar os pesos das arestas do grafo.
 *
 * @param x1 Coordenada X do ponto 1
 * @param y1 Coordenada Y do ponto 1
 * @param x2 Coordenada X do ponto 2
 * @param y2 Coordenada Y do ponto 2
 *
 * @return Distancia entre os dois pontos.
 */
double getDistance(double x1, double y1, double x2, double y2);


/**
 * Funcao que remove arestas de peso 0, que nao devem ser usadas pelos veiculos.
 * @param graph O grafo contendo os vertices e as arestas
 */
void removeUselessEdges(Graph<Node> graph);


/**
 * Funcao que, dado os vertices do grafo pelo qual o(s) veiculo(s) terao de passar, indica se existe algum trajeto
 * que ligue todos os vertices (necessario para que
 */
bool pathExists(Vertex<Node>* central, vector<Delivery> deliveries, vector<vector< pair<double, Vertex<Node>* > > > table);



/**
 * Funcao que, a partir de um grafo e das suas arestas, constroi uma tabela com as distancias entre um vertice e todos os outros
 * (distancia -1 se nao for possivel o trajeto), bem como o vertice anterior relativamente a esse trajeto.
 *
 * @param graph O grafo, ja construido
 *
 * @return A tabela com as distancias e os vertices anteriores.
 */
vector<vector< pair<double, Vertex<Node>* > > > buildDijkstraTable(Graph<Node> graph);



#endif /* GRAPHFUNCTIONS_H_ */
