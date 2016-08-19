#ifndef TILE_H
#define TILE_H

#include "TileIndex.h"
#include <exception>

using std::exception;

class Tile
{
public:
	//Variable(s)
	unsigned int tileValue;

	//Constructor(s) & Destructor
	Tile() {
		tileValue = 0;
	}
	virtual ~Tile() {}

	//Enum(s)
	enum class TILE_TYPE
	{
		TERRAIN,
		ITEM,
		SIGN,
		ENEMY_SPAWN,
		NUM_ENEMIES,
		SAWBLADE_INDEX,
		SAWBLADE_NODE,
		BODY_PARTS,
	};

	//Function(s)
	//Get the value of the tile of a certain type.
	unsigned int GetTileValue(TILE_TYPE type) const {
		return (0x000F << (4 * static_cast<unsigned int>(type))) & tileValue;
	}

	//Clear the value of the tile of a certain type.
	void ClearTileValue(TILE_TYPE type) {
		tileValue ^= (tileValue & (0x000F << (4 * static_cast<unsigned int>(type))));
	}

};

#endif