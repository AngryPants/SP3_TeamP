#ifndef SAW_BLADE_H
#define SAW_BLADE_H

#include "EntityBase.h"
#include "Mesh.h"
#include "Vector2.h"

#include <map>

class Sawblade : public EntityBase {

private:
	float speed;
	Vector2 position;
	bool initialized;

	Mesh *mesh;
	Texture texture;

	std::map<unsigned int, Vector2>::iterator nodeIter;

public:
	std::map<unsigned int, Vector2> nodes;

	Sawblade();
	virtual ~Sawblade() {}

	void Update(const double &deltaTime);
	void Render();
	void RenderUI() {}
};

#endif