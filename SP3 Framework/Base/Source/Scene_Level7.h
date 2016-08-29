#ifndef SCENE_LEVEL_7_H
#define SCENE_LEVEL_7_H

#include "SceneBase.h"

class Scene_Level7 : public SceneBase {

public:
	//Constructor(s) & Destructor
	Scene_Level7();
	virtual ~Scene_Level7();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif