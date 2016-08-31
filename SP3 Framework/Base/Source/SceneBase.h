#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Camera2D.h"
#include "Hero.h"
#include "Enemy.h"
#include "TileIndex.h"
#include "TileSystem.h"
#include "Sawblade.h"
#include <map>

using std::map;

class SceneBase : public Scene {

private:
	//Initialisation
	void InitShader();

	//Minimum Frame Rate
	static const double minFPS;
	
	//State of the scene
	enum class STATE {
		CHARACTER_SELECT,
		PLAY,
		PAUSE,
		END,
	};

	STATE currentState;

	//Characters
	enum HERO {
		KIFELLAH,
		DANIU,
		SEETWO,
		NUM_HERO,
	};

	bool unlockedCharacters[NUM_HERO];
	HERO selectedHero;
	Mesh* heroCard;
	Texture cardTexture[NUM_HERO];
	Texture lockedCardTexture;

	//States
	void CharacterSelection(const double& deltaTime);
	void Play(const double& deltaTime);
	void Pause(const double& deltaTime);
	void End(const double& deltaTime);

	//Text
	Mesh* font;
	Texture fontTexture;

	//Backgrounds
	enum BACKGROUND {
		BACKGROUND_REAR,
		BACKGROUND_MIDDLE,
		BACKGROUND_FRONT,
		BACKGROUND_PAUSE,
		BACKGROUND_END,
		NUM_BACKGROUND,
	};
	Mesh* background;
	Texture backgroundTextures[NUM_BACKGROUND];

	//Camera
	Camera2D* camera;

	//Characters
	Hero* hero;
	set<Enemy*> enemies;

	//Others
	TileSystem tileSystem;
	TileCoord objective;
	bool completedObjective;
	map<unsigned int, Sawblade*> sawblades;	

	//Initialisation
	template <class Type>
	void InitHero() {
		if (is_base_of<Hero, Type>::value == false) {
			throw std::exception("Cannot InitHero with a class that is not a hero, dumbass!");
		}
		if (hero != nullptr) {
			hero->Destroy();
			hero = nullptr;
		}

		hero = new Type(name);
		hero->SetTileSystem(tileSystem);
		hero->SetEnemies(&enemies);
		
		//Spawn the player.
		for (int row = 0; row < tileSystem.GetNumRows(); ++row) {
			for (int col = 0; col < tileSystem.GetNumColumns(); ++col) {
				if (GetTileType(TILE_TYPE::SPAWNS, tileSystem.TileValue(row, col)) == TILE_SPAWN_HERO) {
					hero->position.Set(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());
					hero->SetSpawnpoint(row, col);
					hero->SetCheckpoint(row, col);
					break;
				}
			}
		}
	}
	void InitObjective();
	virtual void InitCamera();
	virtual void InitEnemies();
	virtual bool InitSawblades(const string& filePath);
	virtual void InitBackgrounds();
	void StartScene();

	//Rendering
	virtual void RenderCharacterSelect();
	virtual void RenderBackground();
	virtual void RenderPauseScreen();
	virtual void RenderEndScreen();

	//Reset
	virtual void Reset();
	virtual void ResetItems();
	virtual void ResetEnemies();
	virtual void ResetHero();
	virtual void ResetSawblades();

	//Minimum Frame Rate
	double GetMinimumFPS() const;

	//Scene Transition
	void OpenDoors();
	void CloseDoors();
	void Quit();
	void GoToNextLevel();

	//Debouncing
	enum KEYS {
		SELECT,
		BACK,
		PAUSE,
		MENU_LEFT,
		MENU_RIGHT,
		NUM_KEYS,
	};
	bool isKeyDown[static_cast<unsigned int>(NUM_KEYS)];

public:
	//Public Variable(s)
	string tileMapFile;
	string sawbladesFile;
	string nextScene;
	string bgmFile;
	string unlockCharacter;

	enum class PART {
		HEAD,
		BODY,
		ARMS,
		LEGS,
	};
	PART unlockPart;

	//Constructor(s) & Destructor
	SceneBase(const string& name);
	virtual ~SceneBase();

	//Virtual Function(s)
	virtual void Init();
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void Exit();

};

#endif