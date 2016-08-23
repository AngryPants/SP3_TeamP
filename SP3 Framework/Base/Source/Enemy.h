#ifndef ENEMY_H
#define ENEMY_H

#include "Hero.h"

class AIStrategy;

class Enemy : public Character {

protected:
	//The enemy shall detect the player in a cone shape.
	float viewAngle;
	float viewRange;
	Vector2 viewDirection;

	//Alert
	float alertTime; //How long it takes for us to alert the rest.
	float alertTimeLeft; //How long more until we complete alerting our allies.
	float alertRadius; //How far we can alert.

	//The target of the AI.
	Hero* target;

	//The rest of the AIs
	set<Enemy*>* allies;

	//Strategies
	AIStrategy* currentStrategy;

public:
	//Has this unit been alerted?
	bool isAlerted;

	//Constructor(s) & Destructor
	Enemy(const string& name, const string& sceneName) : Character(name, sceneName) {
		viewAngle = 30.0f;
		viewRange = 10.0f;
		viewDirection.Set(1, 0);
		
		alertRadius = 5.0f;
		alertTime = 5.0f;
		alertTimeLeft = alertTime;
		isAlerted = false;
		
		target = nullptr;
		allies = nullptr;
		
		currentStrategy = nullptr;
	}
	virtual ~Enemy() {}

	//Set Allies
	void SetAllies(set<Enemy*>* allies) {
		this->allies = allies;
	}
	void RemoveAllies() {
		this->allies = allies;
	}

	//Target
	void SetTarget(Hero* target) {
		this->target = target;
	}
	void RemoveTarget() {
		this->target = nullptr;
	}

	//Strategy
	void SetStrategy(AIStrategy* strategy) {
		this->currentStrategy = strategy;
	}
	void RemoveStrategy() {
		this->currentStrategy = nullptr;
	}

	//Movement
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	//virtual void Jump() = 0;

	//Combat
	virtual void Alert() {
		isAlerted = true;
	}
	virtual void UnAlert() {
		isAlerted = false;
	}
	virtual void AlertAllies(const double& deltaTime) = 0;
	virtual void Attack() = 0;

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) {}
	virtual void Render() {}
	virtual void RenderUI() {}
	virtual void Reset() {
		alertTimeLeft = alertTime;
		isAlerted = false;
	}

};

#endif