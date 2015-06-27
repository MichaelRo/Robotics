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

using namespace std;

class Particle {
private:
	Structs::Location _location;
	Map* _map;
	float _belief;

public:
	static const float NORMALIZATION_FACTOR = 1.2;
	static const float MAX_DISTANCE = 2;
	static const float MAX_YAW = 2;
	static const float MAX_PARTICLES_CREATION_RANDOM_RATIO = 5;

	Particle(float x, float y, float yaw, Map* map);
	Particle(Structs::Location location, Map* map);
	virtual ~Particle();

	float getBelief();

	void update(Structs::Location destination);
	float calculatePredictedBelief(Structs::Location destination);
	float calculateBelief(Structs::Location destination);
	float calculateMotionModelProbability(Structs::Location destination);
	float getObservationModel(Structs::Location destination);
	vector<Particle> createDescendantParticles(int amount);

	static float getDistance(Structs::Location destination);
};

#endif /* PARTICLE_H_ */
