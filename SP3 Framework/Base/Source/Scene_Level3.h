#ifndef SCENE_LEVEL_3_H
#define SCENE_LEVEL_3_H

#include "SceneBase.h"

class Scene_Level3 : public SceneBase {

public:
	//Constructor(s) & Destructor
	Scene_Level3();
	virtual ~Scene_Level3();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif