//#include "GameManager.h"
//#include "EntityManager.h"
//
////Constructor(s) & Destructor
//GameManager::GameManager() {
//}
//
//GameManager::~GameManager() {
//}
//
//Bullet& GameManager::GetBullet(const string& sceneName) {
//
//	map<string, set<Bullet*>>::iterator bulletMapIter = bulletMap.find(sceneName);
//	if (bulletMapIter == bulletMap.end()) {
//		set<Bullet*> bulletSet;
//		bulletMap.insert(std::pair<string, set<Bullet*>>(sceneName, bulletSet));
//		cout << "" << endl;
//		bulletMapIter = bulletMap.find(sceneName);
//	}
//
//	for (set<Bullet*>::iterator bulletSetIter = bulletMapIter->second.begin(); bulletSetIter != bulletMapIter->second.end(); ++bulletSetIter) {
//		if ((*bulletSetIter)->isActive == false) {
//			return *(*bulletSetIter);
//		}
//	}
//
//	Bullet* bullet = new Bullet(sceneName);
//	bulletMapIter->second.insert(bullet);
//
//	return *bullet;
//
//}
//
//void GameManager::ClearScene(const string& sceneName) {
//
//	//Release all the bullets
//	map<string, set<Bullet*>>::iterator bulletMapIter = bulletMap.find(sceneName);
//	if (bulletMapIter != bulletMap.end()) {
//		bulletMap.erase(bulletMapIter);
//	}
//
//	//Release the hero
//	map<string, Hero*>::iterator heroMapIter = heroMap.find(sceneName);
//	if (heroMapIter == heroMap.end()) {
//		heroMap.erase(heroMapIter);
//	}
//
//}
//
//Hero* GameManager::GetHero(const string& sceneName) {
//
//	map<string, Hero*>::iterator heroMapIter = heroMap.find(sceneName);
//	if (heroMapIter == heroMap.end()) {
//		return nullptr;
//	}
//
//	return heroMapIter->second;
//
//}
//
//void GameManager::DestroyHero(const string& sceneName) {
//
//	map<string, Hero*>::iterator heroMapIter = heroMap.find(sceneName);
//	if (heroMapIter == heroMap.end()) {
//		return;
//	}
//
//	if (heroMapIter->second != nullptr) {
//		heroMapIter->second->Destroy();
//		heroMapIter->second = nullptr;
//	}
//
//}