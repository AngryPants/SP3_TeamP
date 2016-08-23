#ifndef BULLET_H
#define BULLET_H

#include "Mesh.h"
#include "Texture.h"
#include "Vector2.h"
#include "GameEntity.h"
#include "TileSystem.h"

class Character;

class Bullet : public GameEntity {

private:
	//Private Functions
	void DamageTargets(const double& deltaTime);
	void CheckCollisionWithWall();

public:
	//Stats
	int damage; //Damage of bullet.
	double lifetime; //How long until bullet despawns.
	float radius; //What is the effective radius of the bullet.

	//What characters can the bullet hit?
	vector<Character*>* targets;

	//Check for collision with walls etc.
	TileSystem* tileSystem;

	//Mesh & Texture.
	Mesh* mesh;
	Texture texture;
	
	//Constructor(s) & Destructor
	Bullet(const string& sceneName);
	virtual ~Bullet();

	//Virtual Function(s)
	void Update(const double& deltaTime);
	void Render();
	void RenderUI();

};

#endif