#ifndef TILE_SYSTEM_H
#define TILE_SYSTEM_H

#include <vector>
#include <string>

using namespace std;

typedef vector<vector<unsigned int> > TileMap;

struct TileCoord {

public:
	//Variable(s)
	int row, column;

	//Constructor(s) & Destructor
	TileCoord(int row = 0, int column = 0) {
		Set(row, column);
	}
	TileCoord(const TileCoord& rhs) {
		Set(rhs.row, rhs.column);
	}
	~TileCoord() {}

	//Function(s)
	void Set(int row, int column) {
		this->row = row;
		this->column = column;
	}

	TileCoord operator+(const TileCoord& rhs) const {
		return TileCoord(this->row + rhs.row, this->column + rhs.column);
	}
	TileCoord operator-(const TileCoord& rhs) const {
		return TileCoord(this->row - rhs.row, this->column - rhs.column);
	}
	TileCoord operator*(const int& scalar) const {
		return TileCoord(this->row * scalar, this->column * scalar);
	}
	TileCoord& operator=(const TileCoord& rhs) {
		this->row = rhs.row;
		this->column = rhs.column;
		return *this;
	}
	TileCoord& operator+=(const TileCoord& rhs) {
		this->row += rhs.row;
		this->column += rhs.column;
		return *this;
	}
	TileCoord& operator-=(const TileCoord& rhs) {
		this->row -= rhs.row;
		this->column -= rhs.column;
		return *this;
	}
	TileCoord operator*=(const int& scalar) {
		this->row *= scalar;
		this->column *= scalar;
		return *this;
	}
	bool operator==(const TileCoord& rhs) {
		return this->row == rhs.row && this->column == rhs.column;
	}
	bool operator!=(const TileCoord& rhs) {
		return !(this->row == rhs.row && this->column == rhs.column);
	}

};

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