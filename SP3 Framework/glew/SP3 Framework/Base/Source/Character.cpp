#include "Character.h"

Character::Character()
{
	this->isAlive = true;
	this->position.SetZero();
	this->scale.Set(1, 1);
	this->health = 1;
	this->speed = 1;
	this->damage = 0;
	this->fireRate = 1;
	this->onGround = true;
	this->mesh = nullptr;
	this->tileSystem = nullptr;
}

Character::~Character() {
}

void Character::Update(const double &deltaTime) {
}

void Character::Render() {
}

void Character::RenderUI() {
}

//Stats
int Character::GetHealth() const {

	return this->health;

}

float Character::GetSpeed() const {

	return this->speed;

}

int Character::GetDamage() const {

	return this->damage;

}

float Character::GetFireRate() const {

	return this->fireRate;

}

void Character::SetHealth(const int& health) {

	this->health = health;

}

void Character::SetSpeed(const float& speed) {

	this->speed = speed;

}

void Character::SetDamage(const float& damage) {

	this->damage = damage;

}

void Character::SetFireRate(const float& fireRate) {

	this->fireRate = fireRate;

}

void Character::SetTileSystem(TileSystem& tileSystem) {

	this->tileSystem = &tileSystem;

}

void Character::RemoveTileSystem() {

	this->tileSystem = nullptr;

}