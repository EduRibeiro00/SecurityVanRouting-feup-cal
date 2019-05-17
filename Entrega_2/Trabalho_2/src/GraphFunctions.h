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

/**
 * Funcao que le, de certos ficheiros txt, informacao de modo a gerar um grafo.
 *
 * @param edgeFile Ficheiro que contem a informacao sobre as arestas
 * @param XYFile Ficheiro que contem a informacao sobre as coordenadas dos nos
 * @param tagsFile Ficheiro que contem a informacao sobre as tags/tipos dos nos
 *
 * @return Grafo gerado com a informacao dada.
 */
Graph<Node> loadGraph(string edgeFile, string XYFile, string tagsFile);


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




#endif /* GRAPHFUNCTIONS_H_ */
