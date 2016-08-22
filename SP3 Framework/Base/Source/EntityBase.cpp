#include "EntityManager.h"
#include "EntityBase.h"

EntityBase::EntityBase(const std::string& name, const std::string& sceneName)
: name(name), sceneName(sceneName), isDestroyed(false) {

	EntityManager::GetInstance().AddEntity(sceneName, *this);

}

EntityBase::~EntityBase() {

	isDestroyed = true;
	EntityManager::GetInstance().RemoveEntity(this->sceneName, *this);

}

void EntityBase::Destroy() {

	this->isDestroyed = true;

}

bool EntityBase::IsDestroyed() {

	return this->isDestroyed;

}

void EntityBase::SetScene(const string& sceneName) {

	EntityManager::GetInstance().RemoveEntity(this->sceneName, *this);
	this->sceneName = sceneName;
	EntityManager::GetInstance().AddEntity(this->sceneName, *this);

}

const string& EntityBase::GetScene() const {

	return this->sceneName;

}

void EntityBase::Update(const double& deltaTime) {
}

void EntityBase::Render() {
}

void EntityBase::RenderUI() {
}