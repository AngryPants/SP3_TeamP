#include "SceneBase.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"

SceneBase::SceneBase(const string& name)
:
Scene(name),
gameManager(name) {
	
	hero = nullptr;
	debugMode = false;

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

	if (debugMode) {
		if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_WIREFRAME_OFF]) {
			GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::WIREFRAME>();
			cout << "Wireframe Mode On" << endl;
		} else if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_WIREFRAME_ON]) {
			GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::WIREFRAME>();
			cout << "Wireframe Mode Off" << endl;
		}
	}

}

void SceneBase::Render() {
}

void SceneBase::Exit() {
}