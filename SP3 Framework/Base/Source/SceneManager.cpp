#include "SceneManager.h"
#include "Scene.h"

//Constructor(s) & Destructor
SceneManager::SceneManager() {

	activeScene = nullptr;
	nextScene = nullptr;

}

SceneManager::~SceneManager() {

	Exit();

}

//Private Function(s)
Scene* SceneManager::GetScene(const string& sceneName) {

	//Check if this scene exist.
	SceneMap::iterator mapIter = sceneMap.find(sceneName);
	if (mapIter == sceneMap.end()) {
		//It does not exist.
		cout << "Unable to get scene: " << sceneName << " as it does not exist in the SceneManager." << endl;
		return nullptr;
	}

	return mapIter->second; //It exist.

}

//System Interface
void SceneManager::Update(const double& deltaTime) {

	//Check if we need to switch scenes.
	if (nextScene != nullptr) {
		if (activeScene != nullptr) {
			activeScene->Save();
			activeScene->Exit(); //Do we have an active scene we need to exit?
		}
		activeScene = nextScene;
		activeScene->Init();
		activeScene->Load();
		nextScene = nullptr;
	}

	//Add all the scenes we need to add
	for (set<Scene*>::iterator setIter = addQueue.begin(); setIter != addQueue.end(); ++setIter) {
		Scene* scenePtr = *(setIter);
		sceneMap.insert(pair<string, Scene*>(scenePtr->name, scenePtr));
		cout << "Added Scene " << scenePtr->name << "." << endl;
	}
	addQueue.clear();

	//Delete the scenes that we need to remove.
	for (set<Scene*>::iterator setIter = removeQueue.begin(); setIter != removeQueue.end(); ++setIter) {
		Scene* scenePtr = *(setIter);
		SceneMap::iterator mapIter = sceneMap.find(scenePtr->name);
		if (mapIter->second != scenePtr) {
			cout << "Something went wrong, and a pointer that is to be removed from SceneManager does not match up with the one in removeQueue." << endl;
			throw std::exception("SceneManager error with scene removal. Check SceneManager::Update");
		}
		sceneMap.erase(mapIter);
		if (scenePtr == activeScene) {
			activeScene = nullptr;
			scenePtr->Save();
			scenePtr->Exit();
		}
		cout << "Removed Scene " << scenePtr->name << "." << endl;
		delete scenePtr;
	}
	removeQueue.clear();

	//Check if we have an active scene.
	if (activeScene != nullptr) {
		activeScene->Update(deltaTime); //Update our active scene.
	}

}

void SceneManager::Render() {

	if (activeScene != nullptr) {
		activeScene->Render();
	}

}

void SceneManager::Exit() {

	//Delete all of our scenes.
	for (SceneMap::iterator mapIter = sceneMap.begin(); mapIter != sceneMap.end();) {
		if (mapIter->second != nullptr) {
			mapIter->second->Exit();
			delete mapIter->second;
		}
		mapIter = sceneMap.erase(mapIter);
	}

}

//User Interface
bool SceneManager::CheckSceneExist(const string& sceneName) const {

	return sceneMap.count(sceneName) != 0;

}

bool SceneManager::CheckSceneExist(const Scene& scene) const {

	for (SceneMap::const_iterator mapIter = sceneMap.begin(); mapIter != sceneMap.end(); ++mapIter) {
		if (mapIter->second == &scene) {
			return true;
		}
	}

	return false;

}

bool SceneManager::AddScene(Scene& scene) {

	//Make sure that the scene was not added twice and that there are no 2 scenes with the same name.
	if (CheckSceneExist(scene.name) || CheckSceneExist(scene)) {
		throw std::exception("A scene was either added twice, or 2 scenes have the same name.");
	}

	addQueue.insert(&scene);
	cout << "Added scene " << scene.name << " to the AddQueue." << endl;

	return true;

}

bool SceneManager::RemoveScene(const string& sceneName) {

	//Check if the scene is inside the AddQueue. If it is, we prevent it from being added altogether.
	bool inAddQueue = false;
	for (set<Scene*>::iterator setIter = addQueue.begin(); setIter != addQueue.end(); ++setIter) {
		Scene* scenePtr = *setIter;
		if (scenePtr->name == sceneName) {
			delete scenePtr; //There is no need to Exit() the scene as it has not been initalised yet.
			addQueue.erase(setIter);
			cout << "Scene " << sceneName << " has been removed from the AddQueue." << endl;
			return true;
		}
	}

	//If it isn't inside the AddQueue, make sure that it is inside sceneMap;
	if (!CheckSceneExist(sceneName)) {
		cout << "Unable to remove scene: " << sceneName << " as it doesn't exist in the SceneManager." << endl;
		return false;
	}

	//We found it inside our sceneMap. Let's add it to the remove queue.
	Scene* scenePtr = sceneMap.find(sceneName)->second;
	removeQueue.insert(scenePtr);
	cout << "Scene " << sceneName << " will be removed." << endl;
	return true;

}

bool SceneManager::SetActiveScene(const string& sceneName) {

	//Check if the scene is among the scenes already in our main sceneMap.
	Scene* scenePtr = GetScene(sceneName);
	
	//If it is a nullptr, that means that it was not in our main sceneMap.
	if (scenePtr == nullptr) {
		for (set<Scene*>::iterator setIter = addQueue.begin(); setIter != addQueue.end(); ++setIter) {
			if ((*setIter)->name == sceneName) {
				scenePtr = (*setIter);
				break;
			}
		}
	}

	//If it is still nullptr, it is no where in our SceneManager. GG.
	if (scenePtr == nullptr) {
		cout << "Unable to set scene: " << sceneName << " as active it doesn't exist in the SceneManager." << endl;
		return false;
	}

	nextScene = scenePtr;

	return true;

}