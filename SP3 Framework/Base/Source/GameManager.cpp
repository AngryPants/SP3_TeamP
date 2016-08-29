#include "GameManager.h"
#include "SceneManager.h"

//Include Scenes
#include "Scene_Level1.h"
#include "Scene_Level2.h"
//#include "Scene_Level3.h"
//#include "Scene_Level4.h"
//#include "Scene_Level5.h"
//#include "Scene_Level6.h"
//#include "Scene_Level7.h"
//#include "Scene_Level8.h"

//Constructor(s) & Destructor
GameManager::GameManager() {
}

GameManager::~GameManager() {
}

//Function(s)
bool GameManager::GoToScene(const string& sceneName) {

	if (sceneName == "Level 1") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level1();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;
	} else if (sceneName == "Level 2") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level2();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;
	} else if (sceneName == "Level 3") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level3();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else if (sceneName == "Level 4") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level4();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else if (sceneName == "Level 5") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level5();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else if (sceneName == "Level 6") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level6();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else if (sceneName == "Level 7") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level5();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else if (sceneName == "Level 8") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level5();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else if (sceneName == "Main Menu") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level5();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	}

	return false;

}