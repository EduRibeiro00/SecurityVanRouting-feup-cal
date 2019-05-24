/*
 * Manager.cpp
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */


#include "Manager.h"
#include <iomanip>


bool assignDeliveryToVehicle(vector<Vehicle*>& vehicles, Delivery delivery, Table table) {

	int bestPositionOrigin = -1, bestPositionDestination = -1;
	double bestDelta = INF;

	Vehicle* bestVehicle = NULL;

	// percorre todos os veiculos, e calcula qual o mais apropriado
	for(auto v : vehicles) {
		if(v->getType() == delivery.getType()) {

			int pOrigin, pDestination;

			double curDelta = v->testInsertDelivery(delivery, table, pOrigin, pDestination);


			// rounding the value to two decimal places, in order to avoid residual errors
			curDelta = (int) (curDelta * 100 + 0.5);
			curDelta = (double) curDelta / 100;

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


	// para entregas seguintes, no caso de haver igualdade no termo de
	// comparação, o veiculo ao qual acaba de ser associada uma entrega
	// tera menor prioridade, o que no contexto do problema, na vida
	// real, se traduziria numa reducao do tempo total das entregas, sem
	// haver um aumento na distancia total percorrida.
    for (size_t i = 0; i < vehicles.size() - 1; i++) {
        if (bestVehicle == vehicles[i]) {
            swap(vehicles[i], vehicles[i+1]);
        }
    }


	return true;
}



void assignDeliveries(vector<Vehicle*> vehicles, vector<Delivery>& deliveries, Table table) {

	for(int i = 0; i < deliveries.size(); i++) {
		// se a entrega foi atribuida, apagar do vetor de entregas
		if(assignDeliveryToVehicle(vehicles, deliveries.at(i), table)) {
			deliveries.erase(deliveries.begin() + i);
			i--;
		}
	}
}



void pathExists(vector<Vertex<Node>* > accessNodes, vector<Delivery>& deliveries) {

	// como todos os percursos comecam e acabam na central, mesmo que as entregas
	// acabem por ser feitas por varios veiculos, nao tendo um que passar em todos
	// os pontos, e necessario na mesma que haja um caminho entre todos os pontos.

	// central nao pode ser origem nem destino!

	bool impDelivery = false;

	// verificacao dos pontos
	for(int i = 0; i < deliveries.size(); i++) {

		Delivery d = deliveries.at(i);

		if((find(accessNodes.begin(), accessNodes.end(), d.getOrigem()) == accessNodes.end()) ||
		   (find(accessNodes.begin(), accessNodes.end(), d.getDestino()) == accessNodes.end())) {

			impDelivery = true;
			cout << "Delivery " << d.getID();
			cout << " (" << d.getOrigem()->getInfo().getID();
			cout << " -> " << d.getDestino()->getInfo().getID() << ") ";
			cout << "cannot be done." << endl;

			// apaga do vetor das entregas
			deliveries.erase(deliveries.begin() + i);
			i--;

		}
	}

	if(impDelivery)
		cout << "The impossible deliveries were removed." << endl;
	else
		cout << "Every delivery is valid!" << endl;
}



vector<Vehicle*> resetVehicles(vector<Vehicle*> vehicles) {

	vector<Vehicle*> newVehicles;

	// NOTA: nao esquecer que em 1º e ultimo lugar do vetor de vertices dos veiculos
	// esta sempre a central...

	for(auto v : vehicles)
		newVehicles.push_back(new Vehicle(v->getID(), v->getType(), v->getVehiclePath().at(0)));


	return newVehicles;
}
