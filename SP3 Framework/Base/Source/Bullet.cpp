#include "Bullet.h"

Bullet::Bullet() : bIsActive(false), position(0, 0), rotation(0), speed(0), lifetime(0), damage(0)
{
}

Bullet::Bullet(bool bIsActive, Vector2 position, float rotation, float speed, float lifetime, int damage)
{
	this->bIsActive = bIsActive;
	this->position = position;
	this->rotation = rotation;
	this->speed = speed;
	this->lifetime = lifetime;
	this->damage = damage;
}

Bullet::~Bullet()
{
}

void Bullet::Update(const double& deltaTime)
{
	if (!bIsActive)
	{
		return;
	}

	Vector2 direction(cos(rotation), sin(rotation));
	position.x += speed * direction.x * deltaTime;
	position.y += speed * direction.y * deltaTime;

	lifetime -= deltaTime;
	if (lifetime < 0)
	{
		bIsActive = false;
	}

}