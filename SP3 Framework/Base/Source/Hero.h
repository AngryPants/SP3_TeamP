#pragma once
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Bullet.h"
#include "InputManager.h"

class Hero : public Character
{
private:
	int lives;
public:
	Hero();
	~Hero();

	virtual void Update(const double &deltaTime);
	virtual void Render();
	virtual void RenderUI();

	Bullet *bullet;
};

#endif