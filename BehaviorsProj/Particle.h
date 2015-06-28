/*
 * Particle.h
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <math.h>

#include "Structs.h"
#include "Map.h"
#include "Helper.h"

using namespace std;

class Particle {
private:
	Structs::Location _location;
	Map* _map;
	float _belief;

	bool isObsticleDetectedAsExpected(float laserScan, int laserIndex);
	bool isObsticleOccupiedInMap(Structs::Location scannedObsticleLocation);

public:
	static const float NORMALIZATION_FACTOR = 1.2;
	static const float MAX_DISTANCE = 2; // Check
	static const float MAX_YAW = 2; // Check
	static const float MAX_PARTICLES_CREATION_RANDOM_RATIO = 5;
	static const float MAP_MAX_CELLS_LASER = 5;
	static const float LASER_MAX_RANGE = 4; // Check value + check if meters/cm

	Particle(float x, float y, float yaw, Map* map);
	Particle(Structs::Location location, Map* map);
	virtual ~Particle();

	float getBelief();
	Structs::Location getLocation();

	float update(Structs::Location destination, vector<float> laserScan);
	float calculatePredictedBelief(Structs::Location destination);
	float calculateBelief(Structs::Location destination, vector<float> laserScan);
	float calculateMotionModelProbability(Structs::Location destination);
	float checkObservationModel(vector<float> laserScan);
	vector<Particle> createDescendantParticles(int amount);

	static float getDistance(Structs::Location destination);
};

#endif /* PARTICLE_H_ */
