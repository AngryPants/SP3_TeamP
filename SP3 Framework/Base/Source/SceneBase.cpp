#include "SceneBase.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "EntityManager.h"

SceneBase::SceneBase(const string& name) : Scene(name) {
	//hero = nullptr;
	camera = nullptr;
}

SceneBase::~SceneBase() {
}

void SceneBase::Init() {

	minFPS = 30.0;

	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	InitShader();

	background = MeshBuilder::GetInstance().GenerateQuad("Background");
	backgroundTextures[BACKGROUND_REAR].textureArray[0] = TextureManager::GetInstance().AddTexture("Background Rear", "Image//Cyborg_Shooter//Backgrounds//Background_Rear.tga");

}

void SceneBase::InitShader() {

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader<SHADERS::SHADOW>();
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);
	
}

void SceneBase::Update(const double& deltaTime) {
}

void SceneBase::Render() {
}

void SceneBase::RenderBackground() {

	Vector3 backgroundPosition = camera->GetPosition();

	MS& modelStack = GraphicsManager::GetInstance().modelStack;
	modelStack.PushMatrix();
		modelStack.Translate(backgroundPosition.x, backgroundPosition.y, -30);
		modelStack.Scale(camera->GetOrthoWidth() * 2.0f, camera->GetOrthoSize() * 2.0f, 1);
		background->SetTextureOffset(0, 0);
		RenderHelper::GetInstance().RenderMesh(*background, backgroundTextures[BACKGROUND_REAR], false);
	modelStack.PopMatrix();
	
}

void SceneBase::Exit() {

	//GameManager::GetInstance().ClearScene(name);
	EntityManager::GetInstance().DestroyScene(name);	

}