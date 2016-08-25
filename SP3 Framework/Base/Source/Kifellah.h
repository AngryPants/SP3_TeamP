#pragma once
#ifndef KIFELLAH_H
#define KIFELLAH_H

#include "Hero.h"
#include "AnimationFSM_Kifellah.h"

class Kifellah : public Hero {

private:
	AnimationFSM_Kifellah animationFSM;

public:
	Kifellah(const string& sceneName);
	virtual ~Kifellah();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
	void RenderBullets();

	void Movement(const double &deltaTime);
	void TileCollision();

	virtual void Attack();
	virtual void SpecialAbility(const double &deltaTime);
	virtual bool TakeDamage(const int &damage);
};

#endif