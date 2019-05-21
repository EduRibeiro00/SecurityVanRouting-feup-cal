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
 * Funcao que pergunta ao utilizador que opcao do menu e que este pretende fazer.
 *
 * @return O numero da opcao.
 */
int chooseMenuOption();

/**
 * Funcao que pergunta ao utilizador que opcao prefere para a visualizacao das
 * entregas distribuidas.
 *
 * @return O numero da opcao.
 */
int chooseDeliveryMenuOption();

/**
 * Funcao que retorna um vector apenas com os veiculos do tipo elegido pelo
 * utilizador.
 *
 * @param vehicles Vector com todos os veiculos importados no programa
 * @return Vector apenas com os veiculos relevantes
 */
vector<Vehicle*> getVehiclesFromUserType(vector<Vehicle*> vehicles);

/**
 * Funcao que retorna um vector apenas com os veiculos escolhidos
 * pelo utilizador.
 *
 * @param vehicles Vector com todos os veiculos importados no programa
 * @return Vector apenas com os veiculos relevantes
 */
vector<Vehicle*> userChosenVehicles(vector<Vehicle*> vehicles);

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
 * @param graph Grafo ja inicializado, contendo nos e arestas, de modo a definir qual o no e que e a central
 * @param central Endereco que, quando a funcao retornar, ira apontar para o vertice do grafo correspondente a central
 *
 * @return Vetor com os veiculos disponiveis.
 */
vector<Vehicle*> readCentralAndVehicles(Graph<Node> graph, Vertex<Node>* &central);

/**
 * Funcao que pergunta ao utilizador qual o nome do ficheiro que contem a informacao
 * sobre as entregas a serem feitas; le esse ficheiro e processa a informacao
 * nele contida.
 *
 * @param graph Grafo ja inicializado, contendo nos e arestas
 * @param central Vertice que representa a central dos veiculos
 *
 * @return Vetor com as entregas a serem feitas.
 */
vector<Delivery> readDeliveries(Graph<Node> graph, Vertex<Node>* central);


/**
 * Funcao que escreve no terminal o resultado da aplicacao de algoritmos e estrategias para calcular a melhor rota para cada
 * um dos veiculos; imprime o caminho a ser percorrido por cada um deles e que entregas e que cada um ira fazer, bem como
 * as entregas que nao puderam ser feitas (se houver alguma).
 */
void displayResults(vector<Vehicle*> vehicles, vector<Delivery> deliveries);


#endif /* USERFUNCTIONS_H_ */
