#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityBase.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "Vector2.h"

class Character : public EntityBase {

protected:
	//Stats
	int health;
	float speed;
	int damage;	
	double fireRate;

	//Mesh
	SpriteAnimation* mesh;

public:
	bool isAlive;
	Vector2 position;

	//Constructor(s) & Destructor
	Character();
	Character(bool isAlive, Vector2 position, int health, float speed, int damage, float fireRate);
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

	//TileMap
	void SetTileMap(TileMap& tilemap);
	void RemoveTileMap();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();

};

#endif