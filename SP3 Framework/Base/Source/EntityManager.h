/******************************************************************************/
/*!
\file	EntityManager.h
\author Lim Ngian Xin Terry
\par	email: 150496F@mymail.nyp.edu.sg
\brief
Class that is purely in charge of calling the update and render functions of the entities. It does not handle creation and destruction.
*/
/******************************************************************************/

#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "SingletonTemplate.h"
#include <string>
#include <map>
#include <set>
#include <list>

using std::string;
using std::map;
using std::list;
using std::set;

class EntityBase;

typedef set<EntityBase*> EntitySet;
typedef map<string, EntitySet> EntityMap;

/******************************************************************************/
/*!
		Class EntityManager:
\brief	The EntityManager is purely in charge of calling the update and render functions of the entities. It does not handle creation and destruction.
*/
/******************************************************************************/

class EntityManager : public Singleton<EntityManager> {

	friend class Singleton<EntityManager>;

private:
	EntityMap entityMap;
	EntityMap toBeAdded;
	EntityMap toBeRemoved;

	//Constructor(s) & Destructor
	EntityManager();
	virtual ~EntityManager();

	//Adding and Removing Entities
	void AddEntities(const string& sceneName);
	void RemoveEntities(const string& sceneName);

public:
	void Update(const string& sceneName, const double& deltaTime);
	void Render(const string& sceneName);
	void RenderUI(const string& sceneName);
	
	//Adding and Removing Entities
	bool AddEntity(const string& sceneName, EntityBase& entity);
	bool RemoveEntity(const string& sceneName, EntityBase& entity);
	void ClearScene(const string& sceneName);
	void DestroyScene(const string& sceneName);

};

#endif