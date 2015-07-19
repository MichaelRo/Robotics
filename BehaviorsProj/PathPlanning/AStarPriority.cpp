/*
 * AStarPriority.cpp
 *
 *  Created on: Jul 4, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "AStarPriority.h"

AStarPriority::~AStarPriority() {

}

AStarPriority::AStarPriority() {

}

/**
	This method sort the nodes of the A* algorithm by the f function (f = g + h), the lowest f is the best.

	@return - if the first node has bigger f than the second node
 */
bool AStarPriority::operator() (Structs::Node first, Structs::Node second) const {
	return first.getF() > second.getF();
}
