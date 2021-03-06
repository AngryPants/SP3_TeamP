/******************************************************************************/
/*!
\file	Character.h
\author Teh Kai Hong Bryan
\par	email: 150587A@mymail.nyp.edu.sg
\brief
Class to define a character entity
*/
/******************************************************************************/

#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameEntity.h"
#include "Bullet.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "TileSystem.h"
#include "TileCollider.h"
#include <set>

using std::set;

/******************************************************************************/
/*!
		Class Character:
\brief	Defines a character and its methods
*/
/******************************************************************************/

class Character : public GameEntity {
	
private:
	//Where our character is facing
	Vector2 forwardDirection;

	//Bullet
	int bulletIndex;

protected:
	//Spawnpoint
	TileCoord spawnpoint;

	//Health
	float currentHealth;
	float maxHealth;	

	//Movement	
	bool isMoving;
	float maxSpeed;
	bool onGround;
	float gravity;

	//Combat
	bool isAttacking;
	int damage; //How much damage do we deal.
	float fireRate;	//How many bullets per second can we shoot
	float attackCooldownTimer; //How long until we can shoot again.
	float damageCooldown; //How long until we can take damage again.
	float damageCooldownTimer; //The timer for damage cooldown
	float collisionRadius; //The radius of which the character will collide with bullets etc.

	//Bullets
	vector<Bullet*> bullets;
	Bullet& FetchBullet();
	void ClearBullets();
	virtual void RenderBullets() = 0;

	//Tile System
	TileSystem* tileSystem;
	TileCollider tileCollider;
	
public:
	//Is the character alive?
	bool isDead;

	//Constructor(s) & Destructor
	Character(const string& name, const string& sceneName);
	virtual ~Character();

	//Health
	void SetHealth(const float& health);
	float GetHealth() const;
	void SetMaxHealth(const float& maxHealth);
	float GetMaxHealth() const;

	//Movement (Maximum Horizontal Speed)
	void SetMaxSpeed(const float& speed);
	float GetMaxSpeed() const;
	
	//Direction
	Vector2 GetForwardDirection() const; //Where our character is facing
	void FaceLeft();
	void FaceRight();

	//Spawnpoint
	void SetSpawnpoint(int row, int col);
	TileCoord GetSpawnpoint() const;

	//Combat
	void SetDamage(const int& damage);
	int GetDamage() const;
	void SetFireRate(const float& fireRate);
	float GetFireRate() const;
	void SetCollisionRadius(const float& collisionRadius);
	float GetCollisionRadius() const;	
	virtual void Attack() = 0;
	virtual bool TakeDamage(const int &damage);
	virtual void Knockback(const Vector2 &knockback);

	//Tile System
	void SetTileSystem(TileSystem& tileSystem); //The tile system that the character will interact with.
	void RemoveTileSystem();

	//Collision Detection
	virtual vector<unsigned int> CheckCollisionUp();
	virtual vector<unsigned int> CheckCollisionDown();
	virtual vector<unsigned int> CheckCollisionLeft();
	virtual vector<unsigned int> CheckCollisionRight();
	virtual unsigned int& CheckCollisionCentre();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void Reset();

};

#endif