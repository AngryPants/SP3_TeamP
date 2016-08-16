#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityBase.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "TileMap.h"

class Character : public EntityBase
{
protected:
	bool bIsAlive;
	Vector2 position;
	int health;
	float speed;
	int damage;
	float fireRate;
	float detectionWidth;
	float detectionHeight;
	float offsetX;
	float offsetY;
public:
	Character();
	Character(bool bIsAlive, Vector2 position, int health, float speed, int damage, float fireRate);
	~Character();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}

	int GetTileInfo(Vector2);
	TileMap *tileMap;
};

#endif