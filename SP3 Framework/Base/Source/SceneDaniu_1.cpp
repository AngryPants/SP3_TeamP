#include "SceneDaniu_1.h"
#include "EntityManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "MapRenderer.h"
#include "Kifellah.h"
#include "Daniu.h"
#include "Seetwo.h"
#include "TileIndex.h"

SceneDaniu_1::SceneDaniu_1() : SceneBase ("Daniu Level 1") {
}

SceneDaniu_1::~SceneDaniu_1() {
}

void SceneDaniu_1::Init() {

	SceneBase::Init();

	tileSystem.LoadFile("Level//Daniu//Daniu_Level_1.csv");
	MapRenderer::GetInstance().Reset();

	//AudioManager::GetInstance().PlayAudio2D("Audio//BGM//BGM_Daniu.mp3", true);

	SceneBase::InitHero<Kifellah>();
	SceneBase::InitHero<Daniu>();
	SceneBase::InitHero<Seetwo>();
	SceneBase::InitCamera();
	SceneBase::InitEnemies();
	SceneBase::InitSawblades();
	
	backgroundTextures[BACKGROUND_REAR].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Rear", "Image//Cyborg_Shooter//Backgrounds//Background_Rear.tga");

}

void SceneDaniu_1::Update(const double& deltaTime) {

	SceneBase::Update(deltaTime);

}

void SceneDaniu_1::Render() {

	SceneBase::Render();

}

void SceneDaniu_1::Exit() {

	SceneBase::Exit();

}