#include "MapEditor.h"
#include "InputManager.h"
#include <fstream>
#include <sstream>

using namespace std;

MapEditor::MapEditor() {

	name = "Map Editor";

	filePath = "Levels//Custom//";
	tileSystem = nullptr;
	tileX = 0;
	tileY = 0;

}

MapEditor::~MapEditor() {
}

bool MapEditor::CheckFileExist(const string& fileName) {

	if (ifstream(fileName)) {
		return true;
	}

	return false;

}

void MapEditor::SetTileSystem(TileSystem& tileSystem) {

	this->tileSystem = &tileSystem;

}

void MapEditor::RemoveTileSystem() {

	this->tileSystem = nullptr;
	tileX = 0;
	tileY = 0;

}

void MapEditor::Update(const double& deltaTime) {

	if (tileSystem == nullptr) {
		cout << "Unable to update MapEditor as no tileMap was attached." << endl;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MOVE_RIGHT]) {
		++tileX;
	} else if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MOVE_LEFT]) {
		--tileX;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MOVE_UP]) {
		++tileY;
	} else if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MOVE_DOWN]) {
		--tileY;
	}

	if (tileX < 0) {
		tileX = 0;
	}
	if (tileY < 0) {
		tileY = 0;
	}

}

void MapEditor::Render() {
}

void MapEditor::RenderUI() {

	

}

//Sets a tile to 0.
void MapEditor::DeleteTile() {

	tileSystem->tiles[tileY][tileX].tileValue = 0;

}