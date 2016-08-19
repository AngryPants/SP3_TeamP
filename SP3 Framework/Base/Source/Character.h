#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityBase.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "TileSystem.h"

class Character : public EntityBase {

protected:
	//Stats
	int health;
	int maxHealth;
	float speed;
	int damage;
	double fireRate;
	
	double minFPS;

	//Mesh
	SpriteAnimation* mesh;

	Vector2 hotspots[4];

	//Tile System
	TileSystem* tileSystem;

	//Collision Detection
	virtual void MoveLeft(const double& deltaTime) {};
	virtual void MoveRight(const double& deltaTime) {};
	virtual void MoveDown(const double& deltaTime) {};
	virtual void MoveUp(const double& deltaTime) {};	

	bool onGround;

public:
	bool isAlive;
	Vector2 position;
	Vector2 scale;
	Vector2 velocity;

	//Constructor(s) & Destructor
	Character();
	virtual ~Character();

	//Stats
	int GetHealth() const;
	float GetSpeed() const;
	int GetDamage() const;
	float GetFireRate() const;

	void SetHealth(const int& health);
	void SetSpeed(const float& speed);
	void SetDamage(const float& damage);
	void SetFireRate(const float& fireRate);

	//Others
	void SetTileSystem(TileSystem& tileSystem);
	void RemoveTileSystem();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void TakeDamage(const int &damage);
};

#endif