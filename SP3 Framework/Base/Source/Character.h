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

class Character : public GameEntity {

protected:
	//Health
	int currentHealth;
	int maxHealth;	

	//Movement	
	bool isMoving;
	float maxSpeed;
	bool onGround;
	float gravity;

	//Combat
	bool isShooting;
	int damage; //How much damage do we deal.
	float fireRate;	//How many bullets per second can we shoot
	float shootingCooldown; //How long until we can shoot again.
	float damageCooldown; //How long until we can take damage again.
	float collisionRadius; //The radius of which the character will collide with bullets etc.

	//Bullets
	vector<Bullet*> bullets;
	virtual Bullet& FetchBullet();	

	//Tile System
	TileSystem* tileSystem;
	TileCollider tileCollider;
	
public:
	//Direction
	enum class FACING_DIRECTION {
		LEFT,
		RIGHT,
	};
	FACING_DIRECTION currentDirection;

	//Is the character alive?
	bool isDead;

	//Constructor(s) & Destructor
	Character(const string& name, const string& sceneName);
	virtual ~Character();

	//Health
	void SetHealth(const int& health);
	int GetHealth() const;
	void SetMaxHealth(const int& maxHealth);
	int GetMaxHealth() const;

	//Movement (Maximum Horizontal Speed)
	void SetMaxSpeed(const float& speed);
	float GetMaxSpeed() const;

	//Combat
	void SetDamage(const int& damage);
	int GetDamage() const;
	void SetFireRate(const float& fireRate);
	float GetFireRate() const;
	void SetCollisionRadius(const float& collisionRadius);
	float GetCollisionRadius() const;	
	virtual bool TakeDamage(const int &damage);
	virtual void Knockback(const Vector2 &knockback);

	//Tile System
	void SetTileSystem(TileSystem& tileSystem); //The tile system that the character will interact with.
	void RemoveTileSystem();

	//Collision Detection
	virtual vector<unsigned int>& CheckCollisionUp();
	virtual vector<unsigned int>& CheckCollisionDown();
	virtual vector<unsigned int>& CheckCollisionLeft();
	virtual vector<unsigned int>& CheckCollisionRight();
	virtual unsigned int& CheckCollisionCentre();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render() {}
	virtual void RenderUI() {}

};

#endif