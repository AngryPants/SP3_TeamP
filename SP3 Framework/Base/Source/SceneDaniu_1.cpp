#include "SceneDaniu_1.h"
#include "EntityManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "MapRenderer.h"
#include "Kifellah.h"

SceneDaniu_1::SceneDaniu_1() : SceneBase ("Daniu Level 1") {
}

SceneDaniu_1::~SceneDaniu_1() {
}

void SceneDaniu_1::Init() {

	SceneBase::Init();

	tileSystem.LoadFile("Levels//Daniu//Daniu_Level_1.csv");

	InitHero();
	InitCamera();
	InitEnemies();
	InitSawblades();

}

void SceneDaniu_1::InitHero() {

	hero = new Kifellah();
	hero->SetTileSystem(tileSystem);
	EntityManager::GetInstance().AddEntity(name, *hero);

	//Spawn the player.
	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			if (GetTileInfo(TILE_INFO::ITEM, tileSystem.TileValue(row, col)) == TILE_HERO_SPAWN) {
				hero->position.Set(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());
			}
		}
	}

}

void SceneDaniu_1::InitCamera() {

	camera.SetFollowTarget(*hero);
	camera.SetTileSystem(tileSystem);
	EntityManager::GetInstance().AddEntity(name, camera);

}

void SceneDaniu_1::InitEnemies() {
}

void SceneDaniu_1::InitSawblades() {

}

void SceneDaniu_1::Update(const double& deltaTime) {

	//cout << "FPS: " << std::to_string(1.0 / deltaTime) << endl;

	double frameTime = deltaTime;
	if (frameTime > 1.0 / minFPS) {
		cout << "Lag Spike Detected." << endl;
		frameTime = 1.0 / minFPS;
	}

	EntityManager::GetInstance().Update(name, frameTime);

	AudioManager::GetInstance().Update();

}

void SceneDaniu_1::Render() {

	GraphicsManager::GetInstance().Update();
	GraphicsManager::GetInstance().SetToCameraView(camera);

	EntityManager::GetInstance().Render(this->name);
	EntityManager::GetInstance().RenderUI(this->name);

	MapRenderer::GetInstance().Render(tileSystem);

}

void SceneDaniu_1::Exit() {

	EntityManager::GetInstance().ClearScene(name);
	delete hero;
	hero = nullptr;

}