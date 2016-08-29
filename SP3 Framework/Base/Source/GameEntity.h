#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "EntityBase.h"
#include "Vector2.h"

//The base entity for this game.
class GameEntity : public EntityBase {

public:
	//Variable(s)
	Vector2 velocity; //How fast this entity is moving.
	Vector2 position; //Where this entity is.

	//Constructor(s) & Destructor
	GameEntity(const string& name, const string& sceneName) : EntityBase(name, sceneName) {}
	virtual ~GameEntity() {}

	//Virtual Function(s)
	virtual void Reset() {}

};

#endif