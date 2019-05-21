/*
 * Manager.cpp
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */


#include "Manager.h"


bool assignDeliveryToVehicle(vector<Vehicle*>& vehicles, Delivery delivery, Table table) {

	int bestPositionOrigin = -1, bestPositionDestination = -1;
	double bestDelta = INF;

	Vehicle* bestVehicle = NULL;

	// percorre todos os veiculos, e calcula qual o mais apropriado
	for(auto v : vehicles) {
		if(v->getType() == delivery.getType()) {

			int pOrigin, pDestination;

			double curDelta = v->testInsertDelivery(delivery, table, pOrigin, pDestination);

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
	// haver um aumento na distancia total percorrida
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



void pathExists(Vertex<Node>* central, vector<Delivery>& deliveries, Table table) {

	// como todos os percursos comecam e acabam na central, mesmo que as entregas
	// acabem por ser feitas por varios veiculos, nao tendo um que passar em todos
	// os pontos, e necessario na mesma que haja um caminho entre todos os pontos.

	// uma vez que a tabela ja foi gerada pela aplicacao do algoritmo de Dijkstra,
	// nao e necessario efetuar uma pesquisa em profundidade para verificar a
	// conectividade; basta aceder aos valores da tabela, o que fica bastante mais
	// eficiente.

	// central nao pode ser origem nem destino!

	bool impDelivery = false;

	// verificacao dos pontos
	for(int i = 0; i < deliveries.size(); i++) {

		Delivery d = deliveries.at(i);

		if((getDistFromTable(central, d.getOrigem(), table) == -1) ||
		   (getDistFromTable(central, d.getDestino(), table) == -1)) {

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
