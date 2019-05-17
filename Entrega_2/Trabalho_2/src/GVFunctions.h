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


#endif /* GVFUNCTIONS_H_ */
