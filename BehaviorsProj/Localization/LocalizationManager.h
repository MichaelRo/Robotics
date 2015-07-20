/*
 * LocalizationManager.h
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <list>
#include <iostream>

#include "Particle.h"
#include "../Framework/Map.h"
#include "../Framework/Structs.h"
#include "../Control/Robot.h"

using namespace std;

class LocalizationManager {
private:
	list<Particle> _particles;
	Map * _map;
	Structs::Location _estimatedRobotLocation;

	Particle * getHighestBeliefParticle();

public:
	LocalizationManager(Structs::Location startLocation, Map * map);
	virtual ~LocalizationManager();

	void updateParticles(Structs::Location destinationDelta, vector<double> laserScan);
	Structs::Location getProbableLocation();
	double getHighestBelief();
	double getAverageBeleif();

	Map * getMap();
};

#endif
