#include "GameManager.h"

GameManager::GameManager(const string& sceneName) {

	this->sceneName = sceneName;

}

GameManager::~GameManager() {
}

void GameManager::SetScene(const string& sceneName) {

	this->sceneName = sceneName;

}

string GameManager::GetScene() const {

	return this->sceneName;

}

void GameManager::ClearBullets() {

	bulletMap.clear();

}

void GameManager::DestroyBullets() {

	for (map<string, vector<Bullet*>>::iterator mapIter = bulletMap.begin(); mapIter != bulletMap.end(); ++mapIter) {
		for (vector<Bullet*>::iterator bulletIter = mapIter->second.begin(); bulletIter != mapIter->second.end(); ++bulletIter) {
			(*bulletIter)->Destroy();
		}
	}

	bulletMap.clear();

}