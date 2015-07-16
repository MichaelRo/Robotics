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
	static const int PARTICLES_AMOUNT = 100;

	list<Particle> _particles;
	Map * _map;

	Particle * getHighestBeliefParticle();

public:
	static constexpr float BELIEF_THRESHOLD = 0.6; // 0.6 / 0.25
//	static const int STANDARD = 0.7 - maybe we need a high threshold

	LocalizationManager(Structs::Location startLocation, Map * map);
	virtual ~LocalizationManager();

	void updateParticles(Structs::Location destination, vector<float> laserScan);
	Structs::Location getProbableLocation();
	float getHighestBelief();
};

#endif
