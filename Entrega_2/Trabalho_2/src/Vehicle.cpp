/*
 * Vehicle.cpp
 *
 *  Created on: 16/05/2019
 *      Author: eduribeiro
 */


#include "Vehicle.h"


int Vehicle::getID() const {
	return id;
}


TYPE Vehicle::getType() const {
	return type;
}


vector<Edge<Node>* > Vehicle::getEdgePath() const {
	return edgePath;
}


vector<Delivery> Vehicle::getDeliveries() const {
	return deliveries;
}


void Vehicle::addEdgeToPath(Edge<Node>* edge) {
	edgePath.push_back(edge);
}


void Vehicle::addDelivery(Delivery delivery) {
	deliveries.push_back(delivery);
}






