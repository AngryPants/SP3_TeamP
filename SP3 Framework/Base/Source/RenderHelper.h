#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H

#include "SingletonTemplate.h"
#include "Mesh.h"
#include "SpriteAnimation.h"
#include "Texture.h"
#include "Vertex.h"
#include "ShaderProgram.h"

enum class SHADERS
{
	SHADOW
};

class RenderHelper : public Singleton<RenderHelper> {

	friend class Singleton<RenderHelper>;

public:
	struct ShadowUniforms {
		UniformID modelView;
		UniformID modelViewProjection;
		UniformID modelViewInverseTranspose;
		UniformID ambient;
		UniformID diffuse;
		UniformID specular;
		UniformID shininess;
		UniformID colorTextureEnabled;
		UniformID colorTexture;
		UniformID textColor;
		UniformID textEnabled;
		UniformID numLights;
		UniformID lightEnabled;
		UniformID fogEnabled;
		UniformID alphaDiscardValue;
		UniformID textureOffset;
		UniformID textureScale;
	};

private:
	//Variable(s)
	bool refreshUniforms;
	ShadowUniforms shadowUniforms;
	SHADERS currentShader;

	//Constructor(s) & Destructor
	RenderHelper();
	virtual ~RenderHelper();

	//Shader Loading
	void LoadShadowShader();

public:
	template<SHADERS>
	void LoadShader() {

		throw std::exception("Unrecognisable shader!");

	}

	template<>
	void LoadShader<SHADERS::SHADOW>() {
		LoadShadowShader();
	}


	void Update();
	void SetNumLights(const unsigned num);
	void SetAlphaDiscardValue(const float alphaValue);
	void EnableLight(const bool boolean);
	void EnableFog(const bool boolean);

	//Rendering
	void RenderMesh(Mesh& mesh, Texture& texture, const bool& enableLight= false);
	void RenderMesh(Mesh& mesh, const bool& enableLight = false);
	void RenderText(Mesh& mesh, Texture& texture, const string& text, Color color);

};

#endif