#pragma once
#ifndef HERO_H
#define HERO_H

#include "Character.h"

class Hero : public Character
{
private:
	int lives;
public:
	Hero();
	~Hero();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
};

#endif