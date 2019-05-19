/*
 * Node.cpp
 *
 *  Created on: 15/05/2019
 *      Author: eduribeiro
 */

#include "Node.h"


int Node::getID() const {
	return id;
}


double Node::getX() const {
	return xCoord;
}


double Node::getY() const {
	return yCoord;
}


TYPE Node::getType() const {
	return type;
}


void Node::setType(TYPE type) {
	this->type = type;
}


int Node::getDisplayX() {
	return displayX;
}


void Node::setDisplayX(int displayX) {
	this->displayX = displayX;
}


int Node::getDisplayY() {
	return displayY;
}


void Node::setDisplayY(int displayY) {
	this->displayY = displayY;
}


bool Node::operator==(const Node& n) const {
	return id == n.getID();
}
