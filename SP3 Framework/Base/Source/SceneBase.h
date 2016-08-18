#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Camera2D.h"
#include "Hero.h"
#include "TileSystem.h"

class SceneBase : public Scene {

protected:
	double minFPS;
	Camera2D camera;
	TileSystem tileSystem;
	Hero* hero;

private:
	void InitShader();

public:
	//Constructor(s) & Destructor
	SceneBase(const string& name);
	virtual ~SceneBase();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif