/*
 * AStarPriority.h
 *
 *  Created on: Jul 4, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#ifndef ASTARCOMPARISON_H_
#define ASTARCOMPARISON_H_

#include "Structs.h"

class AStarPriority {
public:
	bool operator() (Structs::Node*& first, Structs::Node*& second) const;
	AStarPriority();
	virtual ~AStarPriority();
};

#endif
