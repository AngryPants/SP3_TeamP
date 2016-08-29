#include "RenderHelper.h"
#include "GraphicsManager.h"
#include <iostream>

using namespace std;

ShaderProgram* GetShader() {

	ShaderProgram* shaderProgram = GraphicsManager::GetInstance().GetActiveShader();

	if (shaderProgram == nullptr) {
		throw std::exception("Unable to render as no active shader has been set.");
	}

	return shaderProgram;
	
}

ShaderProgram::FloatMat4x4 ToOpenglStruct(const Mtx44& matrix) {

	ShaderProgram::FloatMat4x4 mat;

	mat.mat[0] = matrix.a[0];
	mat.mat[1] = matrix.a[1];
	mat.mat[2] = matrix.a[2];
	mat.mat[3] = matrix.a[3];

	mat.mat[4] = matrix.a[4];
	mat.mat[5] = matrix.a[5];
	mat.mat[6] = matrix.a[6];
	mat.mat[7] = matrix.a[7];

	mat.mat[8] = matrix.a[8];
	mat.mat[9] = matrix.a[9];
	mat.mat[10] = matrix.a[10];
	mat.mat[11] = matrix.a[11];

	mat.mat[12] = matrix.a[12];
	mat.mat[13] = matrix.a[13];
	mat.mat[14] = matrix.a[14];
	mat.mat[15] = matrix.a[15];

	return mat;

}

ShaderProgram::FloatVec3 ToOpenglStruct(const Color& color) {

	ShaderProgram::FloatVec3 col;

	col.vec[0] = color.r;
	col.vec[1] = color.g;
	col.vec[2] = color.b;

	return col;

}

ShaderProgram::FloatVec3 ToOpenglStruct(const MaterialComponent& component) {

	ShaderProgram::FloatVec3 comp;

	comp.vec[0] = component.r;
	comp.vec[1] = component.g;
	comp.vec[2] = component.b;

	return comp;

}

void SetNumLightsDelegate(const unsigned num, const RenderHelper::ShadowUniforms& shadowUniforms) {

	ShaderProgram* shaderProgram = GetShader();

	shaderProgram->Update(shadowUniforms.numLights, num);

}

void EnableLightDelegate(const bool boolean, const RenderHelper::ShadowUniforms& shadowUniforms) {

	ShaderProgram* shaderProgram = GetShader();

	shaderProgram->Update(shadowUniforms.lightEnabled, boolean);

}

void EnableFogDelegate(const bool boolean, const RenderHelper::ShadowUniforms& shadowUniforms) {

	ShaderProgram* shaderProgram = GetShader();

	shaderProgram->Update(shadowUniforms.fogEnabled, boolean);

}

void RenderTextDelegate(Mesh& mesh, Texture& texture, const string& text, Color color, const RenderHelper::ShadowUniforms& shadowUniforms) {

	ShaderProgram* shaderProgram = GetShader();

	shaderProgram->Update(shadowUniforms.textEnabled, true);
	shaderProgram->Update(shadowUniforms.textColor, ToOpenglStruct(color), 1);
	shaderProgram->Update(shadowUniforms.lightEnabled, false);

	int booleans[MAX_TEXTURES] = { 1, 0, 0, 0, 0, 0, 0, 0 };
	int ids[MAX_TEXTURES] = { 0, 1, 2, 3, 4, 5, 6, 7 };

	shaderProgram->Update(shadowUniforms.colorTextureEnabled, booleans, MAX_TEXTURES);
	shaderProgram->Update(shadowUniforms.colorTexture, ids, MAX_TEXTURES);

	//Update Texture Coordinates
	ShaderProgram::FloatVec2 textureOffset;
	textureOffset.vec[0] = mesh.textureOffset[0];
	textureOffset.vec[1] = mesh.textureOffset[1];
	shaderProgram->Update(shadowUniforms.textureOffset, textureOffset);

	ShaderProgram::FloatVec2 textureScale;
	textureScale.vec[0] = mesh.textureScale[0];
	textureScale.vec[1] = mesh.textureScale[1];
	shaderProgram->Update(shadowUniforms.textureScale, textureScale);

	shaderProgram->SetActiveTexture(0);
	shaderProgram->BindTexture(texture.textureArray[0]);

	for (unsigned i = 0; i < text.length(); ++i) {

		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = GraphicsManager::GetInstance().projectionStack.Top() * GraphicsManager::GetInstance().viewStack.Top() * GraphicsManager::GetInstance().modelStack.Top() * characterSpacing;
		shaderProgram->Update(shadowUniforms.modelViewProjection, false, ToOpenglStruct(MVP));

		mesh.Render((unsigned)text[i] * 6, 6);

	}
	shaderProgram->UnbindTexture();
	shaderProgram->Update(shadowUniforms.textEnabled, false);

}

