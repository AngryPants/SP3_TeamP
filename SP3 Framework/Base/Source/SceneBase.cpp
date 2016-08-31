#include "SceneBase.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "EntityManager.h"
#include "MapRenderer.h"
#include "GameManager.h"
#include "GameData.h"

#include <fstream>
#include <sstream>
#include <iostream>

//Enemy Types
#include "Turret.h"
#include "Brawler.h"
#include "Gunner.h"

//Hero Types
#include "Kifellah.h"
#include "Daniu.h"
#include "Seetwo.h"

const double SceneBase::minFPS = 30.0;

//Constructor(s) & Destructor
SceneBase::SceneBase(const string& name) : Scene(name) {
	
	//Mesh & Textures
	InitBackgrounds();

	//Character Selection
	heroCard = MeshBuilder::GetInstance().GenerateQuad("Hero Card");
	cardTexture[KIFELLAH].textureArray[0] = TextureManager::GetInstance().AddTexture("Hero Card Kifellah", "Image//Cyborg_Shooter//Characters//Hero_Cards//Kifellah.tga");
	cardTexture[DANIU].textureArray[0] = TextureManager::GetInstance().AddTexture("Hero Card Daniu", "Image//Cyborg_Shooter//Characters//Hero_Cards//Daniu.tga");
	cardTexture[SEETWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Hero Card Seetwo", "Image//Cyborg_Shooter//Characters//Hero_Cards//Seetwo.tga");
	lockedCardTexture.textureArray[0] = TextureManager::GetInstance().AddTexture("Hero Card Lock", "Image//Cyborg_Shooter//Characters//Hero_Cards//Lock.tga");
	
	//unlockedCharacters[KIFELLAH] = GameData::GetInstance().IsCharacterUnlocked("Kifellah");
	//Check for unlocked characters
	unlockedCharacters[KIFELLAH] = true;
	unlockedCharacters[DANIU] = GameData::GetInstance().IsCharacterUnlocked("Daniu");
	unlockedCharacters[SEETWO] = GameData::GetInstance().IsCharacterUnlocked("Seetwo");

	hero = nullptr;
	camera = nullptr;
	//currentState = STATE::PLAY;
	currentState = STATE::CHARACTER_SELECT;
	completedObjective = false;
	selectedHero = HERO::KIFELLAH;

	//Debouncing
	for (unsigned int i = 0; i < static_cast<unsigned int>(NUM_KEYS); ++i) {
		isKeyDown[i] = true;
	}

	tileMapFile = "";
	sawbladesFile = "";
	bgmFile = "";
	unlockCharacter = "Kifellah";
	unlockPart = PART::HEAD;

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
	currentState = STATE::CHARACTER_SELECT;
	GameData::GetInstance().SetCurrentLevel(name);

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

	backgroundTextures[BACKGROUND_PAUSE].textureArray[0] = TextureManager::GetInstance().AddTexture("Pause Background", "Image//Cyborg_Shooter//Backgrounds//Background_Pause.tga");
	backgroundTextures[BACKGROUND_REAR].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Rear", "Image//Cyborg_Shooter//Backgrounds//Background_Rear.tga");
	backgroundTextures[BACKGROUND_MIDDLE].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Middle", "Image//Cyborg_Shooter//Backgrounds//Background_Middle.tga");
	backgroundTextures[BACKGROUND_FRONT].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Front", "Image//Cyborg_Shooter//Backgrounds//Background_Front.tga");

}

//Update
void SceneBase::Update(const double& deltaTime) {
	
	double frameTime = deltaTime;
	if (frameTime > 1.0 / minFPS) {
		cout << "Lag Spike Detected." << endl;
		frameTime = 1.0 / minFPS;
	}
	//cout << "Frame Rate: " << to_string(frameTime) << endl;

	if (!InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT]) {
		isKeyDown[static_cast<unsigned int>(KEYS::SELECT)] = false;
	}
	if (!InputManager::GetInstance().GetInputInfo().keyDown[INPUT_BACK]) {
		isKeyDown[static_cast<unsigned int>(KEYS::BACK)] = false;
	}
	if (!InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_LEFT]) {
		isKeyDown[static_cast<unsigned int>(KEYS::MENU_LEFT)] = false;
	}
	if (!InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_RIGHT]) {
		isKeyDown[static_cast<unsigned int>(KEYS::MENU_RIGHT)] = false;
	}

	switch (currentState) {
		case STATE::CHARACTER_SELECT:
			CharacterSelection(frameTime);
			break;
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

void SceneBase::CharacterSelection(const double& deltaTime) {

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_LEFT] && !isKeyDown[MENU_LEFT]) {
		isKeyDown[MENU_LEFT] = true;
		if (selectedHero > 0) {
			selectedHero = static_cast<HERO>(selectedHero - 1);
		} else {
			selectedHero = static_cast<HERO>(NUM_HERO - 1);
		}
	} else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_RIGHT] && !isKeyDown[MENU_RIGHT]) {
		isKeyDown[MENU_RIGHT] = true;
		selectedHero = static_cast<HERO>(static_cast<unsigned int>(selectedHero + 1) % NUM_HERO);
	}
	
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT] && !isKeyDown[SELECT]) {
		isKeyDown[SELECT] = true;
		if (unlockedCharacters[selectedHero]) {
			currentState = STATE::PLAY;
			StartScene();
			//Play nice sound.
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Good_Buzzer.mp3", false);
		} else {
			//Play bad sound.
			AudioManager::GetInstance().PlayAudio2D("Audio//Sound_Effects//Bad_Buzzer.mp3", false);
		}
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
	
	unsigned int tileValue = 0;
	if (objective.row >= 0 && objective.row < tileSystem.GetNumRows()) {
		if (objective.column >= 0 && objective.column < tileSystem.GetNumColumns()) {
			tileValue = tileSystem.TileValue(objective.row, objective.column);
		}
	}
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
		Quit();
		//GoToNextLevel();
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
	if (!GameManager::GetInstance().GoToScene("Main_Menu")) {
		currentState = STATE::PLAY;
	}

}

