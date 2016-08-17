#ifndef TILE_SYSTEM_H
#define TILE_SYSTEM_H

#include "EntityBase.h"
#include "Tile.h"
#include "SpriteAnimation.h"
#include "Mesh.h"
#include "Texture.h"

typedef vector<vector<Tile>> TileMap;

class TileSystem : public EntityBase {

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
		//Items
		SPRITE_COIN,
		SPRITE_DOOR,
		SPRITE_TRAMPOLINE,

		NUM_SPRITE,
	};
	SpriteAnimation* sprite[NUM_SPRITE];
	Animation animation[NUM_SPRITE];
	Texture spriteTextures[NUM_SPRITE];

	int numRows, numColumns; //Number of tiles in the map.
	
	float tileSize; //Tile Size

	float leftBorder; //Left Most Of Our Map
	float rightBorder; //Right Most Of Our Map
	float topBorder; //Top Most Of Our Map
	float bottomBorder; //Bottom Most Of Our Map
	void UpdateBorders();

	int renderStartTileRow;
	int renderEndTileRow;
	int renderStartTileColumn;
	int renderEndTileColumn;

public:
	//Variable(s)
	TileMap tiles;

	//Constructor
	TileSystem();
	virtual ~TileSystem();

	//Virtual Function(s)
	void Update(const double& deltaTime);
	void Render();
	void RenderUI();

	//Function(s)
	bool LoadFile(const string& filePath);

	//Tile Size
	void SetTileSize(const float& tileSize);
	float GetTileSize() const;

	//Map Borders
	float GetLeftBorder() const;
	float GetRightBorder() const;
	float GetTopBorder() const;
	float GetBottomBorder() const;

	//Tile Position
	int GetTile(const float& position) const;

	//Tile Rendering
	void SetRenderTilesRow(const int& start, const int& end);
	void SetRenderTilesColumn(const int& start, const int& end);

};

#endif