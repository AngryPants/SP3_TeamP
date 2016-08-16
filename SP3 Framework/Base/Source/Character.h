#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "EntityBase.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "Vector2.h"

class Character : public EntityBase
{
private:
	bool bIsAlive;
	Vector2 position;
	int health;
	float speed;
	int damage;
	float fireRate;
public:
	Character();
	Character(bool bIsAlive, Vector2 position, int health, float speed, int damage, float fireRate);
	~Character();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}
};

#endif