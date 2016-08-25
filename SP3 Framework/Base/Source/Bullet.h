#ifndef BULLET_H
#define BULLET_H

#include "Mesh.h"
#include "Texture.h"
#include "Vector2.h"
#include "GameEntity.h"
#include "TileSystem.h"

class Character;

class Bullet {

public:
	//Stats
	int damage; //Damage of bullet.
	double lifetime; //How long until bullet despawns.
	float radius; //What is the effective radius of the bullet.
	bool isActive; //Is this bullet active?

	//Transform
	Vector2 position;
	Vector2 velocity;
	
	//Constructor(s) & Destructor
	Bullet();
	virtual ~Bullet();

	//Virtual Function(s)
	void Update(const double& deltaTime);

};

#endif