#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "SingletonTemplate.h"
#include <string>
#include <map>
#include <list>

using std::string;
using std::map;
using std::list;

class EntityBase;

typedef map<string, list<EntityBase*> > EntityList;

//The EntityManager is purely in charge of calling the update and render functions of the entities. It does not
//handle creation and destruction.
class EntityManager : public Singleton<EntityManager> {

	friend class Singleton<EntityManager>;

private:
	EntityList entityList;

	//Constructor(s) & Destructor
	EntityManager();
	virtual ~EntityManager();

public:
	void Update(const string& sceneName, const double& deltaTime);
	void Render(const string& sceneName);
	void RenderUI(const string& sceneName);
	bool AddEntity(const string& sceneName, EntityBase& entity);
	bool RemoveEntity(const string& sceneName, EntityBase& entity);
	void ClearScene(const string& sceneName);

};

#endif