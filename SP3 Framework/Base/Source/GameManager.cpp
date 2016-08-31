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
			scene->tileMapFile = "Levels//Level2//TM.csv";
			scene->sawbladesFile = "Levels//Level2//SB.txt";
			scene->bgmFile = "Audio//BGM//Back_On_Track.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::BODY;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Level_3") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_4";
			scene->tileMapFile = "Levels//Level3//TM.csv";
			scene->sawbladesFile = "Levels//Level3//SB.txt";
			scene->bgmFile = "Audio//BGM//Dry_Out.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::ARMS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Level_4") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_5";
			scene->tileMapFile = "Levels//Level4//TM.csv";
			scene->sawbladesFile = "Levels//Level4//SB.txt";
			scene->bgmFile = "Audio//BGM//Dry_Out.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::LEGS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Level_5") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_6";
			scene->tileMapFile = "Levels//Level5//TM.csv";
			scene->sawbladesFile = "Levels//Level5//SB.txt";
			scene->bgmFile = "Audio//BGM//Forever_Bound_Stereo_Madness.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::HEAD;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Level_6") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_7";
			scene->tileMapFile = "Levels//Level6//TM.csv";
			scene->sawbladesFile = "Levels//Level6//SB.txt";
			scene->bgmFile = "Audio//BGM//Forever_Bound_Stereo_Madness.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::BODY;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Level_7") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Level_8";
			scene->tileMapFile = "Levels//Level7//TM.csv";
			scene->sawbladesFile = "Levels//Level7//SB.txt";
			scene->bgmFile = "Audio//BGM//Base_After_Base.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::ARMS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Level_8") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneBase* scene = new SceneBase(sceneName);
			scene->nextScene = "Main_Menu";
			scene->tileMapFile = "Levels//Level8//TM.csv";
			scene->sawbladesFile = "Levels//Level8//SB.txt";
			scene->bgmFile = "Audio//BGM//Base_After_Base.mp3";
			scene->unlockCharacter = "Seetwo";
			scene->unlockPart = SceneBase::PART::LEGS;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else if (sceneName == "Main_Menu") {
		if (!SceneManager::GetInstance().CheckSceneExist(sceneName)) {
			SceneMainMenu* scene = new SceneMainMenu(sceneName);
			scene->bgm = "Audio//BGM//Forever_Bound_Stereo_Madness.mp3";
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return true;
	}
	else {
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
			scene->bgmFile = "Audio//BGM//Back_On_Track.mp3";
			scene->unlockCharacter = "Daniu";
			scene->unlockPart = SceneBase::PART::HEAD;
		}
		SceneManager::GetInstance().SetActiveScene(sceneName);
		return false;
	}

	return false;

}