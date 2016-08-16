#include "TileMap.h"
#include <iostream>

using std::cin;
using std::cout;

TileMap::TileMap(void) {

	map.clear();
	numRows = 0;
	numColumns = 0;
	tileSize = 1.0f; 

	leftBorder = 0.0f;
	rightBorder = 0.0f;
	topBorder = 0.0f;
	bottomBorder = 0.0f;

}

TileMap::~TileMap(void) {

	map.clear();

}

bool TileMap::LoadFile(const string& mapName) {

	//Open the file.
	ifstream file(mapName.c_str());
	//If file is successfully opened.
	if (!file.is_open()) {
		cout << "Error: Cannot open file " << mapName << "." << endl;
		return false;
	}

	//Empty our current map.
	map.clear();
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
		vector<int> currentRow;
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
				for (vector<vector<int> >::iterator iter = map.begin(); iter != map.end(); ++iter) {
					(*iter).resize(numColumns, 0);
				}
			}
			currentRow[columnCounter - 1] = atoi(token.c_str());
			//currentRow.push_back(atoi(token.c_str()));
		}
		//Add the current row to our map.
		//map.push_back(currentRow);
		map.insert(map.begin(), currentRow);

	}

	//Close the file after we're done.
	file.close();
	
	UpdateBorders();

	return true;

}

int TileMap::GetNumRows() const {

	return this->numRows;

}

int TileMap::GetNumColumns() const {

	return this->numColumns;

}

void TileMap::SetTileSize(const float& tileSize) {

	if (tileSize <= 0.0f) {
		this->tileSize = 0.0f;
	} else {
		this->tileSize = tileSize;
	}

	UpdateBorders();

}

float TileMap::GetTileSize() const {

	return tileSize;

}

int TileMap::GetTileX(const float& xPosition) {

	if (xPosition >= -tileSize * 0.5f) {
		return static_cast<int>(xPosition / tileSize + 0.5f);
	}

	return static_cast<int>(xPosition / tileSize - 0.5f);

}

int TileMap::GetTileY(const float& yPosition) {

	if (yPosition >= -tileSize * 0.5f) {
		return static_cast<int>(yPosition / tileSize + 0.5f);
	}

	return static_cast<int>(yPosition / tileSize - 0.5f);

}

void TileMap::UpdateBorders() {

	leftBorder = -0.5f * tileSize;
	rightBorder = leftBorder + numColumns * tileSize;
	bottomBorder = -0.5f * tileSize;
	topBorder = bottomBorder + numRows * tileSize;

}

float TileMap::GetLeftBorder() const {

	return this->leftBorder;

}

float TileMap::GetRightBorder() const {

	return this->rightBorder;

}

float TileMap::GetTopBorder() const {

	return this->topBorder;

}

float TileMap::GetBottomBorder() const {

	return this->bottomBorder;

}