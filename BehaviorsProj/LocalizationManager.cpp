/*
 * LocalizationManager.cpp
 *
 *  Created on: Jun 27, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "LocalizationManager.h"

LocalizationManager::LocalizationManager(Structs::Location startLocation, Map * map) {
	_map = map;
	_particles.push_front(*(new Particle(startLocation, map)));
}

LocalizationManager::~LocalizationManager() {
	delete _map;
}

void LocalizationManager::updateParticles(Structs::Location destination, vector<float> laserScan) {
	list<Particle>::iterator particlesIterator = _particles.begin();

	while (particlesIterator != _particles.end()) {
		float currentParticleBelief = particlesIterator->update(destination, laserScan);

		if (currentParticleBelief < BELIEF_THRESHOLD) {
			_particles.erase(particlesIterator++);
		} else {
			// Check if this works on the previous particle
			particlesIterator++->createDescendantParticles(PARTICLES_AMOUNT - _particles.size());
		}
	}
}

Particle * LocalizationManager::getHighestBeliefParticle() {
	list<Particle>::iterator particlesIterator = _particles.begin();
	Particle * highestBeliefParticle = particlesIterator.operator ->();

	for (particlesIterator = _particles.begin(); particlesIterator != _particles.end(); ++particlesIterator) {
		if (particlesIterator->getBelief() > highestBeliefParticle->getBelief())
			highestBeliefParticle = particlesIterator.operator ->();
	}

	return highestBeliefParticle;
}

Structs::Location LocalizationManager::getProbableLocation() {
	return getHighestBeliefParticle()->getLocation();
}

void LocalizationManager::createNewParticles() {
	// Decide who randoms the location - the LocalizationManager or the Particle itself
	getHighestBeliefParticle()->createDescendantParticles(PARTICLES_AMOUNT - _particles.size());
}
