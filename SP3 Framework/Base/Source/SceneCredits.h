#ifndef SCENE_CREDITS_H
#define SCENE_CREDITS_H
#include "Scene.h"
#include "MeshBuilder.h"
#include "Texture.h"

class SceneCredits : public Scene
{
private:
	bool isKeyDown;

public:
	Mesh* mesh;
	Texture texture;
	string bgm;
	SceneCredits(const string& name);
	virtual ~SceneCredits();

	virtual void Init();
	virtual void Update(const double &deltaTime);
	virtual void Render();
	virtual void Exit();
};

#endif