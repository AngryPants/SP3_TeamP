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
	meshTextures[MESH_HEALTH].textureArray[0] = TextureManager::GetInstance().AddTexture("Health", "Image//Cyborg_Shooter//Tiles//Items//Item_Health.tga");
	meshTextures[MESH_HERO_SPAWN].textureArray[0] = TextureManager::GetInstance().AddTexture("Hero Spawn", "Image//Cyborg_Shooter//Tiles//Items//Item_Hero_Spawn.tga");
	meshTextures[MESH_CHECKPOINT_SET].textureArray[0] = TextureManager::GetInstance().AddTexture("Checkpoint Unset", "Image//Cyborg_Shooter//Tiles//Items//Item_Checkpoint_Set.tga");
	meshTextures[MESH_CHECKPOINT_UNSET].textureArray[0] = TextureManager::GetInstance().AddTexture("Checkpoint Set", "Image//Cyborg_Shooter//Tiles//Items//Item_Checkpoint_Unset.tga");
	meshTextures[MESH_DOOR_OPEN].textureArray[0] = TextureManager::GetInstance().AddTexture("Door Open", "Image//Cyborg_Shooter//Tiles//Items//Item_Door_Open.tga");
	meshTextures[MESH_DOOR_CLOSE].textureArray[0] = TextureManager::GetInstance().AddTexture("Door Close", "Image//Cyborg_Shooter//Tiles//Items//Item_Door_Close.tga");
	meshTextures[MESH_OBJECTIVE].textureArray[0] = TextureManager::GetInstance().AddTexture("Objective", "Image//Cyborg_Shooter//Tiles//Items//Item_Objective.tga");

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
	animation[SPRITE_COIN].Set(1, 4, 0, 3, true, 0.4, true);
	sprite[SPRITE_COIN] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Coin", 1, 4);
	sprite[SPRITE_COIN]->animation = &animation[SPRITE_COIN];
	spriteTextures[SPRITE_COIN].textureArray[0] = TextureManager::GetInstance().AddTexture("Coin", "Image//Cyborg_Shooter//Tiles//Items//Item_Coin.tga");
	
	animation[SPRITE_BOOSTPAD].Set(2, 2, 0, 4, true, 0.25, true);
	sprite[SPRITE_BOOSTPAD] = MeshBuilder::GetInstance().GenerateSpriteAnimation("Boost Pad", 2, 2);
	sprite[SPRITE_BOOSTPAD]->animation = &animation[SPRITE_BOOSTPAD];
	spriteTextures[SPRITE_BOOSTPAD].textureArray[0] = TextureManager::GetInstance().AddTexture("Boost Pad", "Image//Cyborg_Shooter//Tiles//Items//Item_Boostpad.tga");	
	
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

void MapRenderer::Update(const double& deltaTime) {

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		sprite[i]->Update(deltaTime);
	}

}

