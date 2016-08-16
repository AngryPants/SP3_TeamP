#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"

class SceneBase : public Scene {

protected:

public:
	//Constructor(s) & Destructor
	SceneBase(const string& name) : Scene(name) {
	}
	virtual ~SceneBase();

	//Virtual Function(s)
	virtual void Initialise();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif