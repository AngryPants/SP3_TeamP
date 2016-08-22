//#ifndef GAME_MANAGER_H
//#define GAME_MANAGER_H
//
//#include "SingletonTemplate.h"
//#include "Bullet.h"
//#include "Hero.h"
//#include <map>
//#include <set>
//#include <string>
//#include <type_traits>
//#include <typeinfo>
//
//using namespace std;
//
//class GameManager : public Singleton<GameManager> {
//
//	friend class Singleton<GameManager>;
//
//private:
//	map<string, Hero*> heroMap; //Stores the pointers of the hero for each scene.
//	map<string, set<Bullet*>> bulletMap; //Stores the pointers of bullets.
//	std::string sceneName;
//
//	//Constructor(s) & Destructor
//	GameManager();
//	virtual ~GameManager();
//
//public:
//	//Bullets
//	Bullet& GetBullet(const string& sceneName);
//	void ClearScene(const string& sceneName);
//
//	void Update(const double& deltaTime);
//
//	//Hero
//	template <class Type>
//	Hero* CreateHero(const string& sceneName) {
//		if (is_base_of<Hero, Type>::value == false) {
//			throw std::exception("Cannot use GetHero on a class that is not a child class of Hero. is not a child class of hero.");
//		}
//
//		map<string, Hero*>::iterator heroMapIter = heroMap.find(sceneName);
//		if (heroMapIter == heroMap.end()) {
//			heroMap.insert(std::pair<string, Hero*>(sceneName, nullptr));
//			heroMapIter = heroMap.find(sceneName);
//		}
//
//		//Destroy any hero that may still be there.
//		if (heroMapIter->second != nullptr) {
//			heroMapIter->second->Destroy();
//		}
//		heroMapIter->second = new Type(sceneName);
//
//		return heroMapIter->second;
//	}
//	Hero* GetHero(const string& sceneName);
//	void DestroyHero(const string& sceneName);
//
//};
//
//#endif