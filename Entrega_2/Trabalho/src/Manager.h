/*
 * Manager.h
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */

#ifndef MANAGER_H_
#define MANAGER_H_

#include <vector>

#include "Graph.h"
#include "Vehicle.h"

/**
 * Funcao que atribui a entrega passada como argumento ao veiculo que compensar mais.
 *
 * @param vehicles Vetor de veiculos disponiveis
 * @param delivery Entrega a associar a um veiculo
 * @param table Tabela com as distancias e outras informacoes
 *
 * @return True se a entrega foi atribuida, false caso contrario.
 */
bool assignDeliveryToVehicle(vector<Vehicle*> vehicles, Delivery delivery, Table table);


/**
 * Funcao que atribui todas as entregas a veiculo que compensar mais. As entregas que sobrarem
 * no vetor das entregas serao aquelas que nao foram atribuidas a nenhum veiculo.
 *
 * @param vehicles Vetor com todos os veiculos disponiveis
 * @param deliveries Vetor com todas as entregas (no fim, tera as entregas que nao foram associadas a nenhum veiculo)
 * @param table Tabela com as distancias e outras informacoes
 */
void assignDeliveries(vector<Vehicle*> vehicles, vector<Delivery>& deliveries, Table table);


#endif /* MANAGER_H_ */