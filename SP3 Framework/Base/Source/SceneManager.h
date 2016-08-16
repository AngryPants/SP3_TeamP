#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include <map>
#include <stack>
#include <string>
#include <iostream>

using std::map;
using std::stack;
using std::pair;
using std::string;
using std::cout;
using std::endl;

class Scene;

typedef map<string, Scene*> SceneMap;

class SceneManager : public Singleton<SceneManager> {

	friend class Singleton<SceneManager>;

private:
	//Variable(s)
	Scene* activeScene;
	Scene* nextScene;
	SceneMap sceneMap; //Stores all of our scenes.
	stack<string> removeStack; //The scenes we need to remove.

	//Constructor(s) & Destructor
	SceneManager();
	virtual ~SceneManager();

	//Private
	Scene* GetScene(const string& sceneName);

public:
	//System Interface Function(s)
	void Update(const double& deltaTime);
	void Render();
	void Exit();

	//User Interface Function(s)
	bool CheckSceneExist(const string& sceneName) const;
	bool AddScene(const string& sceneName, Scene& scene);
	bool RemoveScene(const string& sceneName);
	bool SetActiveScene(const string& sceneName, bool exitCurrent);

};

#endif