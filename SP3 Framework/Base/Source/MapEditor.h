#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include "TileSystem.h"

class MapEditor : EntityBase {

private:
	//Variable(s)
	bool CheckFileExist(const string& filePath);
	string filePath;
	TileSystem* tileSystem;
	int tileX, tileY; //The current tile we are selecting

	void DeleteTile();

public:
	MapEditor();
	virtual ~MapEditor();

	void SetTileSystem(TileSystem& tileSystem);
	void RemoveTileSystem();

	//Virtual Function(s)
	virtual void Update(const double& deltaTime);
	virtual void Render();
	virtual void RenderUI();

};

#endif