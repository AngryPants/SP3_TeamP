#ifndef TILE_SYSTEM_H
#define TILE_SYSTEM_H

#include <vector>
#include <string>

using namespace std;

typedef vector<vector<unsigned int> > TileMap;

class TileSystem {

private:
	//Variable(s)
	TileMap tileMap;
	int numRows, numColumns;
	float tileSize;

	//Boundaries
	float boundaryLeft;
	float boundaryRight;
	float boundaryBottom;
	float boundaryTop;	

	//Private Function(s)
	void UpdateBoundaries();

public:
	//Constructor(s) & Destructor
	TileSystem();
	virtual ~TileSystem();

	//Function(s)
	bool LoadFile(const string& filePath);
	int GetNumRows() const;
	int GetNumColumns() const;
	void SetTileSize(const float& tileSize);
	float GetTileSize() const;
	float GetWidth() const;
	float GetHeight() const;
	int GetTile(const float& position) const;
	float GetBoundaryLeft() const;
	float GetBoundaryRight() const;
	float GetBoundaryBottom() const;
	float GetBoundaryTop() const;

	//Editing Tiles
	unsigned int& TileValue(const int& row, const int& col);

};

#endif