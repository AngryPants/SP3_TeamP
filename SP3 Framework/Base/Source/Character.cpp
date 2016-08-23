#include "Character.h"

//Constructor(s) & Destructor
Character::Character(const string& name, const string& sceneName) : GameEntity(name, sceneName)
{
	//GameEntity
	isActive = true;

	//Health
	currentHealth = 1;
	maxHealth = 1;

	//Movement
	isMoving = false;
	maxSpeed = 1;	
	onGround = true;
	gravity = -9.81f;

	//Direction
	currentDirection = FACING_DIRECTION::RIGHT;

	//Combat
	damage = 1;
	fireRate = 1.0f;
	shootingCooldown = 0.0;
	damageCooldown = 0.0;
	collisionRadius = 1.0f;		
	isShooting = false;
		
	//Tile System
	tileSystem = nullptr;

	//Is the character alive?
	isDead = false;

}

Character::~Character() {}

//Health
void Character::SetHealth(const int& health)
{
	this->currentHealth = health;
	if (this->currentHealth > this->maxHealth) {
		this->currentHealth = this->maxHealth;
	}
}

int Character::GetHealth() const
{
	return this->currentHealth;
}

void Character::SetMaxHealth(const int& maxHealth) {
	this->maxHealth = maxHealth;
	if (this->currentHealth > this->maxHealth) {
		this->currentHealth = this->maxHealth;
	}
}

int Character::GetMaxHealth() const {
	return this->maxHealth;
}

//Movement
void Character::SetMaxSpeed(const float& maxSpeed)
{
	this->maxSpeed = maxSpeed;
}

float Character::GetMaxSpeed() const
{
	return this->maxSpeed;
}

//Combat
void Character::SetDamage(const int& damage)
{
	this->damage = damage;
}

int Character::GetDamage() const
{
	return this->damage;
}

void Character::SetFireRate(const float& fireRate)
{
	this->fireRate = fireRate;
	this->shootingCooldown = 0.0;
}

float Character::GetFireRate() const
{
	return this->fireRate;
}

void Character::SetCollisionRadius(const float& collisionRadius)
{
	this->collisionRadius = collisionRadius;
}

float Character::GetCollisionRadius() const
{
	return this->collisionRadius;
}

bool Character::TakeDamage(const int &damage)
{
	if (damageCooldown <= 0.0)
	{
		this->currentHealth -= damage;
		damageCooldown = 0.5f;
		return true;
	}

	return false;
}

void Character::Knockback(const Vector2 &knockback)
{
	velocity += knockback;
}

//Tile System
void Character::SetTileSystem(TileSystem& tileSystem)
{
	this->tileSystem = &tileSystem;
}

void Character::RemoveTileSystem()
{
	this->tileSystem = nullptr;
}

//Bullets
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

//Collision Detection
vector<unsigned int>& Character::CheckCollisionLeft() {

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);
	TileCoord hotspotTile;

	//We need a vector to store our results.
	static vector<unsigned int> result;
	if (result.size() < tileCollider.GetNumHotspotsHeight()) {
		result.resize(tileCollider.GetNumHotspotsHeight(), 0);
	}

	//Check for collision against walls.
	for (int i = 0; i < tileCollider.GetNumHotspotsHeight(); ++i) {
		result[i] = 0;
		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));

		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		} else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		result[i] = tileSystem->TileValue(hotspotTile.row, hotspotTile.column);
		
		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

	return result;

}

vector<unsigned int>& Character::CheckCollisionRight() {
	
	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x + tileCollider.GetDetectionWidth() * 0.5f, position.y - tileCollider.GetLengthHeight() * 0.5f);
	TileCoord hotspotTile;

	//We need a vector to store our results.
	static vector<unsigned int> result;
	if (result.size() < tileCollider.GetNumHotspotsHeight()) {
		result.resize(tileCollider.GetNumHotspotsHeight(), 0);
	}

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) {		
		result[i] = 0;
		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));

		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		} else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows()) {
			//Update the position of the hotspot.
			hotspot.y += tileCollider.GetHotspotOffsetHeight();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		result[i] = tileSystem->TileValue(hotspotTile.row, hotspotTile.column);

		//Update the position of the hotspot.
		hotspot.y += tileCollider.GetHotspotOffsetHeight();
	}

	return result;

}

vector<unsigned int>& Character::CheckCollisionDown() {

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y - tileCollider.GetDetectionHeight() * 0.5f);
	TileCoord hotspotTile;

	//We need a vector to store our results.
	static vector<unsigned int> result;
	if (result.size() < tileCollider.GetNumHotspotsHeight()) {
		result.resize(tileCollider.GetNumHotspotsHeight(), 0);
	}

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i) 
	{
		result[i] = 0;

		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));
		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns()) {
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		} else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows()) {
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		result[i] = tileSystem->TileValue(hotspotTile.row, hotspotTile.column);
		
		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

	return result;

}

vector<unsigned int>& Character::CheckCollisionUp() {

	//Starting position of the hotspots we're checking.
	Vector2 hotspot(position.x - tileCollider.GetLengthWidth() * 0.5f, position.y + tileCollider.GetDetectionHeight() * 0.5f);
	TileCoord hotspotTile;
	
	//We need a vector to store our results.
	static vector<unsigned int> result;
	if (result.size() < tileCollider.GetNumHotspotsHeight()) {
		result.resize(tileCollider.GetNumHotspotsHeight(), 0);
	}

	//Check for collision against walls or falling through the map.
	for (int i = 0; i < tileCollider.GetNumHotspotsWidth(); ++i)
	{
		result[i] = 0;

		//Which tile our hotspot is in
		hotspotTile.Set(tileSystem->GetTile(hotspot.y), tileSystem->GetTile(hotspot.x));

		//Check if we're within the map's bounds.
		if (hotspotTile.column < 0 || hotspotTile.column >= tileSystem->GetNumColumns())
		{			
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		}
		else if (hotspotTile.row < 0 || hotspotTile.row >= tileSystem->GetNumRows())
		{
			//Update the position of the hotspot.
			hotspot.x += tileCollider.GetHotspotOffsetWidth();
			continue; //We aren't. Don't bother with this hotspot.
		}

		//Okay, we're within the map's boundaries.
		//Let's see if we hit any walls.
		result[i] = tileSystem->TileValue(hotspotTile.row, hotspotTile.column);
		
		//Update the position of the hotspot.
		hotspot.x += tileCollider.GetHotspotOffsetWidth();
	}

	return result;

}

unsigned int& Character::CheckCollisionCentre() {

	//What tile is our centre currently in.
	TileCoord currentTile(tileSystem->GetTile(position.y), tileSystem->GetTile(position.x));
	
	static unsigned int result = 0;
	result = 0;

	//Check if we're within the map's bounds.
	if (currentTile.column < 0 || currentTile.column >= tileSystem->GetNumColumns()) {			
		return result; //We aren't. Don't bother with this hotspot.
	} else if (currentTile.row < 0 || currentTile.row >= tileSystem->GetNumRows())	 {
		return result;
	}

	result = tileSystem->TileValue(currentTile.row, currentTile.column);

	return result;

}

//Virtual Function(s)
void Character::Update(const double& deltaTime) {

	damageCooldown = Math::Max(0.0f, damageCooldown -= static_cast<float>(deltaTime));
	shootingCooldown = Math::Max(0.0f, shootingCooldown -= static_cast<float>(deltaTime));

}