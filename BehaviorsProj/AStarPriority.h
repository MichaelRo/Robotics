/*
 * AStarPriority.h
 *
 *  Created on: Jul 4, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#ifndef ASTARCOMPARISON_H_
#define ASTARCOMPARISON_H_

#include "Structs.h"

#include <functional>

using namespace std;

struct AStarPriority : public std::binary_function<Structs::Node, Structs::Node, bool>{
public:
	AStarPriority();
	virtual ~AStarPriority();

	bool operator() (Structs::Node first, Structs::Node second) const;
};

#endif
