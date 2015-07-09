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

#include "Structs.h"
#include "Map.h"
#include "MapForRobot.h"
#include "Helper.h"

using namespace std;

class Particle {
private:
	int _id;
	Structs::Location _location;
	MapForRobot * _map;
	float _belief;

	bool isObsticleDetectedAsExpected(float laserScan, int laserDegree);
	Structs::Location getRandomDeltaLocation();

	static int PARTICLE_ID_SEQUENCE;

public:
	static constexpr float NORMALIZATION_FACTOR = 1.2;
	static constexpr float MAX_DISTANCE = METER_TO_CM(2); // Check
	static constexpr float MAX_YAW = 2; // Check
	static constexpr float MAP_MAX_CELLS_LASER = 5;
	static constexpr float LASER_MAX_RANGE = METER_TO_CM(4); // Check value + check if meters/cm
	static constexpr float MAX_PARTICLES_RELATIVE_RATIO_CREATION = 0.015;
	static constexpr float MAX_PARTICLES_RELATIVE_YAW_CREATION = 0.1;

	Particle(float x, float y, float yaw, float belief, MapForRobot * map);
	Particle(Structs::Location location, float belief, MapForRobot * map);
	virtual ~Particle();

	bool operator==(const Particle & particle) const;

	float getBelief();
	Structs::Location getLocation();

	float update(Structs::Location destination, vector<float> laserScan);
	float calculatePredictedBelief(Structs::Location destination);
	float calculateBelief(Structs::Location destination, vector<float> laserScan);
	float calculateMotionModelProbability(Structs::Location destination);
	float checkObservationModel(vector<float> laserScan);
	list<Particle> createDescendantParticles(int amount);

	static float getDistance(Structs::Location destination);
};

#endif /* PARTICLE_H_ */
