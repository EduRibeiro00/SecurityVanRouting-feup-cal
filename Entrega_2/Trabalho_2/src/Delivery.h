/*
 * Delivery.h
 *
 *  Created on: 15/05/2019
 *      Author: eduribeiro
 */

#ifndef DELIVERY_H_
#define DELIVERY_H_

#include "Graph.h"
#include "Node.h"

class Delivery {

private:

	/**
	 * ID da entrega.
	 */
	int id;

	/**
	 * Tipo da entrega.
	 */
	TYPE type;

	/**
	 * Vertice origem da entrega.
	 */
	Vertex<Node>* origem;

	/**
	 * Vertice destino da entrega.
	 */
	Vertex<Node>* destino;


public:

	/**
	 * Construtor de entregas.
	 * @param id ID da entrega
	 * @param type Tipo da entrega
	 * @param origem Vertice origem da entrega
	 * @param destino Vertice destino da entrega
	 */
	Delivery(int id, TYPE type, Vertex<Node>* origem, Vertex<Node>* destino): id(id), type(type), origem(origem), destino(destino){}


	/**
	 * Destrutor default.
	 */
	// ~Delivery();


	/**
	 * Funcao que retorna o ID da entrega.
	 * @return ID da entrega.
	 */
	int getID() const;


	/**
	 * Funcao que retorna o tipo da entrega.
	 * @return Tipo da entrega.
	 */
	TYPE getType() const;


	/**
	 * Funcao que retorna a origem da entrega.
	 * @return Origem da entrega.
	 */
	Vertex<Node>* getOrigem() const;


	/**
	 * Funcao que retorna o destino da entrega.
	 * @return Destino da entrega.
	 */
	Vertex<Node>* getDestino() const;
};


#endif /* DELIVERY_H_ */
