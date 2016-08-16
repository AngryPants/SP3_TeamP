#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "SceneManager.h"

using std::string;

class Scene {

public:
	//Variable(s)
	const string name;

	//Constructor(s) & Destructor
	Scene(const string& name) : name(name) {
		SceneManager::GetInstance().AddScene(name, *this);
	}
	virtual ~Scene() {}

	//Virtual Function(s)
	virtual void Initialise() = 0;
	virtual void Update(const double& deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

};

#endif