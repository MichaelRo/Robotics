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
	double _belief;

	bool isObsticleDetectedAsExpected(double laserScan, int laserDegree);
	Structs::Location getRandomDeltaLocation();

	static int PARTICLE_ID_SEQUENCE;

public:
	static constexpr double NORMALIZATION_FACTOR = 1.1;
	static constexpr double MAX_DISTANCE = METER_TO_CM(1);
	static constexpr double MAX_YAW = 10;

	Particle(double x, double y, double yaw, double belief, Map * map);
	Particle(Structs::Location location, double belief, Map * map);
	virtual ~Particle();

	bool operator==(const Particle & particle) const;

	double getBelief();
	Structs::Location getLocation();

	double update(Structs::Location destinationDelta, vector<double> laserScan);
	double calculatePredictedBelief(Structs::Location destinationDelta);
	double calculateBelief(Structs::Location destinationDelta, vector<double> laserScan);
	double calculateMotionModelProbability(Structs::Location destinationDelta);
	double checkObservationModel(vector<double> laserScan);
	void createDescendantParticles(int amount, list<Particle> * list);

	static double getDistance(Structs::Location destination);
};

#endif
