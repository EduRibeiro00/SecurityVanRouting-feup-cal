/*
 * Delivery.cpp
 *
 *  Created on: 15/05/2019
 *      Author: eduribeiro
 */

#include "Delivery.h"


int Delivery::getID() const {
	return id;
}


TYPE Delivery::getType() const {
	return type;
}


Vertex<Node>* Delivery::getOrigem() const {
	return origem;
}


Vertex<Node>* Delivery::getDestino() const {
	return destino;
}
