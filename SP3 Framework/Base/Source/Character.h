#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameEntity.h"
#include "Bullet.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "Vector2.h"
#include "TileSystem.h"
#include "TileCollider.h"

class GameManager;

class Character : public GameEntity {

protected:
	//Stats
	int maxHealth;
	int health;
	float maxSpeed;
	int damage;
	float fireRate;
	float damageCooldown; //How long until we can take damage again.
	float shootingCooldown; //How long until we can shoot again.

	//Bullets
	vector<Bullet*> bullets;
	virtual Bullet& FetchBullet();
	float collisionRadius; //The radius of which the character will collide with bullets etc.

	//Tile System
	TileSystem* tileSystem;
	TileCollider tileCollider;

	//What Direction Are We Facing?
	enum class MOVE_DIRECTION {
		LEFT,
		RIGHT,
	};

	MOVE_DIRECTION currentDirection;
	bool onGround;
	bool isShooting;
	bool isMoving;

	//Movement
	virtual void MoveLeft(const double& deltaTime) {};
	virtual void MoveRight(const double& deltaTime) {};
	virtual void MoveDown(const double& deltaTime) {};
	virtual void MoveUp(const double& deltaTime) {};

public:
	bool isDead;

	//Constructor(s) & Destructor
	Character(const string& name, const string& sceneName);
	virtual ~Character();

	//Stats
	void SetHealth(const int& health);
	void SetSpeed(const float& speed);
	void SetDamage(const int& damage);
	void SetFireRate(const float& fireRate);
	void SetCollisionRadius(const float& collisionRadius);

	int GetHealth() const;
	float GetMaxSpeed() const;
	int GetDamage() const;
	float GetFireRate() const;
	float GetCollisionRadius() const;

	//Others
	void SetTileSystem(TileSystem& tileSystem); //The tile system that the character will interact with.
	void RemoveTileSystem();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}
	virtual bool TakeDamage(const int &damage);
	virtual void Knockback(const Vector2 &knockback);

};

#endif