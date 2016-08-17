#include "TileSystem.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "TileIndex.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Constructor(s) & Destructor
TileSystem::TileSystem() {

	tileSize = 1;

	//Mesh
	mesh = MeshBuilder::GetInstance().GenerateQuad("Tile");
	//Mesh Textures
	meshTextures[TEX_WALL_1].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 1", "Image//Tiles//Wall_1.tga");
	meshTextures[TEX_WALL_2].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 2", "Image//Tiles//Wall_2.tga");
	meshTextures[TEX_WALL_3].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 3", "Image//Tiles//Wall_3.tga");
	meshTextures[TEX_WALL_4].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 4", "Image//Tiles//Wall_4.tga");
	meshTextures[TEX_ACID].textureArray[0] = TextureManager::GetInstance().AddTexture("Acid", "Image//Tiles//Acid.tga");
	meshTextures[TEX_SPIKE].textureArray[0] = TextureManager::GetInstance().AddTexture("Spike", "Image//Tiles//Spike.tga");

	//Sprite
	/*animation[ANIM_COIN].Set(0, 3, true, 1.0, true);
	sprite[ANIM_COIN] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Coin", 1, 4);
	sprite[ANIM_COIN]->animation = &animation[ANIM_COIN];

	animation[ANIM_DOOR].Set(0, 3, false, 1.0, false);
	sprite[ANIM_DOOR] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Door", 1, 4);
	sprite[ANIM_DOOR]->animation = &animation[ANIM_DOOR];

	animation[ANIM_TRAMPOLINE].Set(0, 4, false, 1.0, false);
	sprite[ANIM_TRAMPOLINE] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Trampoline", 1, 5);
	sprite[ANIM_TRAMPOLINE]->animation = &animation[ANIM_TRAMPOLINE];

	//Sprite Textures
	spriteTextures[ANIM_COIN].textureArray[0] = TextureManager::GetInstance().AddTexture("Coin", "Image//Tiles//Coin.tga");
	spriteTextures[ANIM_DOOR].textureArray[0] = TextureManager::GetInstance().AddTexture("Door", "Image//Tiles//Door.tga");
	spriteTextures[ANIM_TRAMPOLINE].textureArray[0] = TextureManager::GetInstance().AddTexture("Trampoline", "Image//Tiles//Trampoline.tga");*/

}

TileSystem::~TileSystem() {
}

//Virtual Function(s)
void TileSystem::Update(const double& deltaTime) {
}

void TileSystem::Render() {

	

}

void TileSystem::RenderUI() {
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
	tiles.clear();
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
		vector<Tile> currentRow;
		currentRow.resize(numColumns); //Make it the size of the largest row.

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
				currentRow.resize(numColumns);
				for (vector<vector<Tile> >::iterator iter = tiles.begin(); iter != tiles.end(); ++iter) {
					(*iter).resize(numColumns);
				}
			}
			currentRow[columnCounter - 1].tileValue = atoi(token.c_str());
			//currentRow.push_back(atoi(token.c_str()));
		}
		//Add the current row to our tiles.
		tiles.push_back(currentRow);

	}

	//Close the file after we're done.
	file.close();
	
	UpdateBorders();

	return true;

}

void TileSystem::SetTileSize(const float& tileSize) {

	this->tileSize = tileSize;

}

float TileSystem::GetTileSize() const {

	return this->tileSize;

}

void TileSystem::UpdateBorders() {

	leftBorder = -0.5f * tileSize;
	rightBorder = leftBorder + numColumns * tileSize;
	bottomBorder = -0.5f * tileSize;
	topBorder = bottomBorder + numRows * tileSize;

}

float TileSystem::GetLeftBorder() const {

	return this->leftBorder;

}

float TileSystem::GetRightBorder() const {

	return this->rightBorder;

}

float TileSystem::GetTopBorder() const {

	return this->topBorder;

}

float TileSystem::GetBottomBorder() const {

	return this->bottomBorder;

}

int TileSystem::GetTile(const float& position) const {

	if (position >= -tileSize * 0.5f) {
		return static_cast<int>(position / tileSize + 0.5f);
	}

	return static_cast<int>(position / tileSize - 0.5f);

}