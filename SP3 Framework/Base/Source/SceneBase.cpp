#include "SceneBase.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "MapRenderer.h"

//Enemy Types
#include "Turret.h"
#include "Brawler.h"
#include "Gunner.h"

SceneBase::SceneBase(const string& name) : Scene(name) {
	hero = nullptr;
	camera = nullptr;
	background = MeshBuilder::GetInstance().GenerateQuad("Scene Background", Color(0.4f, 0.7f, 0.1f));
}

SceneBase::~SceneBase() {
}

void SceneBase::Init() {

	minFPS = 30.0;

	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	InitShader();

}

void SceneBase::InitShader() {

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader<SHADERS::SHADOW>();
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);
	
}

void SceneBase::InitCamera() {

	camera = new Camera2D(name);
	camera->SetFollowTarget(*hero);
	camera->SetTileSystem(tileSystem);

}

void SceneBase::InitEnemies() {

	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			//Spawn Enemies
			unsigned int enemyType = GetTileInfo(TILE_INFO::ENEMY_TYPE, tileSystem.TileValue(row, col));
			unsigned int numEnemies = GetTileInfo(TILE_INFO::NUM_ENEMIES, tileSystem.TileValue(row, col));
			if (enemyType == 0) {
				continue;
			}
			for (unsigned int i = 0; i <= numEnemies; ++i) {
				Enemy* enemy = nullptr;
				switch (enemyType) {
					case (TILE_TURRET_SPAWN): {
						enemy = new Turret(name);
					}
					break;
					case (TILE_BRAWLER_SPAWN): {
						enemy = new Brawler(name);
					}
					break;
					case (TILE_GUNNER_SPAWN): {
						enemy = new Gunner(name);
					}
					break;
				}
				if (enemy != nullptr) {
					enemy->SetTarget(hero);
					enemy->SetTileSystem(tileSystem);
					enemy->SetAllies(&enemies);
					enemy->position.Set(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());
					enemies.insert(enemy);
				}
			}
		}
	}

}

void SceneBase::InitSawblades() {

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

void SceneBase::InitBackgrounds() {
}

void SceneBase::Update(const double& deltaTime) {

	double frameTime = deltaTime;
	if (frameTime > 1.0 / minFPS) {
		cout << "Lag Spike Detected." << endl;
		frameTime = 1.0 / minFPS;
	}

	EntityManager::GetInstance().Update(name, frameTime);
	MapRenderer::GetInstance().Update(deltaTime);
	
}

void SceneBase::Render() {

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

void SceneBase::RenderBackground() {

	Vector3 backgroundPosition = camera->GetPosition();

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(backgroundPosition.x, backgroundPosition.y, -30);
		modelStack.Scale(camera->GetOrthoWidth() * 2.0f, camera->GetOrthoSize() * 2.0f, 1);
		background->SetTextureOffset(0, 0);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_REAR], false);
	modelStack.PopMatrix();
	
}

void SceneBase::Exit() {

	//GameManager::GetInstance().ClearScene(name);
	EntityManager::GetInstance().DestroyScene(name);	

}