#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"
#include "AnimationFSM_Turret.h"

class Turret : public Enemy {

private:
	enum class STATE {
		PATROL,
		COMBAT,
		DEAD,
	};

	STATE currentState;
	AnimationFSM_Turret animationFSM;

	//Movement
	void Move(const double& deltaTime);

	//Patrol
	float patrolTime;
	void Patrol(const double& deltaTime);

	//Combat
	float cannotSeePlayerTimer;
	void Combat(const double& deltaTime);

	void Dead(const double& deltaTime);

public:
	//Constructor(s) & Destructor
	Turret(const string& sceneName);
	virtual ~Turret();
		
	//Combat
	virtual void Attack();
	virtual bool TakeDamage(const int& damage);

	//Movement
	virtual void MoveLeft();
	virtual void MoveRight();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void RenderBullets();
	virtual void Reset();

};

#endif