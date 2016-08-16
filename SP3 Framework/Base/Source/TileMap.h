#ifndef MAP_2D_H
#define MAP_2D_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class TileMap {

private:
	int numRows, numColumns; //Number of tiles in the map.
	
	float tileSize;
	float leftBorder; //Left Most Of Our Map
	float rightBorder; //Right Most Of Our Map
	float topBorder; //Top Most Of Our Map
	float bottomBorder; //Bottom Most Of Our Map

	void UpdateBorders();

public:
	vector<vector<int> > map;

	//Constructor(s) & Destructor
	TileMap(void);
	~TileMap(void);

	bool LoadFile(const string& mapName);
	int GetNumRows() const;
	int GetNumColumns() const;
	void SetTileSize(const float& tileSize);
	float GetTileSize() const;
	int GetTile(const float& xPosition);

	float GetLeftBorder() const;
	float GetRightBorder() const;
	float GetTopBorder() const;
	float GetBottomBorder() const;

};

#endif