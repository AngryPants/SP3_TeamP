#pragma once
#ifndef DANIU_H
#define DANIU_H

#include "Hero.h"
#include "AnimationFSM_Daniu.h"

class Daniu : public Hero {

private:
	AnimationFSM_Daniu animationFSM;

	//Mesh & Textures
	Mesh* mesh;
	Texture specialAbility;

	double abilityAccumulatedTime;
public:
	Daniu(const string& sceneName);
	virtual ~Daniu();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();

	void Movement(const double &deltaTime);
	void TileCollision();

	virtual void Attack();
	virtual void SpecialAbility(const double &deltaTime);
	virtual void HitSound();
	virtual void RenderBullets();
};

#endif