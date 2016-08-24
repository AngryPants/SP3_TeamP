#pragma once

#ifndef PARTICLES_H
#define PARTICLES_H

#include "Vector3.h"

enum ParticleObject_TYPE
{
	P_ABILITY_SEETWO,
	P_TOTAL,
};

class ParticleObject
{
public:
	ParticleObject(ParticleObject_TYPE = P_ABILITY_SEETWO);
	~ParticleObject(void);

	ParticleObject_TYPE type; // Type of Particle

	Vector3 pos; //Position of Particle
	Vector3 vel; //Velocity of Particle	
	Vector3 scale; //Scale of Particle
	float rotation; //Rotation of Particle
	float rotationSpeed; //Rotational Speed of Particle

	bool active; //Activate particles

private:

};

#endif // PARTICLES_H