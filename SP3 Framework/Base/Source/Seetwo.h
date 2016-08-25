#pragma once
#ifndef SEETWO_H
#define SEETWO_H

#include "Hero.h"
#include "AnimationFSM_Seetwo.h"
#include "Particles.h"

class Seetwo : public Hero {

private:
	AnimationFSM_Seetwo animationFSM;
	//Mesh & Textures
	Mesh* mesh;
	Texture specialAbility;

	// Particles
	vector<ParticleObject*> particleList; // Used to store particles
	Vector3 gravity; // Gravity affecting the particles
	int particleCount; // Number of particles
	unsigned int maxParticles; // Max number of particles
	double abilityAccumulatedTime;
public:
	Seetwo(const string& sceneName);
	virtual ~Seetwo();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
	void RenderBullets();

	void Movement(const double &deltaTime);
	void TileCollision();

	// Particles
	void UpdateParticles(double dt);
	ParticleObject *GetParticle(void);
	void RenderParticles();

	virtual void Attack();
	virtual void SpecialAbility(const double &deltaTime);
	virtual void HitSound();
};

#endif