#include "Character.h"

Character::Character() : isAlive(true), position(0, 0),
health(1), speed(1), damage(0), fireRate(1), mesh(nullptr) {
}

Character::Character(bool bIsAlive, Vector2 position, int health, float speed, int damage, float fireRate) {
	
	this->isAlive = bIsAlive;
	this->position = position;
	this->health = health;
	this->speed = speed;
	this->damage = damage;
	this->fireRate = fireRate;

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