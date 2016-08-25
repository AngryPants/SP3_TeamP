#include "Enemy.h"
#include "CollisionSystem.h"

//Constructor(s) & Destructor
Enemy::Enemy(const string& name, const string& sceneName) : Character(name, sceneName) {
	viewAngle = 5.0f;
	viewRange = 10.0f;
		
	alertRadius = 5.0f;
	alertTime = 5.0f;
	alertTimer = alertTime;
	hasAlertedAllies = false;
	isAlerted = false;
	
	attackRange = 10.0f;	

	target = nullptr;
	allies = nullptr;
	
	currentState = nullptr;
}

Enemy::~Enemy() {
}

//Allies
void Enemy::SetAllies(set<Enemy*>* allies) {
	this->allies = allies;
}

void Enemy::RemoveAllies() {
	this->allies = allies;
}

set<Enemy*>* Enemy::GetAllies() {
	return this->allies;
}

//Target
void Enemy::SetTarget(Hero* target) {
	this->target = target;
}

Hero* Enemy::GetTarget() {
	return this->target;
}

//Alert
float Enemy::GetAlertTime() const {
	return this->alertTime;
}

void Enemy::SetAlertTime(const float& alertTime) {
	this->alertTime = alertTime;
}

void Enemy::SetAlertRadius(const float& alertRadius) {
	this->alertRadius = alertRadius;
}

float Enemy::GetAlertRadius() const {
	return this->alertRadius;
}

bool Enemy::CanSeePlayer() const {
	Vector2 relativePosition = target->position - position;
	if (relativePosition.LengthSquared() < Math::EPSILON) {
		return true;
	} else if (GetForwardDirection().AngleBetween(relativePosition) < viewAngle && relativePosition.LengthSquared() <= viewRange * viewRange) {
		return true;
	}

	return false;
}

//Combat
void Enemy::SetAttackRange(const float& attackRange) {
	this->attackRange = attackRange;
}

float Enemy::GetAttackRange() const {
	return this->attackRange;
}

//Strategy
void Enemy::SetState(AIState* state) {
	this->currentState = state;
}

//Movement
bool Enemy::IsOnEdgeLeft() {
	return GetTileInfo(TILE_INFO::TERRAIN, CheckCollisionDown()[0]) == TILE_NOTHING;
}

bool Enemy::IsOnEdgeRight() {
	return GetTileInfo(TILE_INFO::TERRAIN, CheckCollisionDown().back()) == TILE_NOTHING;
}

bool Enemy::HitWallRight() {
	vector<unsigned int>& collisionResult = CheckCollisionRight();
	for (size_t i = 0; i < collisionResult.size(); ++i) {
		if (GetTileInfo(TILE_INFO::TERRAIN, collisionResult[i]) != TILE_NOTHING) {
			return true;
		}
	}
	return false;
}

bool Enemy::HitWallLeft() {
	vector<unsigned int>& collisionResult = CheckCollisionLeft();
	for (size_t i = 0; i < collisionResult.size(); ++i) {
		if (GetTileInfo(TILE_INFO::TERRAIN, collisionResult[i]) != TILE_NOTHING) {
			return true;
		}
	}
	return false;
}

//Combat
void Enemy::Alert() {
	isAlerted = true;
}

void Enemy::UnAlert() {
	isAlerted = false;
}

//Virtual Function(s)
void Enemy::UpdateBullets(const double& deltaTime) {

	for (vector<Bullet*>::iterator bulletIter = bullets.begin(); bulletIter != bullets.end(); ++bulletIter) {
		Bullet* bulletPtr = *bulletIter;
		if (!bulletPtr->isActive) {
			continue;
		}
		bulletPtr->Update(deltaTime);
		//Hurt Enemies
		if (target != nullptr) {
			float timeToCollision = CollisionSystem::CircleCircle(bulletPtr->position, target->position, bulletPtr->radius, target->GetCollisionRadius(), bulletPtr->velocity, target->velocity);
			if (timeToCollision > 0.0f && timeToCollision <= static_cast<float>(deltaTime)) {
				target->TakeDamage(bulletPtr->damage);
				bulletPtr->isActive = false;
				break;
			}
		}
		//Despawn if hit wall
		if (tileSystem != nullptr) {
			TileCoord bulletCoord;
			bulletCoord.Set(tileSystem->GetTile(bulletPtr->position.y), tileSystem->GetTile(bulletPtr->position.x));
			//Check if we are out of the map
			if (bulletCoord.column < 0 || bulletCoord.column >= tileSystem->GetNumColumns()) {
				bulletPtr->isActive = false;
				continue;
			} else if (bulletCoord.row < 0 || bulletCoord.row >= tileSystem->GetNumRows()) {
				bulletPtr->isActive = false;
				continue;
			}
			//Check if we hit a wall
			unsigned int terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem->TileValue(bulletCoord.row, bulletCoord.column));
			if (terrain != TILE_NOTHING) {
				bulletPtr->isActive = false;
			}
		}
	}

}