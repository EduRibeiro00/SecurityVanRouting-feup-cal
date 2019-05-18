/*
 * UserFunctions.h
 *
 *  Created on: 18/05/2019
 *      Author: eduribeiro
 */

#ifndef USERFUNCTIONS_H_
#define USERFUNCTIONS_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "Vehicle.h"

using namespace std;

/**
 * Funcao que pergunta ao utilizador qual o mapa que este deseja escolher.
 * @return Nome da cidade/pais.
 */
string chooseMap();

/**
 * Funcao que pergunta ao utilizador qual o nome do ficheiro em que a informacao
 * sobre a central e os veiculos esta contida; le esse ficheiro e processa a informacao
 * nele contida.
 *
 * @param graph Grafo ja inicializado, contendo nos e arestas, de modo a definir qual o no que e a central
 *
 * @return Vetor com os veiculos disponiveis.
 */
vector<Vehicle*> readCentralAndVehicles(Graph<Node> graph);

/**
 * Funcao que pergunta ao utilizador qual o nome do ficheiro que contem a informacao
 * sobre as entregas a serem feitas; le esse ficheiro e processa a informacao
 * nele contida.
 *
 * @return Vetor com as entregas a serem feitas.
 */
vector<Delivery> readDeliveries();


#endif /* USERFUNCTIONS_H_ */
