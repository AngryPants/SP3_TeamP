#include "Bullet.h"

Bullet::Bullet()
{
	lifetime = 1;
	damage = 1;
	isActive = true;
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

	position += velocity * deltaTime;

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

void Bullet::SetVelocity(float x, float y) {

	this->velocity.x = x;
	this->velocity.y = y;

}

Vector2 Bullet::GetVelocity() const {

	return this->velocity;
	
}