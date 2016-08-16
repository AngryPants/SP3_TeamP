#include "SceneBase.h"
#include "GraphicsManager.h"

void SceneBase::Initialise() {

	GraphicsManager::GetInstance().AddShader("Shadow", "Shadow.vertexshader", "Shadow.fragmentshader");

}

void SceneBase::Update(const double& deltaTime) {
}

void SceneBase::Render() {
}

void SceneBase::Exit() {
}