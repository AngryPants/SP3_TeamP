#ifndef BRAWLER_H
#define BRAWLER_H

#include "Enemy.h"
#include "AnimationFSM_Brawler.h"

class Brawler : public Enemy {

private:
	enum class STATE {
		PATROL,
		COMBAT,
		ALERT,
		DEAD,
	};

	STATE currentState;
	AnimationFSM_Brawler animationFSM;

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

	//Dead
	void Dead(const double& deltaTime);

public:
	//Constructor(s) & Destructor
	Brawler(const string& sceneName);
	virtual ~Brawler();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();
	virtual void Reset();

};

#endif