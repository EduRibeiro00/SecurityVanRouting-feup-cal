/*
 * Manager.cpp
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */


#include "Manager.h"


bool assignDeliveryToVehicle(vector<Vehicle*> vehicles, Delivery delivery, Table table) {

	int bestPositionOrigin = -1, bestPositionDestination = -1;
	double bestDelta = INF;

	Vehicle* bestVehicle = NULL;

	// percorre todos os veiculos, e calcula qual o mais apropriado
	for(auto v : vehicles) {
		if(v->getType() == delivery.getType()) {

			int pOrigin, pDestination;

			double curDelta = v->testInsertDelivery(delivery, table, pOrigin, pDestination);

			cout << "Delta for delivery " << delivery.getID() << " and vehicle " << v->getID() << " is " << curDelta << endl;

			if(curDelta < bestDelta) {
				bestPositionOrigin = pOrigin;
				bestPositionDestination = pDestination;
				bestDelta = curDelta;
				bestVehicle = v;
			}
		}
	}

	// nao ha nenhum veiculo indicado para a entrega
	// ex: nenhum veiculo desse tipo
	if(bestVehicle == NULL)
		return false;

	// adiciona a entrega ao melhor veiculo indicado
	bestVehicle->addVertexToPath(delivery.getOrigem(), bestPositionOrigin);
	bestVehicle->addVertexToPath(delivery.getDestino(), bestPositionDestination);

	bestVehicle->addDelivery(delivery);

	return true;
}

