#pragma once
#ifndef KIFELLAH_H
#define KIFELLAH_H

#include "Hero.h"
#include "SpriteAnimation.h"

class Kifellah : public Hero {

private:
	/*

	****4*************5****
	***********************
	0*********************2
	***********************
	***********************
	***********C***********
	***********************
	***********************
	1*********************3
	***********************
	****6*************7****

	*/

	Vector2 hotspots[8];
	bool onGround;

public:
	Kifellah();
	virtual ~Kifellah();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();

	void Movement(const double &deltaTime);
	void TileCollision();

	TileCollider tCollision;
};

#endif