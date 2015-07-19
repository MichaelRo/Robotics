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

#include "Map.h"
#include "Particle.h"
#include "Structs.h"
#include "Robot.h"

using namespace std;

class LocalizationManager {
private:
	list<Particle> _particles;
	Map * _map;
	Structs::Location _estimatedRobotLocation;

	Particle * getHighestBeliefParticle();

public:
	static constexpr float BELIEF_THRESHOLD = 0.7;
	static constexpr float MINIMUM_BELIEF = 0.3;

	LocalizationManager(Structs::Location startLocation, Map * map);
	virtual ~LocalizationManager();

	void updateParticles(Structs::Location destinationDelta, Structs::Location estimatedRobotLocation, vector<float> laserScan);
	Structs::Location getProbableLocation();
	float getHighestBelief();

	Map * getMap();
};

#endif
