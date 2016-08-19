#include "SceneBase.h"
#include "GraphicsManager.h"

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

	//Initialise the shader.
	if (!GraphicsManager::GetInstance().HasShader("Shadow")) {
		GraphicsManager::GetInstance().AddShader("Shadow", "Shader//Shadow.vertexshader", "Shader//Shadow.fragmentshader");
	}
	GraphicsManager::GetInstance().SetActiveShader("Shadow");

	//Update Shader Uniforms
	GraphicsManager::GetInstance().GetActiveShader()->UpdateBool("lightEnabled", false);
	GraphicsManager::GetInstance().GetActiveShader()->UpdateInt("numLights", 0);
	GraphicsManager::GetInstance().GetActiveShader()->UpdateBool("fogParam.enabled", false);
	GraphicsManager::GetInstance().GetActiveShader()->UpdateFloat("alphaDiscardValue", 0.1f);

}

void SceneBase::InitSawblades() {
}

void SceneBase::Update(const double& deltaTime) {
}

void SceneBase::Render() {
}

void SceneBase::Exit() {
}