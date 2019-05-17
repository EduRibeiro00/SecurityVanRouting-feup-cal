/*
 * Vehicle.h
 *
 *  Created on: 16/05/2019
 *      Author: eduribeiro
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <vector>

#include "Delivery.h"

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
	 * Vetor que ira conter as arestas pelas quais o veiculo tera de passar para cumprir o seu percurso.
	 */
	vector<Edge<Node>* > edgePath;


	/**
	 * Vetor que contem as entregas atribuidas ao veiculo.
	 */
	vector<Delivery> deliveries;


public:

	/**
	 * Construtor do veiculo.
	 * @param id ID do veiculo
	 * @param type Tipo do veiculo
	 */
	Vehicle(int id, TYPE type): id(id), type(type){}


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
	 * Funcao que retorna o vetor de arestas do veiculo.
	 * @return Vetor de arestas do veiculo.
	 */
	vector<Edge<Node>* > getEdgePath() const;


	/**
	 * Funcao que retorna o vetor de entregas do veiculo.
	 * @return Vetor de entregas do veiculo.
	 */
	vector<Delivery> getDeliveries() const;


	/**
	 * Adiciona ao vetor de arestas a aresta passada como argumento.
	 * @param edge A aresta a acrescentar ao vetor
	 */
	void addEdgeToPath(Edge<Node>* edge);


	/**
	 * Adiciona ao vetor de entregas a entrega passada como argumento.
	 * @param delivery A entrega a acrescentar ao vetor
	 */
	void addDelivery(Delivery delivery);

};



#endif /* VEHICLE_H_ */
