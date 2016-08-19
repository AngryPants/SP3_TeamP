#ifndef TILE_INDEX_H
#define TILE_INDEX_H

enum TILE_INDEX {
	TILE_NOTHING = 0, // 0
	//Terrain
	TILE_WALL_1 = 1, // 1
	TILE_WALL_2 = 2, // 2
	TILE_WALL_3 = 3, // 3

	//Items
	TILE_COIN = 0x10, // 16
	TILE_ACID = 0x20, // 32
	TILE_SPIKE = 0x30, // 48
	TILE_HERO_SPAWN = 0x40, //64
	TILE_CHECKPOINT_UNSET = 0x50, //80
	TILE_CHECKPOINT_SET = 0x50, //80
	TILE_DOOR_OPEN = 0x60, // 96
	TILE_DOOR_CLOSE = 0x70, // 112
	TILE_TRAMPOLINE = 0x80, // 128	
	TILE_WRENCH = 0x90, //144

	// Signs
	TILE_ARROW_LEFT = 0x100, // 256
	TILE_ARROW_RIGHT = 0x200, // 512
	TILE_ARROW_UP = 0x300, // 768
	TILE_ARROW_DOWN = 0x400, // 1024
	TILE_WARNING = 0x500, //1280
	TILE_WARNING_SAWBLADE = 0x600, //1536
	TILE_WARNING_SPIKE = 0x700, //1792
	TILE_ALERT_TRAMPOLINE = 0x800, //2048
	TILE_ALERT_EXIT = 0x900, //2304

	// Enemy Spawn
	TILE_TURRET_SPAWN = 0x1000, // 4096
	TILE_GUNNER_SPAWN = 0x2000, // 8192
	TILE_BRAWLER_SPAWN = 0x3000, // 12288

	// Number of Enemies
	TILE_NUM_ENEMIES = 0x10000, //65536

	// Sawblade Index
	TILE_SAWBLADE_INDEX = 0x100000, // 1048576

	// Sawblade Node
	TILE_SAWBLADE_NODE = 0x1000000, // 16777216

	// Body Parts
	TILE_HEAD = 0x10000000, // 268435456
	TILE_BODY = 0x20000000, // 536870912
	TILE_HAND = 0x30000000, // 805306368
	TILE_LEG = 0x40000000, //1073741824
};

//The different information store inside the tiles
enum class TILE_INFO {
	TERRAIN,
	ITEM,
	SIGN,
	ENEMY_SPAWN,
	NUM_ENEMIES,
	SAWBLADE_INDEX,
	SAWBLADE_NODE,
	BODY_PARTS,
};

//Get the info value of a certain tile.
unsigned int GetTileInfo(TILE_INFO infoType, const unsigned int& tileValue);
//Clear the value of the tile of a certain type.
void ClearTileValue(TILE_INFO type, unsigned int& tileValue);

#endif