#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "EntityBase.h"
#include "Vector2.h"

//The base entity for this game.
class GameEntity : public EntityBase {

public:
	//Variable(s)
	Vector2 velocity;
	Vector2 position;
	bool isActive;

	//Constructor(s) & Destructor
	GameEntity(const string& name, const string& sceneName) : EntityBase(name, sceneName) {
		isActive = true;
	}
	virtual ~GameEntity() {}

};

#endif