#include "Character.h"

Character::Character() : bIsAlive(false), position(0, 0), health(0), speed(0), damage(0), fireRate(0)
{
}

Character::Character(bool bIsAlive, Vector2 position, int health, float speed, int damage, float fireRate)
{
	this->bIsAlive = bIsAlive;
	this->position = position;
	this->health = health;
	this->speed = speed;
	this->damage = damage;
	this->fireRate = fireRate;
}

Character::~Character()
{
}

void Character::Update(const double &deltaTime)
{
	if (!bIsAlive)
	{
		return;
	}
}

void Character::Render()
{

}