#include "Daniu.h"

Daniu::Daniu()
{
	maxHealth = 100;
	health = maxHealth;
	damage = 15;
}

Daniu::~Daniu()
{
}

void Daniu::Update(const double &deltaTime)
{
	if (health > maxHealth)
	{
		health = maxHealth;
	}

	Hero::Respawn(maxHealth);
	mesh->Update(deltaTime);
	Hero::Update(deltaTime);
}

void Daniu::Render()
{

}

void Daniu::RenderUI()
{

}