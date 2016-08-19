#ifndef BULLET_H
#define BULLET_H

#include "EntityBase.h"
#include "Mesh.h"
#include "Texture.h"
#include "Vector2.h"

class Bullet : public EntityBase {

protected:
	//The position of the bullet
	Vector2 position;
	//The speed of the bullet
	Vector2 velocity;
	//The lifetime of the bullet
	float lifetime;
	//The damage of the bullet
	int damage;
	bool isActive;

public:
	Bullet();
	virtual ~Bullet();

	void SetVelocity(float x, float y);
	Vector2 GetVelocity() const;

	//Virtual Function(s)
	void Update(const double& deltaTime);
	void Render();
	void RenderUI();

};

#endif