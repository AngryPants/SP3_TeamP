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
	void Fall(const double& deltaTime);

	//Patrol
	float patrolTime;
	void Patrol(const double& deltaTime);

	//Combat
	float cannotSeePlayerTimer;
	void Combat(const double& deltaTime);
	virtual void Attack();

	//Dead
	void Dead(const double& deltaTime);

	//Bullet
	Mesh* bulletMesh;

public:
	//Constructor(s) & Destructor
	Turret(const string& sceneName);
	virtual ~Turret();
		
	//Combat
	virtual bool TakeDamage(const int& damage);
	virtual void Alert();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void RenderBullets();
	virtual void Reset();

};

#endif