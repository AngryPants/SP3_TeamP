#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() {

	activeScene = nullptr;
	nextScene = nullptr;

}

SceneManager::~SceneManager() {

	Exit();

}

//Private Function(s)
Scene* SceneManager::GetScene(const string& sceneName) {

	SceneMap::iterator mapIter = sceneMap.find(sceneName);
	if (mapIter == sceneMap.end()) {
		cout << "Unable to get scene: " << sceneName << " as it does not exist in the SceneManager." << endl;
		return nullptr;
	}

	return mapIter->second;

}

//System Interface
void SceneManager::Update(const double& deltaTime) {

	//Check if we need to switch scenes.
	if (nextScene != nullptr) {
		if (activeScene != nullptr) {
			activeScene->Exit(); //Do we have an active scene we need to exit?
		}
		activeScene = nextScene;
		activeScene->Initialise();
		nextScene = nullptr;		
	}

	//Delete the scenes that we need to remove.
	while (removeStack.size() > 0) {
		Scene* scenePtr = GetScene(removeStack.top());
		//Check if our active scene is being removed.
		if (scenePtr == activeScene) {
			activeScene = nullptr;
		}
		scenePtr->Exit();
		delete scenePtr;
		sceneMap.erase(sceneMap.find(removeStack.top()));
		removeStack.pop();
	}

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

bool SceneManager::AddScene(const string& sceneName, Scene& scene) {

	if (CheckSceneExist(sceneName)) {
		cout << "Unable to add scene: " << sceneName << " as it already exist in the SceneManager.\n Please ensure that all scenes have unique names." << endl;	
		return false;
	}

	sceneMap.insert(pair<string, Scene*>(sceneName, &scene));

	return true;

}

bool SceneManager::RemoveScene(const string& sceneName) {

	Scene* scenePtr = GetScene(sceneName);

	if (scenePtr == nullptr) {
		cout << "Unable to remove scene: " << sceneName << " as it doesn't exist in the SceneManager." << endl;
		return false;
	}

	scenePtr->Exit();
	delete scenePtr;
	sceneMap.erase(sceneMap.find(sceneName));

	return true;

}

bool SceneManager::RemoveScene(const string& sceneName) {

	if (CheckSceneExist(sceneName)) {
		cout << "Unable to remove scene: " << sceneName << " as it doesn't exist in the SceneManager." << endl;
		return false;
	}

	removeStack.push(sceneName);

	return true;

}

bool SceneManager::SetActiveScene(const string& sceneName, bool exitCurrent) {

	Scene* scenePtr = GetScene(sceneName);

	if (scenePtr == nullptr) {
		cout << "Unable to set scene: " << sceneName << " as active it doesn't exist in the SceneManager." << endl;
		return false;
	}

	nextScene = scenePtr;

	return true;

}