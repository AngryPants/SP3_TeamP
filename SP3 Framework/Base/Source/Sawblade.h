#ifndef SAW_BLADE_H
#define SAW_BLADE_H

#include "EntityBase.h"
#include "Mesh.h"
#include "Vector2.h"
#include "Texture.h"
#include "Character.h"

#include <map>

class Sawblade : public GameEntity {

private:
	//Variable(s)
	bool initialized;

	Vector2 position;
	Vector2 velocity;
	float speed;
	float rotation;
	Mesh *mesh;
	Texture texture;

	float radius;
	int damage;

	std::map<unsigned int, Vector2> nodes;
	std::map<unsigned int, Vector2>::iterator destinationNode;

	void DamageTargets(const double& deltaTime);
	void MoveToNode(const double& deltaTime);

public:
	Character* target;

	//Constructor(s) & Destructor
	Sawblade(const string& sceneName);
	virtual ~Sawblade() {}

	void Reset();
	void AddNode(unsigned int index, Vector2 position);

	//Virtual Function(s)
	void Update(const double &deltaTime);
	void Render();
	void RenderUI() {}

};

#endif