#include "TileSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Constructor(s) & Destructor
TileSystem::TileSystem() {

	numRows = 0;
	numColumns = 0;
	tileSize = 1.0f;

}

TileSystem::~TileSystem() {
}

//Private Function(s)
void TileSystem::UpdateBoundaries() {

	if (numColumns == 0 || numRows == 0) {
		boundaryLeft = 0;
		boundaryRight = 0;
		boundaryBottom = 0;
		boundaryTop = 0;		
	} else {
		boundaryLeft = -0.5f * tileSize;
		boundaryRight = boundaryLeft + numColumns * tileSize;
		boundaryBottom = -0.5f * tileSize;
		boundaryTop = boundaryBottom + numRows * tileSize;		
	}

}

bool TileSystem::LoadFile(const string& filePath) {

	//Open the file.
	ifstream file(filePath.c_str());
	//If file is successfully opened.
	if (!file.is_open()) {
		cout << "Error: Cannot open file " << filePath << "." << endl;
		return false;
	}

	//Empty our current tiles.
	tileMap.clear();
	numRows = 0;
	numColumns = 0;

	string currentLine = "";
	while(getline(file, currentLine)) {
		// If this line is a comment line, or an empty line, then ignore it.
		if (currentLine == "") {
			continue;
		}
		//currentLine.find("//*") != NULL
		//A new row of tiles.
		++numRows;
		vector<unsigned int> currentRow;
		currentRow.resize(numColumns, 0); //Make it the size of the largest row.

		//Create a istringstream object with currentLine as it's content.
		istringstream iss(currentLine);
		string token;

		int columnCounter = 0;
		//Each time this loop is done, iss is shortened and token is lengthened.
		while(getline(iss, token, ',')) {
			// Count the number of columns
			++columnCounter;
			//Is the current column we are in right now larger than the size of our current row?
			if (columnCounter > currentRow.size()) {
				numColumns = columnCounter;
				currentRow.resize(numColumns, 0);
				for (vector<vector<unsigned int> >::iterator iter = tileMap.begin(); iter != tileMap.end(); ++iter) {
					(*iter).resize(numColumns, 0);
				}
			}
			currentRow[columnCounter - 1] = atoi(token.c_str());
		}
		//Add the current row to our tiles.
		tileMap.insert(tileMap.begin(), currentRow);

	}

	//Close the file after we're done.
	file.close();
	
	UpdateBoundaries();

	return true;

}

int TileSystem::GetNumColumns() const {

	return numColumns;

}

int TileSystem::GetNumRows() const {

	return numRows;

}

void TileSystem::SetTileSize(const float& tileSize) {

	if (tileSize < 0) {
		this->tileSize = 0.0f;
	} else {
		this->tileSize - tileSize;
	}

	UpdateBoundaries();

}

float TileSystem::GetTileSize() const {

	return this->tileSize;

}

float TileSystem::GetHeight() const {

	return this->tileSize * numRows;

}

float TileSystem::GetWidth() const {

	return this->tileSize * numColumns;

}

unsigned int& TileSystem::TileValue(const int& row, const int& col) {

	return tileMap[row][col];

}

int TileSystem::GetTile(const float& position) const {

	if (position >= -tileSize * 0.5f) {
		return static_cast<int>(position / tileSize + 0.5f);
	}

	return static_cast<int>(position / tileSize);

}

float TileSystem::GetBoundaryLeft() const {

	return boundaryLeft;

}

float TileSystem::GetBoundaryRight() const {

	return boundaryRight;

}

float TileSystem::GetBoundaryBottom() const {

	return boundaryBottom;

}

float TileSystem::GetBoundaryTop() const {

	return boundaryTop;

}