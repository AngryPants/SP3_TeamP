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

	EntityList::iterator listIter = entityList.find(sceneName);
	if (listIter == entityList.end()) {
		cout << "Unable to update " << sceneName << " as it does not exist in the EntityManager." << endl;
		return;
	}

	for (list<EntityBase*>::iterator entityIter = listIter->second.begin(); entityIter != listIter->second.end();) {
		if ((*entityIter)->IsDestroyed()) {
			//Delete this entity.
			delete (*entityIter);
			entityIter = listIter->second.erase(entityIter);
		} else {
			(*entityIter)->Update(deltaTime);
			 ++entityIter;
		}
	}

}

void EntityManager::Render(const string& sceneName) {

	EntityList::iterator listIter = entityList.find(sceneName);
	if (listIter == entityList.end()) {
		return;
	}

	for (list<EntityBase*>::iterator entityIter = listIter->second.begin(); entityIter != listIter->second.end(); ++entityIter) {
		(*entityIter)->Render();
	}

}

void EntityManager::RenderUI(const string& sceneName) {

	EntityList::iterator listIter = entityList.find(sceneName);
	if (listIter == entityList.end()) {
		return;
	}

	for (list<EntityBase*>::iterator entityIter = listIter->second.begin(); entityIter != listIter->second.end(); ++entityIter) {
		(*entityIter)->RenderUI();
	}

}

bool EntityManager::AddEntity(const string& sceneName, EntityBase& entityPtr) {
	
	EntityList::iterator listIter = entityList.find(sceneName);

	//We don't have a record of this scene yet.
	if (listIter == entityList.end()) {
		list<EntityBase*> newList;
		newList.push_front(&entityPtr);
		entityList.insert(std::pair<string, list<EntityBase*> >(sceneName,  newList));		
		return true;
	}

	//We already have a list from this scene.
	for (list<EntityBase*>::iterator entityIter = listIter->second.begin(); entityIter != listIter->second.end(); ++entityIter) {
		if ((*entityIter) == &entityPtr) {
			cout << "The entity already exist in the manager, cannot add again." << endl;
			return false;
		}
		break;
	}

	//This entity doesn't exist in our manager yet. Add it.
	listIter->second.push_back(&entityPtr);

	return true;

}

bool EntityManager::RemoveEntity(const string& sceneName, EntityBase& entity) {

	EntityList::iterator listIter = entityList.find(sceneName);
	if (listIter == entityList.end()) {
		cout << "Error: Scene " << sceneName << "not found." << endl;
		return false;
	}

	for (list<EntityBase*>::iterator entityIter = listIter->second.begin(); entityIter != listIter->second.end(); ++entityIter) {
		if ((*entityIter) == &entity) {
			entityIter = listIter->second.erase(entityIter);
		}
		break;
	}

	//If that list is empty, we delete it.
	if (listIter->second.size() == 0) {
		entityList.erase(listIter);
	}

	return true;

}

void EntityManager::ClearScene(const string& sceneName) {

	EntityList::iterator listIter = entityList.find(sceneName);
	if (listIter == entityList.end()) {
		return;
	}
	
	//Delete da stuff.
	for (list<EntityBase*>::iterator entityIter = listIter->second.begin(); entityIter != listIter->second.end();) {
		if (*entityIter) {
			entityIter = listIter->second.erase(entityIter);
		} else {
			++entityIter;
		}
	}

	//Delete da list.
	entityList.erase(listIter);

}