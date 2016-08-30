#include "GameManager.h"
#include "SceneManager.h"

#include "SceneBase.h"
#include "SceneMainMenu.h"

//Constructor(s) & Destructor
GameManager::GameManager() {
}

GameManager::~GameManager() {
}

//Function(s)
bool GameManager::GoToScene(string sceneName) {

	if (sceneName == "Level_2") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_3";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::BODY;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_3") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_4";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::ARMS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_4") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_5";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::LEGS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_5") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_6";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::HEAD;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_6") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_7";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::BODY;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_7") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_8";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::ARMS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Level_8") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Main_Menu";
			scene->tileMapFile = "";
			scene->sawbladesFile = "";
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::LEGS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else if (sceneName == "Main_Menu") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			Scene* scene = new SceneMainMenu(sceneName);
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	} else {
		bool returnValue = true;
		if (sceneName != "Level_1") {
			returnValue = false;
			sceneName = "Level_1";
			cout << "Error: Unrecognised Level! Defaulting to " << sceneName << "!" << endl;
		}
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_2";
			scene->tileMapFile = "Levels//Level1//TM.csv";
			scene->sawbladesFile = "Levels//Level1//SB.txt";	
			scene->bgmFile = "Audio//BGM//BGM_Daniu.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::HEAD;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return false;
	}

	return false;

}