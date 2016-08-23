#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class AIState;

class Enemy : public Character {

protected:
	//The enemy shall detect the player in a cone shape.
	float detectionAngle;
	float detectionRadius;

	//The target of the AI.
	Character* target;

	//The rest of the AIs
	set<Character*> allies;

	//The state of the Enemy.

public:
	//Constructor(s) & Destructor
	Enemy(const string& name, const string& sceneName);
	virtual ~Enemy();

	void SetTarget(Character* character);
	void RemoveTarget();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();

};

#endif