#include "SceneCredits.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "GameManager.h"
#include "AudioManager.h"

SceneCredits::SceneCredits(const string& name) : Scene(name)
{
	bgm = "";
}

SceneCredits::~SceneCredits()
{
}

void SceneCredits::Init()
{
	mesh = MeshBuilder::GetInstance().GenerateQuad("Quad", Color(0, 0, 0), 1.f);
	texture.textureArray[0] = TextureManager::GetInstance().AddTexture("credits", "Image//Cyborg_Shooter//Backgrounds//Background_Credits.tga");

	AudioManager::GetInstance().PlayAudio2D(bgm, true, 0.5f);
	isKeyDown = true;

}

void SceneCredits::Update(const double &deltaTime)
{
	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT] == false) {
		isKeyDown = false;
	}

	if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT] && !isKeyDown) {
		isKeyDown = true;
		SceneManager::GetInstance().RemoveScene(name);
		GameManager::GetInstance().GoToScene("Main_Menu");
	}
}

void SceneCredits::Render()
{
	MS &modelStack = GraphicsManager::GetInstance().modelStack;

	GraphicsManager::GetInstance().SetToHUD(-50, 50, -50, 50, -50, 50);
	modelStack.PushMatrix();
		modelStack.Scale(100, 100, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture, false);
	modelStack.PopMatrix();
}

void SceneCredits::Exit()
{
	AudioManager::GetInstance().ClearAudioList();
}