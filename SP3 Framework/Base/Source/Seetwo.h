#pragma once
#ifndef SEETWO_H
#define SEETWO_H

#include "Hero.h"

class Seetwo : public Hero
{
private:

public:
	Seetwo();
	~Seetwo();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
};

#endif