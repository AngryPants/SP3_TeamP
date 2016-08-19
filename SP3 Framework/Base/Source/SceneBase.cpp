#include "SceneBase.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

SceneBase::SceneBase(const string& name) : Scene(name) {
	
	hero = nullptr;

}

SceneBase::~SceneBase() {
}

void SceneBase::Init() {

	minFPS = 30.0;
	hero = nullptr;

	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	InitShader();

}

void SceneBase::InitShader() {

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader<SHADERS::SHADOW>();
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);

}

void SceneBase::InitSawblades() {
}

void SceneBase::Update(const double& deltaTime) {
}

void SceneBase::Render() {
}

void SceneBase::Exit() {
}