#ifndef TILE_INDEX_H
#define TILE_INDEX_H

enum TILE_INDEX {
	//Terrain
	TILE_NOTHING = 0, // 0
	TILE_WALL_1 = 1, // 1
	TILE_WALL_2 = 2, // 2
	TILE_WALL_3 = 3, // 3
	TILE_WALL_4 = 4, //4

	//Items
	TILE_COIN = 0x10, // 16
	TILE_ACID = 0x20, // 32
	TILE_SPIKE = 0x30, // 48
	TILE_DOOR_OPEN = 0x40, // 64
	TILE_DOOR_CLOSE = 0x50, // 80
	TILE_TRAMPOLINE = 0x60, // 96

	// Character Spawns
	TILE_CHARACTER_SPAWN = 0x100, // 256

	// Enemy Spawn
	TILE_TURRET = 0x1000, // 4096
	TILE_GUNNER = 0x2000, // 8192
	TILE_BRAWLER = 0x3000, // 12288

	// Number of Enemies
	TILE_NUM_ENEMY = 0x10000, //65536

	// Sawblade Index
	TILE_SAWBLADE_INDEX = 0x100000, // 1048576

	// Sawblade Node
	TILE_SAWBLADE_NODE = 0x1000000, // 16777216
};

#endif