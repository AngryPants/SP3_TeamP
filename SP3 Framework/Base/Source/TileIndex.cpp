#include "TileIndex.h"
#include <iostream>

/*

Bits:		Representation:
0-7			Terrain (Can collide with but not interact with.)
8-11			Signs (Decoration)
12-19		Interactables (Things like Acid/Spikes)
20			Toggle Set/Unset Item
21-27		Items (Things we can pick up)
28-31		Spawns

*/

unsigned int GetTileType(TILE_TYPE type, const unsigned int& tileValue) {

	switch (type) {
		case TILE_TYPE::TERRAIN: {
			return tileValue & 0x00FF;
		}
		break;
		case TILE_TYPE::SIGNS: {
			return tileValue & 0x0F00;
		}
		break;
		case TILE_TYPE::INTERACTABLES: {
			return tileValue & 0x000FF000;
		}
		break;
		case TILE_TYPE::ITEMS: {
			return tileValue & 0x07F00000;
		}
		break;
		case TILE_TYPE::ITEM_TOGGLE: {
			return tileValue & 0x08000000;
		}
		break;
		case TILE_TYPE::SPAWNS: {
			return tileValue & 0xF0000000;
		}
		break;
		default:
			std::cout << "Unrecognised Tile Type!" << std::endl;
	}

}

unsigned int& ToggleItem(bool set, unsigned int& tileValue) {

	unsigned int itemToggle = 0x08000000;

	if (set) {
		tileValue |= itemToggle;
	} else {
		tileValue &= ~itemToggle;
	}

	return tileValue;

}

bool CheckItemToggle(const unsigned int& tileValue) {

	return (tileValue >> 27) & 1;

}