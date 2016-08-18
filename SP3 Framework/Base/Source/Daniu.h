#pragma once
#ifndef DANIU_H
#define DANIU_H

#include "Hero.h"

class Daniu : public Hero
{
private:

public:
	Daniu();
	virtual ~Daniu();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
};

#endif