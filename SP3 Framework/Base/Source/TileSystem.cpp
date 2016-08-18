#include "TileSystem.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "TileIndex.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

//Constructor(s) & Destructor
TileSystem::TileSystem()
{

	tileSize = 1;

	renderStartTileRow = 0;
	renderEndTileRow = 0;
	renderStartTileColumn = 0;
	renderEndTileColumn = 0;

	//Mesh
	mesh = MeshBuilder::GetInstance().GenerateQuad("Tile");
	//Mesh Textures
	//Terrain
	meshTextures[MESH_WALL_1].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 1", "Image//Cyborg_Shooter//Tiles//Terrain//Terrain_Wall_1.tga");
	meshTextures[MESH_WALL_2].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 2", "Image//Cyborg_Shooter//Tiles//Terrain//Terrain_Wall_2.tga");
	meshTextures[MESH_WALL_3].textureArray[0] = TextureManager::GetInstance().AddTexture("Wall 3", "Image//Cyborg_Shooter//Tiles//Terrain//Terrain_Wall_3.tga");

	//Items
	meshTextures[MESH_ACID].textureArray[0] = TextureManager::GetInstance().AddTexture("Acid", "Image//Cyborg_Shooter//Tiles//Items//Item_Acid.tga");
	meshTextures[MESH_SPIKE].textureArray[0] = TextureManager::GetInstance().AddTexture("Spike", "Image//Cyborg_Shooter//Tiles//Items//Item_Spike.tga");
	meshTextures[MESH_WRENCH].textureArray[0] = TextureManager::GetInstance().AddTexture("Wrench", "Image//Cyborg_Shooter//Tiles//Items//Item_Wrench.tga");
	meshTextures[MESH_HERO_SPAWN].textureArray[0] = TextureManager::GetInstance().AddTexture("Hero Spawn", "Image//Cyborg_Shooter//Tiles//Items//Item_Hero_Spawn.tga");
	meshTextures[MESH_CHECKPOINT_SET].textureArray[0] = TextureManager::GetInstance().AddTexture("Checkpoint Unset", "Image//Cyborg_Shooter//Tiles//Items//Item_Checkpoint_Unset.tga");
	meshTextures[MESH_CHECKPOINT_UNSET].textureArray[0] = TextureManager::GetInstance().AddTexture("Checkpoint Set", "Image//Cyborg_Shooter//Tiles//Items//Item_Checkpoint_Set.tga");

	//Signs
	meshTextures[MESH_ARROW_LEFT].textureArray[0] = TextureManager::GetInstance().AddTexture("Arrow Left", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Arrow_Left.tga");
	meshTextures[MESH_ARROW_RIGHT].textureArray[0] = TextureManager::GetInstance().AddTexture("Arrow Right", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Arrow_Right.tga");
	meshTextures[MESH_ARROW_UP].textureArray[0] = TextureManager::GetInstance().AddTexture("Arrow Up", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Arrow_Up.tga");
	meshTextures[MESH_ARROW_DOWN].textureArray[0] = TextureManager::GetInstance().AddTexture("Arrow Down", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Arrow_Down.tga");
	meshTextures[MESH_WARNING].textureArray[0] = TextureManager::GetInstance().AddTexture("Warning", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Warning.tga");
	meshTextures[MESH_WARNING_SAWBLADE].textureArray[0] = TextureManager::GetInstance().AddTexture("Warning Sawblade", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Warning_Sawblade.tga");
	meshTextures[MESH_WARNING_SPIKE].textureArray[0] = TextureManager::GetInstance().AddTexture("Warning Spike", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Warning_Spike.tga");
	meshTextures[MESH_ALERT_TRAMPOLINE].textureArray[0] = TextureManager::GetInstance().AddTexture("Alert Trampoline", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Alert_Trampoline.tga");
	meshTextures[MESH_ALERT_EXIT].textureArray[0] = TextureManager::GetInstance().AddTexture("Acid", "Image//Cyborg_Shooter//Tiles//Signs//Sign_Alert_Exit.tga");

	//Sprite
	animation[SPRITE_COIN].Set(0, 3, true, 1.0, true);
	sprite[SPRITE_COIN] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Coin", 1, 4);
	sprite[SPRITE_COIN]->animation = &animation[SPRITE_COIN];
		
	animation[SPRITE_DOOR].Set(0, 3, false, 1.0, false);
	sprite[SPRITE_DOOR] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Door", 1, 4);
	sprite[SPRITE_DOOR]->animation = &animation[SPRITE_DOOR];

	animation[SPRITE_TRAMPOLINE].Set(0, 4, false, 1.0, false);
	sprite[SPRITE_TRAMPOLINE] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Trampoline", 1, 5);
	sprite[SPRITE_TRAMPOLINE]->animation = &animation[SPRITE_TRAMPOLINE];

	//Sprite Textures
	spriteTextures[SPRITE_COIN].textureArray[0] = TextureManager::GetInstance().AddTexture("Coin", "Image//Cyborg_Shooter//Tiles//Items//Item_Coin.tga");
	spriteTextures[SPRITE_DOOR].textureArray[0] = TextureManager::GetInstance().AddTexture("Door", "Image//Cyborg_Shooter//Tiles//Items//Item_Door.tga");
	spriteTextures[SPRITE_TRAMPOLINE].textureArray[0] = TextureManager::GetInstance().AddTexture("Trampoline", "Image//Cyborg_Shooter//Tiles//Items//Item_Trampoline.tga");

}

TileSystem::~TileSystem()
{
}

//Virtual Function(s)
void TileSystem::Update(const double& deltaTime)
{

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		sprite[i]->Update(deltaTime);
	}

}

void TileSystem::Render()
{

	unsigned int terrain = 0;
	unsigned int item = 0;
	unsigned int sign = 0;

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	
	for (int row = Math::Max(0, renderStartTileRow); row < Math::Min(numRows, renderEndTileRow); ++row)
	{
		for (int column = Math::Max(0, renderStartTileColumn); column < Math::Min(numColumns, renderEndTileColumn); ++column)
		{
			terrain = tiles[row][column].GetTileValue(Tile::TILE_TYPE::TERRAIN);
			item = tiles[row][column].GetTileValue(Tile::TILE_TYPE::ITEM);
			sign = tiles[row][column].GetTileValue(Tile::TILE_TYPE::SIGN);

			modelStack.PushMatrix();
				modelStack.Translate(column * tileSize, row * tileSize, -4);
				//Terrain (Walls etc.)
				switch (terrain)
				{
					case 0:
						//Do Nothing
						break;
					case TILE_WALL_1:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_WALL_1], false);				
						break;
					case TILE_WALL_2:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_WALL_2], false);	
						break;
					case TILE_WALL_3:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_WALL_3], false);	
						break;
				}

				modelStack.Translate(0, 0, 1);
				//Items (Coins, Trampoline, Checkpoints etc)
				switch (item)
				{
					case 0:
						//Do Nothing
						break;
					case TILE_COIN:
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_COIN], spriteTextures[SPRITE_COIN], false);
						break;
					case TILE_ACID:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ACID], false);	
						break;
					case TILE_SPIKE:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_SPIKE], false);
						break;
					case TILE_DOOR_OPEN:
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_DOOR], spriteTextures[SPRITE_DOOR], false);
						break;
					case TILE_DOOR_CLOSE:
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_DOOR], spriteTextures[SPRITE_DOOR], false);
						break;
					case TILE_TRAMPOLINE:
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_TRAMPOLINE], spriteTextures[SPRITE_TRAMPOLINE], false);
						break;
				}

				modelStack.Translate(0, 0, 1);
				//Signs (Arrows etc.)
				switch (sign)
				{
					case 0:
						break;
					case TILE_ARROW_LEFT:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ARROW_LEFT], false);
						break;
					case TILE_ARROW_RIGHT:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ARROW_RIGHT], false);
						break;
					case TILE_ARROW_UP:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ARROW_UP], false);
						break;
					case TILE_ARROW_DOWN:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ARROW_DOWN], false);
						break;
					case TILE_WARNING:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_WARNING], false);
						break;
					case TILE_WARNING_SAWBLADE:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_WARNING_SAWBLADE], false);
						break;
					case TILE_WARNING_SPIKE:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_WARNING_SPIKE], false);
						break;
					case TILE_ALERT_TRAMPOLINE:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ALERT_TRAMPOLINE], false);
						break;
					case TILE_ALERT_EXIT:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ALERT_EXIT], false);
						break;
				}

			modelStack.PopMatrix();
		}
	}

}