void MapRenderer::Render(TileSystem& tileSystem) {

	unsigned int terrain = 0;
	unsigned int interactable = 0;
	unsigned int item = 0;	
	unsigned int sign = 0;
	unsigned int spawn = 0;

	MS& modelStack = GraphicsManager::GetInstance().modelStack;

	for (int row = Math::Max(0, startRow); row < Math::Min(tileSystem.GetNumRows(), endRow); ++row) {
		for (int column = Math::Max(0, startColumn); column < Math::Min(tileSystem.GetNumColumns(), endColumn); ++column) {
			modelStack.PushMatrix();
				modelStack.Translate(column * tileSystem.GetTileSize(), row * tileSystem.GetTileSize(), -6);

				unsigned int tileValue = tileSystem.TileValue(row, column);

				//Terrain
				terrain = GetTileType(TILE_TYPE::TERRAIN, tileValue);
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

				//Signs (Arrows etc.)
				sign = GetTileType(TILE_TYPE::SIGNS, tileValue);
				modelStack.Translate(0, 0, 1);
				switch (sign) {
					case 0:
						//Do Nothing
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
				
				//Interactables
				interactable = GetTileType(TILE_TYPE::INTERACTABLES, tileValue);
				modelStack.Translate(0, 0, 1);
				switch (interactable) {
					case 0:
						//Do Nothing
					break;
					case TILE_ACID:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_ACID], false);
					break;
					case TILE_SPIKE:
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_SPIKE], false);
						break;
					case TILE_HERO_SPAWN:
						modelStack.Scale(3, 3, 3);
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_HERO_SPAWN], false);
						break;
					case TILE_CHECKPOINT_UNSET:
						modelStack.Scale(3, 3, 3);
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_CHECKPOINT_UNSET], false);
						break;
					case TILE_CHECKPOINT_SET:
						modelStack.Scale(3, 3, 3);
						RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_CHECKPOINT_SET], false);
						break;				
					case TILE_DOOR_OPEN:
						modelStack.Scale(3, 3, 3); 
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_DOOR_OPEN], spriteTextures[SPRITE_DOOR_OPEN], false);
						break;
					case TILE_DOOR_CLOSE:
						modelStack.Scale(3, 3, 3); 
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_DOOR_CLOSE], spriteTextures[SPRITE_DOOR_CLOSE], false);
						break;
					case TILE_BOOSTPAD_RIGHT:
						RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_BOOSTPAD], spriteTextures[SPRITE_BOOSTPAD], false);
						break;
					case TILE_BOOSTPAD_LEFT:
						modelStack.PushMatrix();
							modelStack.Rotate(180, 0, 0, 1);
							RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_BOOSTPAD], spriteTextures[SPRITE_BOOSTPAD], false);
						modelStack.PopMatrix();
					break;
					case TILE_BOOSTPAD_DOWN:
						modelStack.PushMatrix();
							modelStack.Rotate(270, 0, 0, 1);
							RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_BOOSTPAD], spriteTextures[SPRITE_BOOSTPAD], false);
						modelStack.PopMatrix();
					break;
					case TILE_BOOSTPAD_UP:
						modelStack.PushMatrix();
							modelStack.Rotate(90, 0, 0, 1);
							RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_BOOSTPAD], spriteTextures[SPRITE_BOOSTPAD], false);
						modelStack.PopMatrix();
					break;
				}

				//Render Items
				item = GetTileType(TILE_TYPE::ITEMS, tileValue);
				modelStack.Translate(0, 0, 1);
				switch (item) {
					case 0:
						//Do Nothing
					break;
					case TILE_COIN:
						if (CheckItemToggle(tileValue))
							RenderHelper::GetInstance().RenderMesh(*sprite[SPRITE_COIN], spriteTextures[SPRITE_COIN], false);
					break;
					case TILE_HEALTH:
						if (CheckItemToggle(tileValue))	
							RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_HEALTH], false);
					break;
					case TILE_CHECKPOINT: {
						modelStack.PushMatrix();
							modelStack.Scale(3, 3, 1);
							if (CheckItemToggle(tileValue)) {
								RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_CHECKPOINT_UNSET], false);
							} else {
								RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_CHECKPOINT_SET], false);
							}
						modelStack.PopMatrix();
					}
					break;
					case TILE_DOOR: {
						modelStack.PushMatrix();
							modelStack.Scale(1, 2, 1);
							if (CheckItemToggle(tileValue)) {
								RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_DOOR_OPEN]);
							} else {
								RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_DOOR_CLOSE]);
							}
						modelStack.PopMatrix();
					}
					break;
					case TILE_OBJECTIVE: {
						if (CheckItemToggle(tileValue)) {
							RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_OBJECTIVE]);
						}
					}
					break;
				}

				//Render Spawn
				spawn = GetTileType(TILE_TYPE::SPAWNS, tileValue);
				modelStack.Translate(0, 0, 1);
				switch (spawn) {
					case TILE_SPAWN_HERO: {
						modelStack.PushMatrix();
						modelStack.Scale(3, 3, 1);
							RenderHelper::GetInstance().RenderMesh(*mesh, meshTextures[MESH_HERO_SPAWN]);
						modelStack.PopMatrix();
					}
					break;
				}

			modelStack.PopMatrix();
		}
	}

}

void MapRenderer::Reset() {

	for (unsigned int i = 0; i < NUM_SPRITE; ++i) {
		sprite[i]->Reset(true);
	}

}