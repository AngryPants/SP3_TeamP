#ifndef BULLET_H
#define BULLET_H

#include "EntityBase.h"
#include "Mesh.h"
#include "Texture.h"
#include "Vector2.h"

class Bullet : public EntityBase {

private:
	Mesh* mesh;
	Texture texture;

	//Indicate the IsActive of this bullet
	bool bIsActive;
	//The position of the bullet
	Vector2 position;
	//The rotation of the bullet
	float rotation;
	//The speed of the bullet
	float speed;
	//The lifetime of the bullet
	float lifetime;
	//The damage of the bullet
	int damage;

public:
	Bullet();
		/*mesh = MeshBuiklder::GenerateQuad("Bullet", 1.0f);
		texture - Textadasd a:AdddTExture(aslkdjakls, "");*/
	Bullet(bool bIsActive, Vector2 position, float rotation, float speed, float lifetime, int damage);
	~Bullet();

	//Virtual Function(s)
	void Update(const double& deltaTime);
	void Render();
	void RenderUI() {}
};

#endif