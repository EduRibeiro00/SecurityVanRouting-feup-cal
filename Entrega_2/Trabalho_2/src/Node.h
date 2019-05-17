/*
 * Node.h
 *
 *  Created on: 15/05/2019
 *      Author: eduribeiro
 */

#ifndef NODE_H_
#define NODE_H_

// VER MELHOR OS TIPOS DE NOS NOS FICHEIROS TXT DADOS
enum TYPE { BANK, MUSEUM, STORE , OTHER, CENTRAL };

class Node {

private:
	/**
	 * ID do node.
	 */
	int id;

	/**
	 * Coordenada X do node.
	 */
	double xCoord;

	/**
	 * Coordenada Y do node.
	 */
	double yCoord;

	/**
	 * Tipo do node (BANK, MUSEUM, SHOP, etc)
	 */
	TYPE type;

public:

	/**
	 * Construtor do node.
	 * @param id ID do node
	 * @param xCoord Coordenada X do node
	 * @param yCoord Coordenada Y do node
	 * @param type tipo do node
	 */
	Node(int id, double xCoord, double yCoord, TYPE type): id(id), xCoord(xCoord), yCoord(yCoord), type(type){}


	/**
	 * Segundo construtor do node (inicializa "type" como OTHER).
	 * @param id ID do node
	 * @param xCoord Coordenada X do node
	 * @param yCoord Coordenada Y do node
	 */
	Node(int id, double xCoord, double yCoord): id(id), xCoord(xCoord), yCoord(yCoord), type(OTHER){}


	/**
	 * Terceiro construtor do node (apenas inicializa o ID).
	 * @param id ID do node
	 */
	Node(int id): id(id), xCoord(0), yCoord(0), type(OTHER){}

	/**
	 * Destrutor default.
	 */
	// ~Node();


	/**
	 * Funcao que retorna o ID do node.
	 * @return O ID do node.
	 */
	int getID() const;


	/**
	 * Funcao que retorna a coordenada X do node.
	 * @return Coordenada X do node.
	 */
	double getX() const;


	/**
	 * Funcao que retorna a coordenada Y do node.
	 * @return Coordenada Y do node.
	 */
	double getY() const;


	/**
	 * Funcao que retorna o tipo do node.
	 * @return Tipo do node.
	 */
	TYPE getType() const;


	/**
	 * Funcao que modifique o tipo do node.
	 * @param type Novo tipo do node
	 */
	void setType(TYPE type);


	/**
	 * Overload do operador de igualdade.
	 * @param n Node que ira ser comparado com o node que chamou o metodo
	 * @return True se forem iguais, false caso contrario.
	 */
	bool operator==(const Node& n) const;

};



#endif /* NODE_H_ */
