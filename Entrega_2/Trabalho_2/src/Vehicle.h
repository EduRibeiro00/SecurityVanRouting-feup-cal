/*
 * Vehicle.h
 *
 *  Created on: 16/05/2019
 *      Author: eduribeiro
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <vector>

#include "GraphFunctions.h"

class Vehicle {

private:

	/**
	 * ID do veiculo.
	 */
	int id;


	/**
	 * Tipo do veiculo.
	 */
	TYPE type;


	/**
	 * Vetor que ira conter os vertices pelos quais o veiculo tera de passar para cumprir o seu percurso.
	 */
	vector<Vertex<Node>* > vehiclePath;


	/**
	 * Vetor que contem as entregas atribuidas ao veiculo.
	 */
	vector<Delivery> deliveries;


public:

	/**
	 * Construtor do veiculo.
	 * @param id ID do veiculo
	 * @param type Tipo do veiculo
	 * @param central No do grafo que simboliza a central dos veiculos, a qual ira ser o ponto de partida e chegada de qualquer trajeto
	 */
	Vehicle(int id, TYPE type, Vertex<Node>* central): id(id), type(type){

		// inserido duas vezes, porque sera o inicio e o fim do trajeto
		vehiclePath.push_back(central);
		vehiclePath.push_back(central);
	}


	/**
	 * Destrutor default.
	 */
	// ~Vehicle();


	/**
	 * Funcao que retorna o ID do veiculo.
	 * @return ID do veiculo.
	 */
	int getID() const;


	/**
	 * Funcao que retorna o tipo do veiculo.
	 * @return Tipo do veiculo.
	 */
	TYPE getType() const;


	/**
	 * Funcao que retorna o vetor ordenado de vertices do veiculo.
	 * @return Vetor de vertices do veiculo.
	 */
	vector<Vertex<Node>* > getVehiclePath() const;


	/**
	 * Funcao que retorna o vetor de entregas do veiculo.
	 * @return Vetor de entregas do veiculo.
	 */
	vector<Delivery> getDeliveries() const;


	/**
	 * Adiciona ao vetor de vertices o vertice passado como argumento, na posicao indicada.
	 * @param vertex O vertice a acrescentar ao vetor
	 * @param index O indice em que se deve inserir o vertice.
	 */
	void addVertexToPath(Vertex<Node>* vertex, int index);


	/**
	 * Funcao que adiciona a entrega passada como argumento ao vetor de entregas.
	 * @param delivery A entrega a adicionar ao veto
	 */
	void addDelivery(Delivery delivery);

	/**
	 * Testa o que aconteceria se este veiculo ficasse encarregue desta entrega. Calcula as melhores
	 * posicoes para se inserir a origem e o destino da entrega, tendo em conta as distancias
	 * presentes na tabela, e retorna a distancia adicional implicada pela adicao desta entrega
	 * ao percurso.
	 *
	 * @param delivery A entrega a acrescentar
	 * @param table Tabela com distancias entre os vertices, para saber onde os inserir
	 * @param bestPositionOrigin Indice ideal onde se deve inserir a origem
	 * @param bestPositionDestination Indice ideal onde se deve inserir o destino
	 *
	 * @return Distancia adicional que resultaria se a entrega fosse realmente adicionada.
	 */
	double testInsertDelivery(Delivery delivery, Table table, int& bestPositionOrigin, int& bestPositionDestination);

};



#endif /* VEHICLE_H_ */
