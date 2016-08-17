#include "Hero.h"

Hero::Hero() {

	mesh = nullptr;

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

int Hero::GetLives() const
{
	return this->lives;
}

void Hero::SetLives(const int& lives)
{
	this->lives = lives;
}