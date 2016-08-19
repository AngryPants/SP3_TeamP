#include "MapRenderer.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "Animation.h"
#include "TileIndex.h"

MapRenderer::MapRenderer() {

	startRow = 0;
	endRow = 0;
	startColumn = 0;
	endColumn = 0;

	mesh = MeshBuilder::GetInstance().GenerateQuad("Tile");

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

	/*animation[SPRITE_TRAMPOLINE].Set(0, 4, false, 1.0, false);
	sprite[SPRITE_TRAMPOLINE] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Trampoline", 1, 5);
	sprite[SPRITE_TRAMPOLINE]->animation = &animation[SPRITE_TRAMPOLINE];*/

	//Sprite Textures
	spriteTextures[SPRITE_COIN].textureArray[0] = TextureManager::GetInstance().AddTexture("Coin", "Image//Cyborg_Shooter//Tiles//Items//Item_Coin.tga");
	spriteTextures[SPRITE_DOOR].textureArray[0] = TextureManager::GetInstance().AddTexture("Door", "Image//Cyborg_Shooter//Tiles//Items//Item_Door.tga");
	//spriteTextures[SPRITE_TRAMPOLINE].textureArray[0] = TextureManager::GetInstance().AddTexture("Trampoline", "Image//Cyborg_Shooter//Tiles//Items//Item_Trampoline.tga");
	

}

MapRenderer::~MapRenderer() {
}

void MapRenderer::SetStartRow(const int& startRow) {

	this->startRow = startRow;

}

void MapRenderer::SetEndRow(const int& endRow) {

	this->endRow = endRow;

}

void MapRenderer::SetStartColumn(const int& startColumn) {

	this->startColumn = startColumn;

}

void MapRenderer::SetEndColumn(const int& endColumn) {

	this->endColumn = endColumn;

}

void MapRenderer::Render(TileSystem& tileSystem) {

	unsigned int terrain = 0;
	unsigned int item = 0;
	unsigned int sign = 0;

	MS& modelStack = GraphicsManager::GetInstance().modelStack;

	for (int row = Math::Max(0, startRow); row < Math::Min(tileSystem.GetNumRows(), endRow); ++row) {
		for (int column = Math::Max(0, startColumn); column < Math::Min(tileSystem.GetNumColumns(), endColumn); ++column) {
			modelStack.PushMatrix();
				modelStack.Translate(column * tileSystem.GetTileSize(), row * tileSystem.GetTileSize(), -5);

				terrain = GetTileInfo(TILE_INFO::TERRAIN, tileSystem.TileValue(row, column));
				item = GetTileInfo(TILE_INFO::ITEM, tileSystem.TileValue(row, column));
				sign = GetTileInfo(TILE_INFO::SIGN, tileSystem.TileValue(row, column));

				//Render Terrain
				switch (terrain) {
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
				//Render Items
				switch (item) {
					case 0:
						break;
					case TILE_COIN:
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_COIN], spriteTextures[SPRITE_COIN], false);
						break;
					case TILE_DOOR_OPEN:
						//RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_COIN], spriteTextures[SPRITE_COIN], false);
						break;
					case TILE_DOOR_CLOSE:
						//RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_COIN], spriteTextures[SPRITE_COIN], false);
						break;
				}

				modelStack.Translate(0, 0, 1);
				//Signs (Arrows etc.)
				switch (sign) {
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