#include "SceneBase.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "MapRenderer.h"
#include "GameManager.h"

#include <fstream>
#include <sstream>
#include <iostream>

//Enemy Types
#include "Turret.h"
#include "Brawler.h"
#include "Gunner.h"

const double SceneBase::minFPS = 30.0;

//Constructor(s) & Destructor
SceneBase::SceneBase(const string& name) : Scene(name) {
	
	font = MeshBuilder::GetInstance().GenerateText("Consolas", 16, 16);
	fontTexture.textureArray[0] = TextureManager::GetInstance().AddTexture("Consolas", "Image//Fonts//Consolas.tga");
	backgroundTextures[BACKGROUND_PAUSE].textureArray[0] = TextureManager::GetInstance().AddTexture("Pause Background", "Image//Cyborg_Shooter//Backgrounds//Background_Rear.tga");

	hero = nullptr;
	camera = nullptr;
	currentState = STATE::PLAY;
	completedObjective = false;

	//Debouncing
	for (unsigned int i = 0; i < static_cast<unsigned int>(NUM_KEYS); ++i) {
		isKeyDown[i] = true;
	}

}

SceneBase::~SceneBase() {
}

//Initialisation
void SceneBase::Init() {

	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	InitShader();
	background = MeshBuilder::GetInstance().GenerateQuad("Scene Background", Color(0.4f, 0.7f, 0.1f));
	currentState = STATE::PLAY;

}

void SceneBase::InitShader() {

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader<SHADERS::SHADOW>();
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);
	
}

void SceneBase::InitObjective() {

	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			unsigned int item = GetTileType(TILE_TYPE::ITEMS, tileSystem.TileValue(row, col));
			if (item == TILE_OBJECTIVE) {
				objective.row = row;
				objective.column = col;
				break;
			}
		}
	}

}

void SceneBase::InitCamera() {

	camera = new Camera2D(name);
	camera->SetFollowTarget(*hero);
	camera->SetTileSystem(tileSystem);

}

void SceneBase::InitEnemies() {

	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			unsigned int enemyType = GetTileType(TILE_TYPE::SPAWNS, tileSystem.TileValue(row, col));
			if (enemyType == 0) {
				continue;
			}

			Enemy* enemy = nullptr;
			switch (enemyType) {
				case (TILE_SPAWN_TURRET): {
					enemy = new Turret(name);
				}
				break;
				case (TILE_SPAWN_BRAWLER): {
					enemy = new Brawler(name);
				}
				break;
				case (TILE_SPAWN_GUNNER): {
					enemy = new Gunner(name);
				}
				break;
			}
			if (enemy != nullptr) {
				enemy->SetTarget(hero);
				enemy->SetTileSystem(tileSystem);
				enemy->SetAllies(&enemies);
				enemy->SetSpawnpoint(row, col);
				enemy->position.Set(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());
				enemies.insert(enemy);
			}
		}
	}

}

bool SceneBase::InitSawblades(const string& filePath) {

	//Open the file.
	ifstream file(filePath.c_str());
	//If file is successfully opened.
	if (!file.is_open()) {
		cout << "Error: Cannot open file " << filePath << "." << endl;
		return false;
	}
	
	enum SAWBLADE_ATRIB {
		INDEX,
		NODE_INDEX,
		ROW,
		COL,
	};

	string currentLine = "";
	while (getline(file, currentLine)) {
		if (currentLine == "") {
			continue;
		}

		SAWBLADE_ATRIB attribute = INDEX;
		istringstream iss(currentLine);
		string token;
		
		unsigned int index = 0;
		unsigned int nodeIndex = 0;
		Vector2 nodePosition;
		while (getline(iss, token, ',')) {
			unsigned int number = atoi(token.c_str());
			switch (attribute) {
				case INDEX:
					index = number;
				break;
				case NODE_INDEX:
					nodeIndex = number;
				break;
				case ROW:
					nodePosition.y = tileSystem.GetTileSize() * number;
				break;
				case COL:
					nodePosition.x = tileSystem.GetTileSize() * number;
					map<unsigned int, Sawblade*>::iterator iter = sawblades.find(index);
					if (iter != sawblades.end()) {
						iter->second->AddNode(nodeIndex, nodePosition);
					} else {
						Sawblade* sawblade = new Sawblade(name);
						sawblade->AddNode(nodeIndex, nodePosition);
						sawblade->target = hero;
						sawblades.insert(std::pair<unsigned int, Sawblade*>(index, sawblade));
					}
					attribute = INDEX;
				break;
			}
			attribute = static_cast<SAWBLADE_ATRIB>(attribute + 1);
		}
	}

	cout << "Successfully loaded " << filePath << "." << endl;
	return true;

}

void SceneBase::InitBackgrounds() {
}

//Update
void SceneBase::Update(const double& deltaTime) {

	double frameTime = deltaTime;
	if (frameTime > 1.0 / minFPS) {
		cout << "Lag Spike Detected." << endl;
		frameTime = 1.0 / minFPS;
	}

	if (!InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT]) {
		isKeyDown[static_cast<unsigned int>(KEYS::SELECT)] = false;
	}
	if (!InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACK]) {
		isKeyDown[static_cast<unsigned int>(KEYS::BACK)] = false;
	}

	switch (currentState) {
		case STATE::PLAY:
			Play(frameTime);
			break;
		case STATE::PAUSE:
			Pause(frameTime);
			break;
		case STATE::END:
			End(frameTime);
			break;
	}

}

