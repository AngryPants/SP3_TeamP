#pragma once
#ifndef HERO_H
#define HERO_H

#include "Character.h"
#include "Bullet.h"
#include "InputManager.h"
#include "TileCollider.h"

class Hero : public Character {

protected:
	//Stats
	int lives;
	int score;
	float gravity;
	TileCoord checkpoint;

	//Move
	virtual void Move(const double& deltaTime);
	virtual void MoveLeft(const double& deltaTime);
	virtual void MoveRight(const double& deltaTime);
	virtual void MoveDown(const double& deltaTime);
	virtual void MoveUp(const double& deltaTime);

	//Item Interaction
	bool canBoost; //Make sure we don't go too fast on boostpads
	virtual void ItemInteraction(const double& deltaTime);
	virtual void ItemInteraction(int row, int column, const double& deltaTime);

public:
	vector<Character*>* enemies;

	Hero(const string& name, const string& sceneName);
	virtual ~Hero();

	virtual void Update(const double &deltaTime);
	virtual void Render();
	virtual void RenderUI();

	//Stats
	int GetLives() const;
	void SetLives(const int& lives);
	
	int GetScore() const;
	void SetScore(const int& score);

	void SetCheckpoint(int row, int column);
	TileCoord GetCheckpoint() const;

	virtual void Shoot() {};
	virtual bool TakeDamage(const int &damage);
	virtual void Knockback(const Vector2 &knockback);
	void Respawn();

	Mesh *mesh;
	Texture hpBorder;
	Texture hpBar;
};

#endif