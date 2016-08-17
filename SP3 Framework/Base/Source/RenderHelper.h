#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include "SingletonTemplate.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "Texture.h"
#include "Vertex.h"

class RenderHelper : public Singleton<RenderHelper> {

	friend class Singleton<RenderHelper>;

private:
	//Variable(s)
	bool refreshUniforms;
	
	//Uniform Enums
	//enum UNIFORM_TYPE {
	//	
	//};

	//Constructor(s) & Destructor
	RenderHelper();
	virtual ~RenderHelper();

public:
	void Update();

	//Rendering
	void RenderMesh(Mesh& mesh, Texture& texture, const bool& enableLight);
	void RenderText(Mesh& mesh, Texture& texture, const string& text, Color color);

};

#endif