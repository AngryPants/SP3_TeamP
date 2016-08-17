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
	enum TEXTURE_TYPE {
		//Terrain
		TEX_WALL_1,
		TEX_WALL_2,
		TEX_WALL_3,
		TEX_WALL_4,

		//Items
		TEX_ACID,
		TEX_SPIKE,

		NUM_TEXTURE,
	};

	Mesh* mesh;
	Texture meshTextures[NUM_TEXTURE];

	enum ANIMATION_TYPE {
		//Items
		ANIM_COIN,
		ANIM_DOOR,
		ANIM_TRAMPOLINE,

		NUM_ANIMATION,
	};
	SpriteAnimation* sprite[NUM_ANIMATION];
	Animation animation[NUM_ANIMATION];
	Texture spriteTextures[NUM_ANIMATION];

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