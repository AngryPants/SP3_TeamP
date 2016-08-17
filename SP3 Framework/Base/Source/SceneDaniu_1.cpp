#include "SceneDaniu_1.h"
#include "EntityManager.h"
#include "AudioManager.h"
#include "GraphicsManager.h"
#include "Kifellah.h"

SceneDaniu_1::SceneDaniu_1() : SceneBase ("Daniu Level 1") {
}

SceneDaniu_1::~SceneDaniu_1() {
}

void SceneDaniu_1::Init() {

	SceneBase::Init();

	hero = new Kifellah();
	EntityManager::GetInstance().AddEntity(name, *hero);

	camera.SetFollowTarget(*hero);
	//EntityManager::GetInstance().AddEntity(name, camera);

}

void SceneDaniu_1::Update(const double& deltaTime) {

	double frameTime = deltaTime;
	if (frameTime > 1.0 / minFPS) {
		frameTime = 1.0 / minFPS;
	}

	EntityManager::GetInstance().Update(name, frameTime);

}

void SceneDaniu_1::Render() {

	GraphicsManager::GetInstance().Update();
	GraphicsManager::GetInstance().SetToCameraView(camera);
	EntityManager::GetInstance().Render(this->name);
	EntityManager::GetInstance().RenderUI(this->name);

}

void SceneDaniu_1::Exit() {
}