#pragma once
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Bullet.h"
#include "InputManager.h"

class Hero : public Character {

protected:
	//Enum(s)
	enum ANIMATION_TYPE {
		IDLE,
		RUN,
		JUMP,
		SHOOT,
		RUN_SHOOT,
		DEAD,

		NUM_ANIMATION,
	};

	Animation animations[NUM_ANIMATION];
	SpriteAnimation* mesh;
	Texture texture;

	int lives;
	Vector2 velocity;

public:
	Hero();
	virtual ~Hero();

	virtual void Update(const double &deltaTime);
	virtual void Render();
	virtual void RenderUI();

	int GetLives() const;
	void SetLives(const int& lives);

};

#endif