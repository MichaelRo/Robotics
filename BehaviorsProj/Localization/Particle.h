/*
 * Particle.h
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#define DEGREES_TO_RADIANS(degree)		((degree) * M_PI / 180)
#define METER_TO_CM(meter)				(meter * 100)

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <set>

#include "../Framework/Structs.h"
#include "../Framework/Map.h"
#include "../Utils/Helper.h"

using namespace std;

class Particle {
private:
	int _id;
	Structs::Location _location;
	Map * _map;
	float _belief;

	bool isObsticleDetectedAsExpected(float laserScan, int laserDegree);
	Structs::Location getRandomDeltaLocation();

	static int PARTICLE_ID_SEQUENCE;

public:
	static constexpr float NORMALIZATION_FACTOR = 1.1;
	static constexpr float MAX_DISTANCE = METER_TO_CM(1);
	static constexpr float MAX_YAW = 10;

	Particle(float x, float y, float yaw, float belief, Map * map);
	Particle(Structs::Location location, float belief, Map * map);
	virtual ~Particle();

	bool operator==(const Particle & particle) const;

	float getBelief();
	Structs::Location getLocation();

	float update(Structs::Location destinationDelta, vector<float> laserScan);
	float calculatePredictedBelief(Structs::Location destinationDelta);
	float calculateBelief(Structs::Location destinationDelta, vector<float> laserScan);
	float calculateMotionModelProbability(Structs::Location destinationDelta);
	float checkObservationModel(vector<float> laserScan);
	list<Particle> createDescendantParticles(int amount);

	static float getDistance(Structs::Location destination);
};

#endif
