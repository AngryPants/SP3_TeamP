#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Bullet.h"
#include "Hero.h"
#include <list>
#include <map>
#include <vector>
#include <string>
#include <type_traits>
#include <typeinfo>
#include "EntityManager.h"

using namespace std;

class GameManager {

private:
	map<string, vector<Bullet*>> bulletMap;
	std::string sceneName;

public:
	//Constructor(s) & Destructor
	GameManager(const string& sceneName);
	virtual ~GameManager();

	void SetScene(const string& sceneName);
	string GetScene() const;

	void ClearBullets();
	void DestroyBullets();

	template <class Type>
	Type* GetBullet() {
		if (is_base_of<Bullet, Type>::value == false) {
			cout << "Cannot use GetBullet on something that is not a bullet." << endl;
			return nullptr;
		}

		bool keyExist = false;
		map<string, vector<Bullet*>>::iterator mapIter = bulletMap.find(typeid(Type).name());
		if (mapIter != bulletMap.end()) {
			keyExist = true;
			for (vector<Bullet*>::iterator bulletIter = mapIter->second.begin(); bulletIter != mapIter->second.end(); ++bulletIter) {
				if ((*bulletIter)->isActive == false) {
					return static_cast<Type*>(*bulletIter);
				}
			}
		}
		
		Type* bullet = new Type();
		if (keyExist) {
			mapIter->second.push_back(bullet);
		} else {
			vector<Bullet*> bulletVector;
			bulletVector.push_back(bullet);
			bulletMap.insert(pair<string, vector<Bullet*>>(typeid(Type).name(), bulletVector));
		}

		EntityManager::GetInstance().AddEntity(sceneName, *bullet);
		return bullet;
	}

};

#endif