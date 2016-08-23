#pragma once
#ifndef SEETWO_H
#define SEETWO_H

#include "Hero.h"
#include "AnimationFSM_Seetwo.h"

class Seetwo : public Hero {

private:
	AnimationFSM_Seetwo animationFSM;

public:
	Seetwo(const string& sceneName);
	virtual ~Seetwo();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();

	void Movement(const double &deltaTime);
	void TileCollision();

	virtual void Shoot();
	virtual void SpecialAbility(const double &deltaTime);
};

#endif