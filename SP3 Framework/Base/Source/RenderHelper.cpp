#include "RenderHelper.h"
#include "GraphicsManager.h"
#include <iostream>

using namespace std;

RenderHelper::RenderHelper() {

	refreshUniforms = true;

}

RenderHelper::~RenderHelper() {
}

void RenderHelper::Update() {

	refreshUniforms = true;

}

void RenderHelper::RenderMesh(Mesh& mesh, Texture& texture, const bool& enableLight) {

	ShaderProgram* shaderProgram = GraphicsManager::GetInstance().GetActiveShader();
	if (shaderProgram == nullptr) {
		cout << "Unable to render as no active shader has been set." << endl;
		return;
	}
	
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = GraphicsManager::GetInstance().projectionStack.Top() * GraphicsManager::GetInstance().viewStack.Top() * GraphicsManager::GetInstance().modelStack.Top();
	
	shaderProgram->UpdateFloatMatrix4x4("MVP", false, &MVP.a[0]);
	modelView = GraphicsManager::GetInstance().viewStack.Top() * GraphicsManager::GetInstance().modelStack.Top();
	shaderProgram->UpdateFloatMatrix4x4("MV", false, &modelView.a[0]);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	shaderProgram->UpdateFloatMatrix4x4("MV_inverse_transpose", false, &modelView_inverse_transpose.a[0]);

	shaderProgram->UpdateBool("lightEnabled", enableLight);
	
	if (enableLight) {
		//Load Material
		shaderProgram->UpdateFloatVector3("material.kAmbient", &mesh.material.kAmbient.r);
		shaderProgram->UpdateFloatVector3("material.kDiffuse", &mesh.material.kDiffuse.r);
		shaderProgram->UpdateFloatVector3("material.kSpecular", &mesh.material.kSpecular.r);
		shaderProgram->UpdateFloat("material.kShininess", mesh.material.kShininess);
	}

	for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
		if (texture.textureArray[i] > 0) {
			shaderProgram->UpdateBool("colorTextureEnabled[" + to_string(i) + "]", true);
			shaderProgram->SetActiveTexture(i);
			shaderProgram->BindTexture(texture.textureArray[i]);
			shaderProgram->UpdateBool("colorTexture[" + to_string(i) + "]", i);
		} else {
			shaderProgram->UpdateBool("colorTextureEnabled[" + to_string(i) + "]", false);
		}
	}

	mesh.Render();

	for (unsigned int i = 0; i < MAX_TEXTURES; ++i) {
		if (texture.textureArray[i] > 0) {
			shaderProgram->UnbindTexture();
		}
	}

}

void RenderHelper::RenderText(Mesh& mesh, Texture& texture, const string& text, Color color) {

	ShaderProgram* shaderProgram = GraphicsManager::GetInstance().GetActiveShader();
	if (shaderProgram == nullptr) {
		cout << "Unable to render as no active shader has been set." << endl;
		return;
	}

	shaderProgram->UpdateBool("textEnabled", true);
	shaderProgram->UpdateFloatVector3("textColor", &color.r);
	shaderProgram->UpdateBool("lightEnabled", true);
	shaderProgram->UpdateBool("colorTextureEnabled[0]", true);
	shaderProgram->SetActiveTexture(0);
	shaderProgram->BindTexture(texture.textureArray[0]);
	shaderProgram->UpdateBool("colorTexture[0]", false);
	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = GraphicsManager::GetInstance().projectionStack.Top() * GraphicsManager::GetInstance().viewStack.Top() * GraphicsManager::GetInstance().modelStack.Top() * characterSpacing;
		shaderProgram->UpdateFloatMatrix4x4("MVP", false, &MVP.a[0]);
		
		mesh.Render((unsigned)text[i] * 6, 6);
	}
	shaderProgram->UnbindTexture();
	shaderProgram->UpdateBool("textEnabled", false);
	
}