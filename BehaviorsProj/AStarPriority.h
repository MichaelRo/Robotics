/*
 * AStarPriority.h
 *
 *  Created on: Jul 4, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#ifndef ASTARCOMPARISON_H_
#define ASTARCOMPARISON_H_

#include "Structs.h"

using namespace std;

class AStarPriority {
public:
	AStarPriority();
	virtual ~AStarPriority();

	bool operator() (Structs::Node first, Structs::Node second) const;
};

#endif
