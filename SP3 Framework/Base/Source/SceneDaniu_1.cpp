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

	InitHero();
	InitCamera();
	InitEnemies();
	InitSawblades();

	AudioManager::GetInstance().PlayAudio2D("Audio//BGM//BGM_Daniu.mp3", true);
	MapRenderer::GetInstance().Reset();

}

void SceneDaniu_1::InitHero() {

	hero = new Seetwo(name);
	//hero = new Daniu(name);
	//hero = new Kifellah(name);
	hero->SetTileSystem(tileSystem);

	//Spawn the player.
	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			if (GetTileInfo(TILE_INFO::ITEM, tileSystem.TileValue(row, col)) == TILE_HERO_SPAWN) {
				hero->position.Set(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());
				hero->SetCheckpoint(row, col);
				break;
			}
		}
	}

}

void SceneDaniu_1::InitCamera() {

	camera = new Camera2D(name);
	camera->SetFollowTarget(*hero);
	camera->SetTileSystem(tileSystem);

}

void SceneDaniu_1::InitEnemies() {
}

void SceneDaniu_1::InitSawblades() {

	// Get the position of the nodes for sawblade's movement
	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			unsigned int sawbladeIndex = GetTileInfo(TILE_INFO::SAWBLADE_INDEX, tileSystem.TileValue(row, col));
			if (sawbladeIndex == 0)
				continue;

			unsigned int nodeIndex = GetTileInfo(TILE_INFO::SAWBLADE_NODE, tileSystem.TileValue(row, col));
			Vector2 nodePosition(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());

			std::map<int, Sawblade*>::iterator sawbladeIter = sawblades.find(sawbladeIndex);
			if (sawbladeIter == sawblades.end()) {
				Sawblade *sawBlade = new Sawblade(name);
				sawBlade->AddNode(nodeIndex, nodePosition);
				sawblades.insert(std::pair<int, Sawblade*>(sawbladeIndex, sawBlade));
				sawBlade->target = hero;
			} else {
				sawbladeIter->second->AddNode(nodeIndex, nodePosition);
			}			
		}
	}

}

void SceneDaniu_1::Update(const double& deltaTime) {

	//cout << "FPS: " << std::to_string(1.0 / deltaTime) << endl;

	double frameTime = deltaTime;
	if (frameTime > 1.0 / minFPS) {
		cout << "Lag Spike Detected." << endl;
		frameTime = 1.0 / minFPS;
	}

	//Hero* testHero = new Kifellah(name);
	//testHero->Destroy();

	AudioManager::GetInstance().Update();
	EntityManager::GetInstance().Update(name, frameTime);
	MapRenderer::GetInstance().Update(deltaTime);

}

void SceneDaniu_1::Render() {

	GraphicsManager::GetInstance().Update();
	GraphicsManager::GetInstance().SetToCameraView(*camera);
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();
	RenderBackground();
	MapRenderer::GetInstance().Render(tileSystem);
	EntityManager::GetInstance().Render(this->name);

	GraphicsManager::GetInstance().SetToHUD(-50, 50, -50, 50, -50, 50);
	GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::DEPTH_TEST>();
	EntityManager::GetInstance().RenderUI(this->name);

}

void SceneDaniu_1::Exit() {

	SceneBase::Exit();

}