void SceneBase::Play(const double& deltaTime) {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACK] && !isKeyDown[KEYS::BACK]) {
		isKeyDown[KEYS::BACK] = true;
		currentState = STATE::PAUSE;
	}

	//Update the game
	EntityManager::GetInstance().Update(name, deltaTime);
	MapRenderer::GetInstance().Update(deltaTime);
	
	unsigned int tileValue = tileSystem.TileValue(objective.row, objective.column);
	unsigned int item = GetTileType(TILE_TYPE::ITEMS, tileValue);
	if (completedObjective == false && (item != TILE_OBJECTIVE || CheckItemToggle(tileValue) == false)) {
		completedObjective = true;
		OpenDoors();
	}

	//Check if hero is at the door.
	if (hero->IsAtExit()) {
		currentState = STATE::END;
	}

	//Check if hero is dead and needs reseting.
	if (hero->GetLives() <= 0 || hero->isDead) {
		Reset();
	}

}

void SceneBase::Pause(const double& deltaTime) {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT] && !isKeyDown[KEYS::SELECT]) {
		isKeyDown[KEYS::SELECT] = true;
		currentState = STATE::PLAY;
	} else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACK] && !isKeyDown[KEYS::BACK]) {
		isKeyDown[KEYS::BACK] = true;
		//Quit();
		GoToNextLevel();
	}

}

void SceneBase::End(const double& deltaTime) {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT] && !isKeyDown[KEYS::SELECT]) {
		//Move on to next level.
		isKeyDown[KEYS::SELECT] = true;
		GoToNextLevel();
	} else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACK] && !isKeyDown[KEYS::BACK]) {
		//Restart the level
		isKeyDown[KEYS::BACK] = true;
		currentState = STATE::PLAY;
		Reset();
	}

}

void SceneBase::Quit() {

	SceneManager::GetInstance().RemoveScene(name);
	GameManager::GetInstance().GoToScene("Main Menu");	

}

void SceneBase::GoToNextLevel() {

	SceneManager::GetInstance().RemoveScene(name);
	GameManager::GetInstance().GoToScene(nextScene);

}

void SceneBase::OpenDoors() {

	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			unsigned int item = GetTileType(TILE_TYPE::ITEMS, tileSystem.TileValue(row, col));
			if (item == TILE_DOOR) {
				ToggleItem(true, tileSystem.TileValue(row, col));
			}
		}
	}

}

void SceneBase::CloseDoors() {

	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			unsigned int item = GetTileType(TILE_TYPE::ITEMS, tileSystem.TileValue(row, col));
			if (item == TILE_DOOR) {
				ToggleItem(false, tileSystem.TileValue(row, col));
			}
		}
	}

}

//Rendering
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

	if (currentState == STATE::PAUSE) {
		RenderPauseScreen();
	} else if (currentState == STATE::END) {
		RenderEndScreen();
	}

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

void SceneBase::RenderPauseScreen() {

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_PAUSE],false);
		RenderHelper::GetInstance().RenderText(*font, fontTexture, "Press ESC/[B] To Quit", Color(1, 1, 1));
		RenderHelper::GetInstance().RenderText(*font, fontTexture, "Press Enter/[A] To Resume", Color(1, 1, 1));
	modelStack.PopMatrix();

}

void SceneBase::RenderEndScreen() {

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_PAUSE],false);
		RenderHelper::GetInstance().RenderText(*font, fontTexture, "Press ESC/[B] To Restart", Color(1, 1, 1));
		RenderHelper::GetInstance().RenderText(*font, fontTexture, "Press Enter/[A] To Continue", Color(1, 1, 1));
	modelStack.PopMatrix();

} 

//Reset
void SceneBase::Reset() {

	ResetItems();
	ResetHero();
	ResetEnemies();
	ResetSawblades();
	completedObjective = false;

}

void SceneBase::ResetItems() {

	for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
		for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
			unsigned int item = GetTileType(TILE_TYPE::ITEMS, tileSystem.TileValue(row, col));
			if (item == 0) {
				continue;
			}
			if (item == TILE_DOOR) {
				ToggleItem(false, tileSystem.TileValue(row, col));
			} else {
				ToggleItem(true, tileSystem.TileValue(row, col));
			}
		}
	}

}

void SceneBase::ResetHero() {

	hero->Reset();

}

void SceneBase::ResetEnemies() {

	for (set<Enemy*>::iterator enemyIter = enemies.begin(); enemyIter != enemies.end(); ++enemyIter) {
		(*enemyIter)->Reset();
	}

}

void SceneBase::ResetSawblades() {

	for (map<unsigned int, Sawblade*>::iterator sawbladeIter = sawblades.begin(); sawbladeIter != sawblades.end(); ++sawbladeIter) {
		sawbladeIter->second->Reset();
	}

}

//Exit
void SceneBase::Exit() {

	camera = nullptr;
	hero = nullptr;
	enemies.clear();
	sawblades.clear();
	tileSystem.Clear();
	EntityManager::GetInstance().DestroyScene(name);	

}