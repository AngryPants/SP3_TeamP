#ifndef SCENE_LEVEL_5_H
#define SCENE_LEVEL_5_H

#include "SceneBase.h"

class Scene_Level5 : public SceneBase {

public:
	//Constructor(s) & Destructor
	Scene_Level5();
	virtual ~Scene_Level5();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif