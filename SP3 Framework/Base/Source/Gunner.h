#ifndef GUNNER_H
#define GUNNER_H

#include "Enemy.h"
#include "AnimationFSM_Gunner.h"

class Gunner : public Enemy {

private:
	enum class STATE {
		PATROL,
		COMBAT,
		ALERT,
		DEAD,
	};

	STATE currentState;
	AnimationFSM_Gunner animationFSM;

	//Movement
	bool canWalkLeft;
	bool canWalkRight;
	void Move(const double& deltaTime);

	//Patrol
	float patrolTime;
	bool shouldMove;
	void Patrol(const double& deltaTime);

	//Alert
	float alertTimer;
	virtual void AlertAllies(const double& deltaTime);
	virtual void Alert();
	Texture alertTexture;
	Mesh* alertMesh;

	//Combat
	float cannotSeePlayerTimer;
	void Combat(const double& deltaTime);
	void Chase();
	virtual void Attack();
	virtual bool TakeDamage(const int& damage);
	Mesh* bulletMesh;

	//Dead
	void Dead(const double& deltaTime);

public:
	//Constructor(s) & Destructor
	Gunner(const string& sceneName);
	virtual ~Gunner();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void RenderBullets();
	virtual void Reset();

};

#endif