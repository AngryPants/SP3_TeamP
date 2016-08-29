#include "EntityManager.h"
#include "EntityBase.h"
#include <iostream>

using std::cout;
using std::endl;

EntityManager::EntityManager() {
}

EntityManager::~EntityManager() {
}

void EntityManager::Update(const string& sceneName, const double& deltaTime) {

	AddEntities(sceneName);
	RemoveEntities(sceneName);	

	EntityMap::iterator mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		//cout << "EntityManager has nothing to update." << endl;
	}

	for (EntitySet::iterator setIter = mapIter->second.begin(); setIter != mapIter->second.end();) {
		if ((*setIter)->IsDestroyed() == false) {
			(*setIter)->Update(deltaTime);
			++setIter;
		} else {
			cout << "Deleting " << (*setIter)->name << endl;
			delete *setIter;
			setIter = mapIter->second.erase(setIter);
		}
	}

}

void EntityManager::Render(const string& sceneName) {

	//AddEntities(sceneName);
	//RemoveEntities(sceneName);

	EntityMap::iterator mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		return;
	}

	for (set<EntityBase*>::iterator setIter = mapIter->second.begin(); setIter != mapIter->second.end(); ++setIter) {
		if ((*setIter)->IsDestroyed() == false) {
			(*setIter)->Render();
		}
	}

}

void EntityManager::RenderUI(const string& sceneName) {

	//AddEntities(sceneName);
	//RemoveEntities(sceneName);	

	EntityMap::iterator mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		return;
	}

	for (set<EntityBase*>::iterator setIter = mapIter->second.begin(); setIter != mapIter->second.end(); ++setIter) {
		if ((*setIter)->IsDestroyed() == false) {
			(*setIter)->RenderUI();
		}
	}

}

//Adding and Removing Entities
bool EntityManager::AddEntity(const string& sceneName, EntityBase& entity) {
	
	//Check if there's already a list.
	EntityMap::iterator mapIter = toBeAdded.find(sceneName);
	if (mapIter == toBeAdded.end()) { //There isn't. Let's add one.
		EntitySet entitySet;
		entitySet.insert(&entity);
		toBeAdded.insert(std::pair<string, EntitySet>(sceneName, entitySet));
	} else { //There is.
		mapIter->second.insert(&entity);
	}

	cout << "EntityManager will add " << entity.name << " in the next update." << endl;

	return true;

}

bool EntityManager::RemoveEntity(const string& sceneName, EntityBase& entity) {

	//Check if it was supposed to be added. If yes, remove it from being added.
	EntityMap::iterator mapIter = toBeAdded.find(sceneName);
	if (mapIter != toBeAdded.end()) {
		EntitySet::iterator setIter = mapIter->second.find(&entity);
		if (setIter != mapIter->second.end()) {
			mapIter->second.erase(setIter);
		}
	}

	//Check if this scene even exist.
	mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		//cout << "The entity " << entity.name << " cannot be removed. As it has not been registed with the EntityManager" << endl;
		return false;
	}

	//Check if the entity was in the scene.
	EntitySet::iterator setIter = mapIter->second.find(&entity);
	if (setIter == mapIter->second.end()) {
		cout << "EntityManager says fuck you! We can't remove shit from a scene if it wasn't in it in the first place dumbass." << endl;
		return false;
	}

	//Let's add this to our list of things to be removed.
	mapIter = toBeRemoved.find(sceneName);
	if (mapIter == toBeRemoved.end()) {
		EntitySet entitySet;
		entitySet.insert(&entity);
		toBeRemoved.insert(std::pair<string, EntitySet>(sceneName, entitySet));
	} else {
		mapIter->second.insert(&entity);
	}

	cout << "Removed " << entity.name << "." << endl;

	return true;

}

void EntityManager::AddEntities(const string& sceneName) {

	EntityMap::iterator addMapIter = toBeAdded.find(sceneName);
	if (addMapIter == toBeAdded.end()) {
		cout << "Nothing To Add." << endl;
		return;
	}

	EntityMap::iterator mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		EntitySet entitySet;
		entityMap.insert(std::pair<string, EntitySet>(sceneName, entitySet));
		mapIter = entityMap.find(sceneName);
	}
	
	for (EntitySet::iterator setIter = addMapIter->second.begin(); setIter != addMapIter->second.end(); ++setIter) {
		mapIter->second.insert(*setIter);
		cout << "Added " << (*setIter)->name << "." << endl;
	}
	addMapIter->second.clear();

}

void EntityManager::RemoveEntities(const string& sceneName) {

	EntityMap::iterator mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		cout << "Cannot remove entities as scene " << sceneName << " does not exist in the SceneManager." << endl;
		return;
	}

	EntityMap::iterator removeMapIter = toBeRemoved.find(sceneName);
	if (removeMapIter == toBeRemoved.end()) {
		//cout << "Nothing to remove." << endl;
		return;
	}
	
	for (EntitySet::iterator setIter = removeMapIter->second.begin(); setIter != removeMapIter->second.end(); ++setIter) {
		mapIter->second.erase(*setIter);
	}

	removeMapIter->second.clear();

}

void EntityManager::ClearScene(const string& sceneName) {

	EntityMap::iterator mapIter = toBeAdded.find(sceneName);
	if (mapIter != toBeAdded.end()) {
		toBeAdded.erase(mapIter);
	}

	mapIter = toBeRemoved.find(sceneName);
	if (mapIter != toBeRemoved.end()) {
		toBeRemoved.erase(mapIter);
	}

	mapIter = entityMap.find(sceneName);
	if (mapIter != entityMap.end()) {
		entityMap.erase(mapIter);
	}

}

void EntityManager::DestroyScene(const string& sceneName) {

	AddEntities(sceneName);
	RemoveEntities(sceneName);

	EntityMap::iterator mapIter = entityMap.find(sceneName);
	if (mapIter == entityMap.end()) {
		cout << "EntityManager has nothing to destroy." << endl;
		return;
	}

	for (EntitySet::iterator setIter = mapIter->second.begin(); setIter != mapIter->second.end(); ++setIter) {
		cout << "Deleting " << (*setIter)->name << endl;
		delete *setIter;
	}

	ClearScene(sceneName);

}