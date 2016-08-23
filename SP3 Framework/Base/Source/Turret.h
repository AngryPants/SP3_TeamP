#ifndef TURRET_H
#define TURRET_H

#include "Enemy.h"

class Turret : public Enemy {

private:

public:
	//Constructor(s) & Destructor
	Turret(const string& sceneName);
	virtual ~Turret();

	//Movement
	virtual void MoveLeft() {}
	virtual void MoveRight() {}

	//Alert
	virtual void AlertAllies(const double& deltaTime);
	
	//Combat
	virtual void Attack();

};

#endif