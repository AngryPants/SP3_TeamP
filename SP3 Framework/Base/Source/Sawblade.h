#ifndef SAW_BLADE_H
#define SAW_BLADE_H

#include "EntityBase.h"
#include "Mesh.h"
#include "Vector2.h"
#include "Texture.h"
#include "Hero.h"

#include <map>

class Sawblade : public EntityBase {

private:
	//Variable(s)
	bool initialized;

	Vector2 position;
	Vector2 velocity;
	float speed;
	float rotation;

	float radius;
	int damage;
	
	Hero *hero;
	
	Mesh *mesh;
	Texture texture;

	std::map<unsigned int, Vector2> nodes;
	std::map<unsigned int, Vector2>::iterator destinationNode;

	void DamageHero(const double& deltaTime);
	void MoveToNode(const double& deltaTime);

public:
	//Constructor(s) & Destructor
	Sawblade();
	virtual ~Sawblade() {}

	void AddNode(unsigned int index, Vector2 position);
	void SetHero(Hero& hero);
	void RemoveHero();

	//Virtual Function(s)
	void Update(const double &deltaTime);
	void Render();
	void RenderUI() {}

};

#endif