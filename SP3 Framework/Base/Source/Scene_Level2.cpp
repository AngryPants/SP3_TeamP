#include "Scene_Level2.h"
#include "EntityManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "MapRenderer.h"
#include "Kifellah.h"
#include "Daniu.h"
#include "Seetwo.h"
#include "TileIndex.h"

Scene_Level2::Scene_Level2() : SceneBase("Level 2") {
}

Scene_Level2::~Scene_Level2() {
}

void Scene_Level2::Init() {

	SceneBase::Init();

	tileSystem.LoadFile("Levels//Level2//TM.csv");
	SceneBase::ResetItems();
	MapRenderer::GetInstance().Reset();

	//AudioManager::GetInstance().PlayAudio2D("Audio//BGM//BGM_Daniu.mp3", true);

	//SceneBase::InitHero<Kifellah>();
	//SceneBase::InitHero<Daniu>();
	SceneBase::InitHero<Seetwo>();
	SceneBase::InitCamera();
	SceneBase::InitEnemies();
	SceneBase::InitSawblades("Levels//Level2//SB.csv");
	
	backgroundTextures[BACKGROUND_REAR].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Rear", "Image//Cyborg_Shooter//Backgrounds//Background_Rear.tga");
	nextScene = "Level 1";

}