void TileSystem::RenderUI()
{
}

bool TileSystem::LoadFile(const string& filePath)
{
	
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
		//tiles.push_back(currentRow);
		tiles.insert(tiles.begin(), currentRow);

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

void TileSystem::SetRenderTilesRow(const int& start, const int& end) {

	if (start > 0) {
		this->renderStartTileRow = start;
	} else {
		this->renderStartTileRow = 0;
	}

	if (end > 0) {
		this->renderEndTileRow = end;
	} else {
		this->renderEndTileRow = 0;
	}

	if (this->renderEndTileRow < this->renderStartTileRow) {
		this->renderEndTileRow = this->renderStartTileRow;
	}

}

void TileSystem::SetRenderTilesColumn(const int& start, const int& end) {

	if (start > 0) {
		this->renderStartTileColumn = start;
	} else {
		this->renderStartTileColumn = 0;
	}

	if (end > 0) {
		this->renderEndTileColumn = end;
	} else {
		this->renderEndTileColumn = 0;
	}

	if (this->renderEndTileColumn < this->renderStartTileColumn) {
		this->renderEndTileColumn = this->renderStartTileColumn;
	}

}

int TileSystem::GetNumRows() const {

	return numRows;

}

int TileSystem::GetNumColumns() const {

	return numColumns;

}