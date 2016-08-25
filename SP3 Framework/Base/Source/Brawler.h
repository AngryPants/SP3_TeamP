#ifndef BRAWLER_H
#define BRAWLER_H

#include "Enemy.h"

class Brawler : public Enemy {

public:
	//Constructor(s) & Destructor
	Brawler(const string& sceneName);
	virtual ~Brawler();

	//Combat
	virtual void AlertAllies(const double& deltaTime);
	virtual void Attack();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();

};

#endif