#ifndef SCENE_LEVEL_4_H
#define SCENE_LEVEL_4_H

#include "SceneBase.h"

class Scene_Level4 : public SceneBase {

public:
	//Constructor(s) & Destructor
	Scene_Level4();
	virtual ~Scene_Level4();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif