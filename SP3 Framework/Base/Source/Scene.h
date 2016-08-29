#ifndef SCENE_H
#define SCENE_H

#include <string>
#include "SceneManager.h"

using std::string;

//NOTE: No 2 scenes should ever have the same name. Doing so will fuck things up bad. Real bad.

class Scene {

public:
	//Variable(s)
	const string name;

	//Constructor(s) & Destructor
	Scene(const string& name) : name(name) {
		SceneManager::GetInstance().AddScene(*this);		
	}
	virtual ~Scene() {}
	
	//Virtual Function(s)
	virtual void Init() = 0;
	virtual void Save() {}
	virtual void Load() {}
	virtual void Update(const double& deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;

};

#endif