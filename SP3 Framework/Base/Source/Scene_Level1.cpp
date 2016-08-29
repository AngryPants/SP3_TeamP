#include "Scene_Level1.h"
#include "EntityManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "MapRenderer.h"
#include "Kifellah.h"
#include "Daniu.h"
#include "Seetwo.h"
#include "TileIndex.h"

Scene_Level1::Scene_Level1() : SceneBase("Level 1") {
}

Scene_Level1::~Scene_Level1() {
}

void Scene_Level1::Init() {

	SceneBase::Init();

	tileSystem.LoadFile("Level//Daniu//Daniu_Level_2.csv");
	tileSystem.LoadFile("Levels//Level1//TM.csv");
	SceneBase::ResetItems();
	MapRenderer::GetInstance().Reset();

	//AudioManager::GetInstance().PlayAudio2D("Audio//BGM//BGM_Daniu.mp3", true);

	//SceneBase::InitHero<Kifellah>();
	//SceneBase::InitHero<Daniu>();
	SceneBase::InitHero<Seetwo>();
	SceneBase::InitCamera();
	SceneBase::InitEnemies();
	SceneBase::InitSawblades("Levels//Level1//SB.csv");
	
	backgroundTextures[BACKGROUND_REAR].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Rear", "Image//Cyborg_Shooter//Backgrounds//Background_Rear.tga");
	nextScene = "Level 2";

}