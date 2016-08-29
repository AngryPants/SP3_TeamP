#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "SingletonTemplate.h"
#include <map>
#include <set>
#include <string>
#include <iostream>

using std::map;
using std::set;
using std::pair;
using std::string;
using std::cout;
using std::endl;

/*

Scene Transition Procedure
Step 1: Save the current Scene.
Step 2: Exit the current Scene.
Step 3: Initialise the next Scene.
Step 4: Load the next Scene.

Scene Adding Procedure
Step 1: Check if the scene alreaedy exist in sceneMap.
Step 2: If it does not, check if it is already in the adding queue.
Step 3: If Step 1 or Step 2 is true, do not proceed. Otherwise, continue with Step 4.
Step 4: Add the new Scene to the adding queue.
Step 5: During the update, insert the new Scenes to sceneMap.
Step 6: Pop the new Scenes from the adding queue.

Scene Removal Procedure
Step 1: Find out if the Scene exist in sceneMap or the adding queue.
Step 2: If it does, remove it.

*/

class Scene;

typedef map<string, Scene*> SceneMap;

class SceneManager : public Singleton<SceneManager> {

	friend class Singleton<SceneManager>;

private:
	//Variable(s)
	Scene* activeScene; //The current active scene.
	Scene* nextScene; //The next scene.

	SceneMap sceneMap; //Stores all of our scenes.
	set<Scene*> removeQueue; //The scenes we need to remove.
	set<Scene*> addQueue; //The scenes we need to add.

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
	bool CheckSceneExist(const string& sceneName) const; //Check if a scene is in the main sceneMap of the SceneManager.
	bool CheckSceneExist(const Scene& scenePtr) const;
		
	bool AddScene(Scene& scene);
	bool RemoveScene(const string& sceneName);
	bool SetActiveScene(const string& sceneName);

};

#endif