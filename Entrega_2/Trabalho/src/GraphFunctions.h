/*
 * GraphFunctions.h
 *
 *  Created on: 17/05/2019
 *      Author: eduribeiro
 */

#ifndef GRAPHFUNCTIONS_H_
#define GRAPHFUNCTIONS_H_

#include <string>
#include <map>

#include "Graph.h"
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
 * Funcao que acede a tabela, e retorna a distancia entre os dois vertices.
 *
 * @param v1 Primeiro vertice
 * @param v2 Segundo vertice
 * @param table Tabela com os valores
 *
 * @return Distancia entre os dois vertices (-1 se nao existe nenhum caminho entre os dois).
 */
double getDistFromTable(Vertex<Node>* v1, Vertex<Node>* v2, Table table);

/**
 * Funcao que retorna o ultimo vertice no caminho de v1 para v2.
 *
 * @param v1 Primeiro vertice
 * @param v2 Segundo vertice
 * @param table Tabela com os valores
 *
 * @return Ultimo vertice no caminho (NULL se o caminho nao existir).
 */
Vertex<Node>* getPathFromTable(Vertex<Node>* v1, Vertex<Node>* v2, Table table);


/**
 * Funcao que, a partir de um grafo e das suas arestas, constroi uma tabela com as distancias entre um vertice e todos os outros,
 * bem como o vertice anterior relativamente a esse trajeto (feito apenas para os nós acessiveis a partir da central, que
 * sao os de interesse).
 *
 * @param graph O grafo, ja construido
 * @param accessNodes Vetor com os vértices acessiveis a partir da central
 *
 * @return A tabela com as distancias e os vertices anteriores.
 */

Table buildDijkstraTable(Graph<Node> graph, vector<Vertex<Node>* > accessNodes);



#endif /* GRAPHFUNCTIONS_H_ */
