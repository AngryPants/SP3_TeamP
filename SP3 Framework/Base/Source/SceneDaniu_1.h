#ifndef SCENE_DANIU_1_H
#define SCENE_DANIU_1_H

#include "SceneBase.h"

class SceneDaniu_1 : public SceneBase {

protected:
	virtual void InitHero();
	virtual void InitCamera();
	virtual void InitEnemies();
	virtual void InitSawblades();

public:
	//Constructor(s) & Destructor
	SceneDaniu_1();
	virtual ~SceneDaniu_1();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif