#include "Bullet.h"

Bullet::Bullet() : position(0, 0), rotation(0), speed(0), lifetime(0), damage(0)
{
	isActive = true;
}

Bullet::Bullet(bool isActive, Vector2 position, float rotation, float speed, float lifetime, int damage)
{
	this->isActive = isActive;
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
	if (!isActive)
	{
		return;
	}

	Vector2 direction(cos(rotation), sin(rotation));
	position.x += speed * direction.x * deltaTime;
	position.y += speed * direction.y * deltaTime;

	lifetime -= deltaTime;
	if (lifetime < 0)
	{
		isActive = false;
	}

}

void Bullet::Render() {
}

void Bullet::RenderUI() {
}