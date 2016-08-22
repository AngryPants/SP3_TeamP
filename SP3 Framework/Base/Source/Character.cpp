#include "Character.h"

Character::Character(const string& name, const string& sceneName) : GameEntity(name, sceneName)
{
	collisionRadius = 1.0f;
	isActive = true;
	position.SetZero();
	health = 1;
	maxHealth = 1;
	maxSpeed = 1;
	damage = 0;
	fireRate = 1;
	damageCooldown = 0.0;
	shootingCooldown = 0.0;
	currentDirection = MOVE_DIRECTION::RIGHT;

	onGround = true;
	isShooting = false;
	isMoving = false;
	isDead = false;

	tileSystem = nullptr;
}

Character::~Character(){}

//Stats
int Character::GetHealth() const
{
	return this->health;
}

float Character::GetMaxSpeed() const
{
	return this->maxSpeed;
}

int Character::GetDamage() const
{
	return this->damage;
}

float Character::GetFireRate() const
{
	return this->fireRate;
}

void Character::SetHealth(const int& health)
{
	this->health = health;
}

void Character::SetSpeed(const float& maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

void Character::SetDamage(const int& damage)
{
	this->damage = damage;
}

void Character::SetFireRate(const float& fireRate)
{
	this->fireRate = fireRate;
}

void Character::SetTileSystem(TileSystem& tileSystem)
{
	this->tileSystem = &tileSystem;
}

void Character::RemoveTileSystem()
{
	this->tileSystem = nullptr;
}

bool Character::TakeDamage(const int &damage)
{
	if (damageCooldown <= 0.0)
	{
		this->health -= damage;
		damageCooldown = 0.5f;
		return true;
	}

	return false;
}

void Character::SetCollisionRadius(const float& collisionRadius)
{
	this->collisionRadius = collisionRadius;
}

float Character::GetCollisionRadius() const
{
	return this->collisionRadius;
}

Bullet& Character::FetchBullet() {

	static int bulletIndex = 0;
	size_t vectorSize = bullets.size();

	if (bulletIndex > vectorSize) {
		bulletIndex = 0;
	}

	if (vectorSize == 0) {
		bullets.push_back(new Bullet(GetScene()));
		return *bullets.back();
	}

	vector<Bullet*>::iterator iter = std::next(bullets.begin(), bulletIndex);
	int endIndex = bulletIndex;

	do {
		if (iter == bullets.end()) {
			iter = bullets.begin();
		}
		if ((*iter)->isActive == false) {
			bulletIndex = (bulletIndex + 1) % vectorSize;
			return *(*iter);
		}		
		++iter;		
		bulletIndex = (bulletIndex + 1) % vectorSize;
	} while (bulletIndex!= endIndex);

	for (unsigned int n = 0; n < (vectorSize + 1) / 2; ++n) {
		bullets.push_back(new Bullet(GetScene()));
	}

	bulletIndex = vectorSize;

	return *(*(std::next(bullets.begin(), bulletIndex)));

}