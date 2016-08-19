#include "Seetwo.h"

Seetwo::Seetwo()
{
	maxHealth = 150;
	health = maxHealth;
}

Seetwo::~Seetwo()
{
}

void Seetwo::Update(const double &deltaTime)
{
	if (health > maxHealth)
	{
		health = maxHealth;
	}

	Hero::Respawn(maxHealth);
	mesh->Update(deltaTime);
	Hero::Update(deltaTime);
}

void Seetwo::Render()
{

}

void Seetwo::RenderUI()
{

}