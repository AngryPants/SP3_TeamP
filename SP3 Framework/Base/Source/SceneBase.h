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

protected:
	enum BACKGROUND {
		BACKGROUND_REAR,
		BACKGROUND_MIDDLE,
		BACKGROUND_FRONT,

		NUM_BACKGROUND,
	};

	Mesh* background;
	Texture backgroundTextures[NUM_BACKGROUND];

	double minFPS;
	Camera2D* camera;
	Hero* hero;
	set<Enemy*> enemies;
	map<int, Sawblade*> sawblades;
	TileSystem tileSystem;

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
				if (GetTileInfo(TILE_INFO::ITEM, tileSystem.TileValue(row, col)) == TILE_HERO_SPAWN) {
					hero->position.Set(col * tileSystem.GetTileSize(), row * tileSystem.GetTileSize());
					hero->SetCheckpoint(row, col);
					break;
				}
			}
		}
	}

	virtual void InitCamera();
	virtual void InitEnemies();
	virtual void InitSawblades();
	virtual void InitBackgrounds();

	virtual void RenderBackground();

private:
	void InitShader();

public:
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