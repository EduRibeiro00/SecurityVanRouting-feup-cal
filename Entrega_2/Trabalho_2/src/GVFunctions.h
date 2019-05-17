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
 * Funcao que desenha o grafo.
 *
 * @param graph Grafo a ser desenhado
 * @param edgeColor Cor a dar as arestas
 * @param vertexSize Tamanho dos vertices do grafo
 *
 * @return Pointer para o objeto GraphViewer
 */
GraphViewer* displayGraph(Graph<Node> graph, string edgeColor, int vertexSize);

#endif /* GVFUNCTIONS_H_ */
