#ifndef ENEMY_H
#define ENEMY_H

#include "Hero.h"
#include "TileIndex.h"

class AIState;

class Enemy : public Character {

	friend class AIState;

protected:
	//The enemy shall detect the player in a cone shape.
	float viewAngle;
	float viewRange;
	
	//Combat
	float alertTime; //How long it takes for us to alert the rest.
	float alertRadius; //How far we can alert.
	float attackRange;

	//The target of the AI.
	Hero* target;

	//The rest of the AIs
	set<Enemy*>* allies;

	//State
	AIState* currentState;

public:
	//Has this unit been alerted?
	bool isAlerted;

	//Constructor(s) & Destructor
	Enemy(const string& name, const string& sceneName);
	virtual ~Enemy();

	//Allies
	void SetAllies(set<Enemy*>* allies);
	void RemoveAllies();
	set<Enemy*>* GetAllies();

	//Target
	void SetTarget(Hero* target);
	Hero* GetTarget();

	//Alert
	void SetAlertTime(const float& alertTime);
	float GetAlertTime() const;
	void SetAlertRadius(const float& alertRadius);
	float GetAlertRadius() const;
	bool CanSeePlayer() const;

	//Combat
	void SetAttackRange(const float& attackRange);
	float GetAttackRange() const;

	//Strategy
	void SetState(AIState* state);

	//Movement
	virtual void MoveLeft() = 0;
	virtual void MoveRight() = 0;
	bool IsOnEdgeLeft();
	bool IsOnEdgeRight();
	bool HitWallRight();
	bool HitWallLeft();
	//virtual void Jump() = 0;

	//Combat
	virtual void Alert();
	virtual void UnAlert();
	virtual void Attack() = 0;

	//Virtual Function(s)
	virtual void Update(const double& deltaTime) = 0;
	virtual void UpdateBullets(const double& deltaTime);
	virtual void Render() {}
	virtual void RenderUI() {}
	virtual void RenderBullets() = 0;
	virtual void Reset() = 0;

};

#endif