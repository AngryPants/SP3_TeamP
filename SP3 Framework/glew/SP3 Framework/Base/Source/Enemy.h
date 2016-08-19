#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character
{
private:

public:
	Enemy();
	virtual ~Enemy();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
};

#endif