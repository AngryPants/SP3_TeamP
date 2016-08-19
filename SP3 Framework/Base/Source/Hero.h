#pragma once
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Bullet.h"
#include "InputManager.h"
#include "TileCollider.h"

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
	TileCollider tileCollider;

	int lives;
	int score;
	float gravity;

	//Debug
	Mesh* debugMesh;

	//Move
	virtual void MoveLeft(const double& deltaTime);
	virtual void MoveRight(const double& deltaTime);
	virtual void MoveDown(const double& deltaTime);
	virtual void MoveUp(const double& deltaTime);

	virtual void PickUpItem(unsigned int& tileValue);

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