void SceneBase::GoToNextLevel() {

	//Unlock/save our stuff
	switch (unlockPart) {
		case PART::HEAD:
			GameData::GetInstance().UnlockHead(unlockCharacter);
		break;
		case PART::BODY:
			GameData::GetInstance().UnlockBody(unlockCharacter);
		break;
		case PART::ARMS:
			GameData::GetInstance().UnlockArms(unlockCharacter);
		break;
		case PART::LEGS:
			GameData::GetInstance().UnlockLegs(unlockCharacter);
		break;
	}
	GameData::GetInstance().AddHighScore(name, hero->GetScore());
	GameData::GetInstance().SetCurrentLevel(nextScene);
	GameData::GetInstance().SaveGameData("SaveFile//DataOne.txt", "SaveFile//Highscore.txt");
	
	SceneManager::GetInstance().RemoveScene(name);
	if (!GameManager::GetInstance().GoToScene(nextScene)) {
		currentState = STATE::PLAY;
	}

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
	background->SetTextureOffset(0, 0);

	if (currentState != STATE::CHARACTER_SELECT) {
		GraphicsManager::GetInstance().SetToCameraView(*camera);
		GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();
		RenderBackground();
		MapRenderer::GetInstance().Render(tileSystem);
		EntityManager::GetInstance().Render(this->name);
	}

	GraphicsManager::GetInstance().SetToHUD(-50, 50, -50, 50, -50, 50);
	GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::DEPTH_TEST>();
	EntityManager::GetInstance().RenderUI(this->name);

	if (currentState == STATE::CHARACTER_SELECT) {
		RenderCharacterSelect();
	} else if (currentState == STATE::PAUSE) {
		RenderPauseScreen();
	} else if (currentState == STATE::END) {
		RenderEndScreen();
	}

}

void SceneBase::RenderCharacterSelect() {

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Scale(100, 100, 1);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_REAR], false);
		modelStack.Translate(0, 0, 1);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_MIDDLE], false);
		modelStack.Translate(0, 0, 1);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(-30.0f, 0, 0);
		if (selectedHero == KIFELLAH) {
			modelStack.Scale(30, 30, 1);
		} else {
			modelStack.Scale(20, 20, 1);
		}
		RenderHelper::GetInstance().RenderMesh(*heroCard, cardTexture[KIFELLAH]);
		if (unlockedCharacters[KIFELLAH] == false) {
			RenderHelper::GetInstance().RenderMesh(*heroCard, lockedCardTexture);
		}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		if (selectedHero == DANIU) {
			modelStack.Scale(30, 30, 1);
		} else {
			modelStack.Scale(20, 20, 1);
		}
		RenderHelper::GetInstance().RenderMesh(*heroCard, cardTexture[DANIU]);
		if (unlockedCharacters[DANIU] == false) {
			RenderHelper::GetInstance().RenderMesh(*heroCard, lockedCardTexture);
		}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
		modelStack.Translate(30.0f, 0, 0);
		if (selectedHero == SEETWO) {
			modelStack.Scale(30, 30, 1);
		} else {
			modelStack.Scale(20, 20, 1);
		}
		RenderHelper::GetInstance().RenderMesh(*heroCard, cardTexture[SEETWO]);
		if (unlockedCharacters[DANIU] == false) {
			RenderHelper::GetInstance().RenderMesh(*heroCard, lockedCardTexture);
		}
	modelStack.PopMatrix();

}

void SceneBase::RenderBackground() {

	Vector3 backgroundPosition = camera->GetPosition();

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(backgroundPosition.x, backgroundPosition.y, -30);
		modelStack.Scale(camera->GetOrthoWidth() * 2.0f, camera->GetOrthoSize() * 2.0f, 1);
		background->SetTextureOffset(0, 0);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_REAR], false);
		modelStack.Translate(0, 0, 1);
		background->SetTextureOffset(camera->GetPosition().x / camera->GetOrthoWidth() * 0.1f, 0);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_MIDDLE], false);
		modelStack.Translate(0, 0, 1);
		background->SetTextureOffset(camera->GetPosition().x / camera->GetOrthoWidth() * 0.2f, 0);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_FRONT], false);
	modelStack.PopMatrix();

}

void SceneBase::RenderPauseScreen() {

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Scale(100, 100, 1);
		background->SetTextureOffset(0, 0);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_PAUSE],false);
	modelStack.PopMatrix();

}

void SceneBase::RenderEndScreen() {

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
	modelStack.Scale(100, 100, 1);
	background->SetTextureOffset(0, 0);
	RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_PAUSE], false);
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
	AudioManager::GetInstance().ClearAudioList();
	selectedHero = HERO::KIFELLAH;

}

void SceneBase::StartScene() {

	tileSystem.LoadFile(tileMapFile);
	InitObjective();
	ResetItems();
	MapRenderer::GetInstance().Reset();		
	switch (selectedHero) {
		case DANIU:
			SceneBase::InitHero<Daniu>();
		break;
		case SEETWO:
			SceneBase::InitHero<Seetwo>();
		break;
		default:
			SceneBase::InitHero<Kifellah>();
	}
	
	InitCamera();
	InitEnemies();
	InitSawblades(sawbladesFile);

	AudioManager::GetInstance().PlayAudio2D(bgmFile, true, 0.1f);

}