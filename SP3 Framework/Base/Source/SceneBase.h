#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Camera2D.h"
#include "Hero.h"
#include "TileIndex.h"
#include "TileSystem.h"
#include "Sawblade.h"
#include <map>
#include "GameManager.h"

using std::map;

class SceneBase : public Scene {

protected:
	double minFPS;
	Camera2D* camera;
	TileSystem tileSystem;
	Hero* hero;
	map<int, Sawblade*> sawblades;
	GameManager gameManager;

	virtual void InitHero() = 0;
	virtual void InitCamera() = 0;
	virtual void InitEnemies() = 0;
	virtual void InitSawblades();

	bool debugMode;

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