void RenderMeshDelegate(Mesh& mesh, Texture& texture, const bool& enableLight, const RenderHelper::ShadowUniforms& shadowUniforms) {

	ShaderProgram* shaderProgram = GetShader();

	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = GraphicsManager::GetInstance().projectionStack.Top() * GraphicsManager::GetInstance().viewStack.Top() * GraphicsManager::GetInstance().modelStack.Top();

	shaderProgram->Update(shadowUniforms.modelViewProjection, false, ToOpenglStruct(MVP));
	modelView = GraphicsManager::GetInstance().viewStack.Top() * GraphicsManager::GetInstance().modelStack.Top();
	shaderProgram->Update(shadowUniforms.modelView, false, ToOpenglStruct(modelView));
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	shaderProgram->Update(shadowUniforms.modelViewInverseTranspose, false, ToOpenglStruct(modelView_inverse_transpose));

	shaderProgram->Update(shadowUniforms.lightEnabled, enableLight);

	//Update Texture Coordinates
	ShaderProgram::FloatVec2 textureOffset;
	textureOffset.vec[0] = mesh.textureOffset[0];
	textureOffset.vec[1] = mesh.textureOffset[1];
	shaderProgram->Update(shadowUniforms.textureOffset, textureOffset);

	ShaderProgram::FloatVec2 textureScale;
	textureScale.vec[0] = mesh.textureScale[0];
	textureScale.vec[1] = mesh.textureScale[1];
	shaderProgram->Update(shadowUniforms.textureScale, textureScale);

	if (enableLight) {

		//Load Material
		shaderProgram->Update(shadowUniforms.ambient, ToOpenglStruct(mesh.material.kAmbient));
		shaderProgram->Update(shadowUniforms.diffuse, ToOpenglStruct(mesh.material.kDiffuse));
		shaderProgram->Update(shadowUniforms.specular, ToOpenglStruct(mesh.material.kSpecular));
		shaderProgram->Update(shadowUniforms.shininess, mesh.material.kShininess);

	}

	int booleans[MAX_TEXTURES];
	unsigned ids[MAX_TEXTURES] = {0, 1, 2, 3, 4, 5, 6, 7};

	for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {

		if (texture.textureArray[i] > 0) {

			shaderProgram->SetActiveTexture(i);
			shaderProgram->BindTexture(texture.textureArray[i]);
			booleans[i] = true;

		}
		else {

			booleans[i] = false;

		}

		shaderProgram->Update(shadowUniforms.colorTexture, ids, MAX_TEXTURES);
		shaderProgram->Update(shadowUniforms.colorTextureEnabled, booleans, MAX_TEXTURES);

	}

	mesh.Render();

	for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {

		if (texture.textureArray[i] > 0) {

			shaderProgram->UnbindTexture();

		}

	}

}

RenderHelper::RenderHelper() {

	refreshUniforms = true;

}

RenderHelper::~RenderHelper() {
}

void RenderHelper::Update() {

	refreshUniforms = true;

}

void RenderHelper::LoadShadowShader() {

	if (!GraphicsManager::GetInstance().HasShader("Shadow")) {
		GraphicsManager::GetInstance().AddShader("Shadow", "Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
		GraphicsManager::GetInstance().SetActiveShader("Shadow");
		ShaderProgram* shaderProgram = GraphicsManager::GetInstance().GetActiveShader();

		shadowUniforms.modelView = shaderProgram->GetUniformID("MV");
		shadowUniforms.modelViewProjection = shaderProgram->GetUniformID("MVP");
		shadowUniforms.modelViewInverseTranspose = shaderProgram->GetUniformID("MV_inverse_transpose");
		shadowUniforms.ambient = shaderProgram->GetUniformID("material.kAmbient");
		shadowUniforms.diffuse = shaderProgram->GetUniformID("material.kDiffuse");
		shadowUniforms.specular = shaderProgram->GetUniformID("material.kSpecular");
		shadowUniforms.shininess = shaderProgram->GetUniformID("material.kShininess");
		shadowUniforms.colorTextureEnabled = shaderProgram->GetUniformID("colorTextureEnabled");
		shadowUniforms.colorTexture = shaderProgram->GetUniformID("colorTexture");
		shadowUniforms.textColor = shaderProgram->GetUniformID("textColor");
		shadowUniforms.textEnabled = shaderProgram->GetUniformID("textEnabled");
		shadowUniforms.numLights = shaderProgram->GetUniformID("numLights");
		shadowUniforms.lightEnabled = shaderProgram->GetUniformID("lightEnabled");
		shadowUniforms.fogEnabled = shaderProgram->GetUniformID("fogParam.enabled");
		shadowUniforms.alphaDiscardValue = shaderProgram->GetUniformID("alphaDiscardValue");
		shadowUniforms.textureOffset = shaderProgram->GetUniformID("textureOffset");
		shadowUniforms.textureScale = shaderProgram->GetUniformID("textureScale");
	} else {
		GraphicsManager::GetInstance().SetActiveShader("Shadow");
	}

	currentShader = SHADERS::SHADOW;

}

void RenderHelper::SetNumLights(const unsigned num) {

	switch (currentShader) {

	case SHADERS::SHADOW:
		SetNumLightsDelegate(num, shadowUniforms);
		break;

	}

}

void RenderHelper::EnableLight(const bool boolean) {

	switch (currentShader) {

	case SHADERS::SHADOW:
		EnableLightDelegate(boolean, shadowUniforms);
		break;

	}

}

void RenderHelper::EnableFog(const bool boolean) {

	switch (currentShader) {

	case SHADERS::SHADOW:
		EnableFogDelegate(boolean, shadowUniforms);
		break;

	}

}

void RenderHelper::SetAlphaDiscardValue(const float alphaValue) {

	switch (currentShader) {
		case SHADERS::SHADOW:
			GetShader()->Update(shadowUniforms.alphaDiscardValue, alphaValue);
			break;
	}

}

void RenderHelper::RenderMesh(Mesh& mesh, Texture& texture, const bool& enableLight) {

	switch (currentShader) {
		case SHADERS::SHADOW:
			RenderMeshDelegate(mesh, texture, enableLight, shadowUniforms);
			break;
	}

}

void RenderHelper::RenderMesh(Mesh& mesh, const bool& enableLight) {

	static Texture texture;
	RenderMesh(mesh, texture, enableLight);

}

void RenderHelper::RenderText(Mesh& mesh, Texture& texture, const string& text, Color color) {

	switch (currentShader) {
		case SHADERS::SHADOW:
			RenderTextDelegate(mesh, texture, text, color, shadowUniforms);
			break;
	}

}