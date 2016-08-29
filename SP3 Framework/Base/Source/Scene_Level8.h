#ifndef SCENE_LEVEL_8_H
#define SCENE_LEVEL_8_H

#include "SceneBase.h"

class Scene_Level8 : public SceneBase {

public:
	//Constructor(s) & Destructor
	Scene_Level8();
	virtual ~Scene_Level8();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif