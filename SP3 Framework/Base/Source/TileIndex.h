#ifndef TILE_INDEX_H
#define TILE_INDEX_H

/*

Bits:		Representation:
0-7			Terrain (Can collide with but not interact with.)
8-11			Signs (Decoration)
12-19		Interactables (Things like Acid/Spikes)
20-26		Items (Things we can pick up)
27			Toggle Set/Unset Item
28-31		Spawns

*/

//Item Toggle = 0x08000000 (134217728)

enum TILE_INDEX {
	//Nothing
	TILE_NOTHING = 0,
	
	//Terrain (0x01 to 0xFF)
	TILE_WALL_1 = 0x0001, //1
	TILE_WALL_2 = 0x0002, //2
	TILE_WALL_3 = 0x0003, //3

	//Signs (0x0100 to 0x0F00)
	TILE_ARROW_LEFT = 0x0100, //256
	TILE_ARROW_RIGHT = 0x0200, //512
	TILE_ARROW_UP = 0x0300, //768
	TILE_ARROW_DOWN = 0x0400, //1024
	TILE_WARNING = 0x0500, //1280
	TILE_WARNING_SAWBLADE = 0x0600, //1536
	TILE_WARNING_SPIKE = 0x0700, //1792
	TILE_ALERT_TRAMPOLINE = 0x800, //2048
	TILE_ALERT_EXIT = 0x0900, //2304

	//Interactables (0x0000 1000 to 0x000F F000)
	TILE_SPIKE = 0x1000, //4096
	TILE_ACID = 0x2000, //8192
	TILE_BOOSTPAD_LEFT = 0x3000, //12288
	TILE_BOOSTPAD_RIGHT = 0x4000, //16384
	TILE_BOOSTPAD_DOWN = 0x5000, //20480
	TILE_BOOSTPAD_UP = 0x6000, //24576

	//Items (0x0020 0000 to 0x0400 0000)
	TILE_COIN = 0x00100000, //1048576
	TILE_HEALTH = 0x00200000, //2097152
	TILE_CHECKPOINT = 0x00300000, //3145728
	TILE_DOOR = 0x00400000, //4194304
	TILE_OBJECTIVE = 0x00500000, //5242880

	//Spawns (0x1000 0000 to 0xF000 0000)
	TILE_SPAWN_HERO = 0x10000000, //268435456
	TILE_SPAWN_TURRET = 0x20000000, //536870912
	TILE_SPAWN_BRAWLER = 0x30000000, //805306368
	TILE_SPAWN_GUNNER = 0x40000000, //1073741824

};

enum class TILE_TYPE {
	TERRAIN,
	SIGNS,
	INTERACTABLES,
	ITEMS,
	ITEM_TOGGLE,
	SPAWNS,
};

unsigned int GetTileType(TILE_TYPE type, const unsigned int& tileValue);
unsigned int& ToggleItem(bool set, unsigned int& tileValue);
bool CheckItemToggle(const unsigned int& tileValue);

#endif