#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "SingletonTemplate.h"
#include <set>
#include <string>

using namespace std;

class Scene;

class GameManager : public Singleton<GameManager> {

	friend class Singleton<GameManager>;

private:
	//Constructor(s) & Destructor
	GameManager();
	virtual ~GameManager();

public:
	//Function(s)
	bool GoToScene(string sceneName);

};

#endif