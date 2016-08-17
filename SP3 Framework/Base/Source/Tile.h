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
		HERO_SPAWN,
		ENEMY_SPAWN,
		NUM_ENEMIES,
		SAWBLADE_INDEX,
		SAWBLADE_NODE,
	};

	//Function(s)
	template <TILE_TYPE type>
	unsigned int GetTileValue() {
		return (0x000F << (4 * static_cast<unsigned int>(type))) & tileValue;
	}

};

#endif