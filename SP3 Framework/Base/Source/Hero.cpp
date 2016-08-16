#include "Hero.h"

Hero::Hero() : lives(3)
{
	bIsAlive = true;
	health = 100;
	speed = 10;
	damage = 10;
	fireRate = 5;
}

Hero::~Hero()
{
}

void Hero::Update(const double &deltaTime)
{
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_RIGHT]) 
	{
		position.x += speed * deltaTime;
	}
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MOVE_LEFT])
	{
		position.x += speed * deltaTime;
	}
	/*if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SHOOT])
	{
		bullet = new Bullet(true, position, 0, 10, 3, 10);
	}*/
}

void Hero::Render()
{

}

void Hero::RenderUI()
{

}