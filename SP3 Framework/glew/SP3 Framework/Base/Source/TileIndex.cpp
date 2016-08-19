#include "TileIndex.h"

//Get the info value of a certain tile.
unsigned int GetTileInfo(TILE_INFO infoType, const unsigned int& tileValue) {
	return (0x000F << (4 * static_cast<unsigned int>(infoType))) & tileValue;
}

//Clear the value of the tile of a certain type.
void ClearTileValue(TILE_INFO type, unsigned int& tileValue) {
	tileValue ^= (tileValue & (0x000F << (4 * static_cast<unsigned int>(type))));
}