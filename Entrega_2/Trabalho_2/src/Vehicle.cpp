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


vector<Vertex<Node>* > Vehicle::getVehiclePath() const {
	return vehiclePath;
}


vector<Delivery> Vehicle::getDeliveries() const {
	return deliveries;
}


void Vehicle::addVertexToPath(Vertex<Node>* vertex, int index) {

	if(index >= vehiclePath.size()) {
		cout << "Invalid index!" << endl;
		return;
	}

	vehiclePath.insert(vehiclePath.begin() + index, vertex);
}


void Vehicle::addDelivery(Delivery delivery) {
	deliveries.push_back(delivery);
}


double Vehicle::testInsertDelivery(Delivery delivery, Table table, int& bestPositionOrigin, int& bestPositionDestination) {

	double deltaOrigin, deltaDestination;

	Vertex<Node>* origin = delivery.getOrigem();
	Vertex<Node>* destination = delivery.getDestino();

	// caso particular: o veiculo ainda nao tem nenhuma entrega associada
	if(deliveries.empty()) {
		bestPositionOrigin = 1;
		bestPositionDestination = 2;

		Vertex<Node>* central = vehiclePath.at(0);

		deltaOrigin = getDistFromTable(central, origin, table) +
					  getDistFromTable(origin, central, table);

		deltaDestination = getDistFromTable(origin, destination, table) +
						   getDistFromTable(destination, central, table) -
						   getDistFromTable(origin, central, table);

		return deltaOrigin + deltaDestination;
	}


	double minDistance = INF;

	// nao considera a primeira e ultima posicoes do vetor
	// de vertices, uma vez que estes sao a central.
	for(int i = 1; i < vehiclePath.size() - 1; i++) {

		Vertex<Node>* previous = vehiclePath.at(i - 1);
		Vertex<Node>* next = vehiclePath.at(i + 1);

        double curDeltaOrigin, curDeltaDestination;

        // NOTA: A funcao admite que a conectividade do grafo
		// ja foi avaliada, e que existe sempre um caminho entre
		// qualquer par de vertices.

		 curDeltaOrigin = getDistFromTable(previous, origin, table) +
		              getDistFromTable(origin, next, table) -
					  getDistFromTable(previous, next, table);

		 for (int j = i; j < vehiclePath.size() - 1; j++) {
             previous = vehiclePath.at(j - 1);
             next = vehiclePath.at(j + 1);

             // NOTA: A funcao admite que a conectividade do grafo
             // ja foi avaliada, e que existe sempre um caminho entre
             // qualquer par de vertices.

             if (i == bestPositionOrigin) {
                 curDeltaDestination = getDistFromTable(origin, destination, table) +
                               getDistFromTable(destination, next, table) -
                               getDistFromTable(origin, next, table);
             }
             else {
                 curDeltaDestination = getDistFromTable(previous, destination, table) +
                               getDistFromTable(destination, next, table) -
                               getDistFromTable(previous, next, table);
             }

             if(curDeltaOrigin + curDeltaDestination < minDistance) {
                 minDistance = curDeltaOrigin + curDeltaDestination;
                 bestPositionOrigin = i;
                 bestPositionDestination = j + 1;
                 deltaOrigin = curDeltaOrigin;
                 deltaDestination = curDeltaDestination;
             }
		 }
	}

	return deltaOrigin + deltaDestination;

}






