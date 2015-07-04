/*
 * AStarPriority.cpp
 *
 *  Created on: Jul 4, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "AStarPriority.h"

bool AStarPriority::operator() (Structs::Node*& first, Structs::Node*& second) const
{
	return (first->getF()>second->getF());
}

AStarPriority::AStarPriority() {
}

AStarPriority::~AStarPriority() {
}
