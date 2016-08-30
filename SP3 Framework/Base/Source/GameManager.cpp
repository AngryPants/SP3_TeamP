#include "GameManager.h"
#include "SceneManager.h"

#include "SceneBase.h"

//Constructor(s) & Destructor
GameManager::GameManager() {
}

GameManager::~GameManager() {
}

//Function(s)
bool GameManager::GoToScene(const string& sceneName) {

	if (sceneName == "Level_1") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_2";
			scene->tileMapFile = "Levels//Level1//TM.csv";
			scene->sawbladesFile = "Levels//Level1//SB.txt";	
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_2") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_3";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
		}
			SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_3") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_4";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
		}
			SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_4") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_5";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
		}
			SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Main Menu") {
		/*if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new Scene_Level5();
			SceneManager::GetInstance().SetActiveScene(scene->name);
		} else {
			SceneManager::GetInstance().SetActiveScene(sceneName);
		}
		return true;*/
	} else {
		cout << "Error: Unrecognised Level!" << endl;
	}

	return false;

}