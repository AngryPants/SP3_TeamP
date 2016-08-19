#ifndef MAP_RENDERER_H
#define MAP_RENDERER_H

#include "SingletonTemplate.h"
#include "TileSystem.h"
#include "SpriteAnimation.h"
#include "Texture.h"

class MapRenderer : public Singleton<MapRenderer> {

	friend class Singleton<MapRenderer>;

private:
	//Enum(s)
	enum MESH_TYPE {
		//Terrain
		MESH_WALL_1,
		MESH_WALL_2,
		MESH_WALL_3,
		
		//Items
		MESH_ACID,
		MESH_SPIKE,
		MESH_WRENCH,
		MESH_HERO_SPAWN,
		MESH_CHECKPOINT_UNSET,
		MESH_CHECKPOINT_SET,
		
		//SIGNS
		MESH_ARROW_LEFT,
		MESH_ARROW_RIGHT,
		MESH_ARROW_UP,
		MESH_ARROW_DOWN,
		MESH_WARNING,
		MESH_WARNING_SAWBLADE,
		MESH_WARNING_SPIKE,		
		MESH_ALERT_TRAMPOLINE,		
		MESH_ALERT_EXIT,

		NUM_MESH,
	};

	Mesh* mesh;
	Texture meshTextures[NUM_MESH];

	enum SPRITE_TYPE {
		SPRITE_COIN,
		SPRITE_DOOR,

		NUM_SPRITE,
	};
	SpriteAnimation* sprite[NUM_SPRITE];
	Animation animation[NUM_SPRITE];
	Texture spriteTextures[NUM_SPRITE];

	int startRow, endRow;
	int startColumn, endColumn;
	
	//Constructor & Destructor
	MapRenderer();
	virtual ~MapRenderer();

public:	
	void SetStartRow(const int& startRow);
	void SetEndRow(const int& endRow);

	void SetStartColumn(const int& startColumn);
	void SetEndColumn(const int& endColumn);

	void Render(TileSystem& tileSystem);

};

#endif