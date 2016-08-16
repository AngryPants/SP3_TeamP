#pragma once
#ifndef KIFELLA_H
#define KIFELLA_H

#include "Hero.h"

class Kifella : public Hero
{
private:

public:
	Kifella();
	~Kifella();

	void Update(const double &deltaTime);
	void Render();
	void RenderUI();
};

#endif