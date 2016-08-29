#ifndef SCENE_LEVEL_6_H
#define SCENE_LEVEL_6_H

#include "SceneBase.h"

class Scene_Level6 : public SceneBase {

public:
	//Constructor(s) & Destructor
	Scene_Level6();
	virtual ~Scene_Level6();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif