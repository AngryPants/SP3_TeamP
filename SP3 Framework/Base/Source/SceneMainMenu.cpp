#include "SceneMainMenu.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "SceneDaniu_1.h"

SceneMainMenu::SceneMainMenu() : Scene("Main Menu")
{

}

SceneMainMenu::~SceneMainMenu()
{

}

void SceneMainMenu::Init()
{
	pointerPositionY = 3.5f;
	menuChange = false;

	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader<SHADERS::SHADOW>();
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);

	mainmenu.MainMenuInit();

	mesh = MeshBuilder::GetInstance().GenerateQuad("StartGame", Color(0, 0, 0), 1.f);
	// Pointer Texture
	texture[MENUGUI_MENU_POINTER].textureArray[0] = TextureManager::GetInstance().AddTexture("Buttons", "Image//Cyborg_Shooter//Buttons//ButtonRight_Select.tga");

	// Title and background
	texture[MENUGUI_TITLE].textureArray[0] = TextureManager::GetInstance().AddTexture("Title", "Image//Cyborg_Shooter//Others//DawnOfCyborgs.tga");
	texture[MENUGUI_BACKGROUND].textureArray[0] = TextureManager::GetInstance().AddTexture("Menu Background", "Image//Cyborg_Shooter//Tiles//Terrain//Terrain_Wall_2.tga");

	// Volume Graphics
	texture[MENUGUI_VOLUMEICON].textureArray[0] = TextureManager::GetInstance().AddTexture("VolumeUpDown", "Image//Cyborg_Shooter//Buttons//Button_Mute.tga");
	texture[MENUGUI_VOLUMEPLUS].textureArray[0] = TextureManager::GetInstance().AddTexture("Muted Volume", "Image//Cyborg_Shooter//Buttons//Button_Plus.tga");
	texture[MENUGUI_VOLUMEMINUS].textureArray[0] = TextureManager::GetInstance().AddTexture("Max Volume", "Image//Cyborg_Shooter//Buttons//Button_Minus.tga");

	// All the options avilable for choosing
	texture[MENUGUI_OPTION_ONE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option One", "Image//Cyborg_Shooter//MenuUI//New_Game.tga");
	texture[MENUGUI_OPTION_TWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Two", "Image//Cyborg_Shooter//MenuUI//Continue_Game.tga");
	texture[MENUGUI_OPTION_THREE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Three", "Image//Cyborg_Shooter//MenuUI//Option.tga");
	texture[MENUGUI_OPTION_FOUR].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Four", "Image//Cyborg_Shooter//MenuUI//How_To_Play.tga");
	texture[MENUGUI_OPTION_FIVE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Five", "Image//Cyborg_Shooter//MenuUI//Quit.tga");


	camera = new Camera("Camera", name);
	camera->SetPosition(Vector3(0, 0, 1));
	camera->SetTarget(Vector3(0, 0, 0));
	camera->SetUp(Vector3(0, 1, 0));
	camera->aspectRatio.Set(1024, 800);
	camera->SetOrtho();
	camera->SetFarClippingPlane(100);
	camera->SetNearClippingPlane(-100);
	camera->SetOrthoSize(9);
}

bool SceneMainMenu::InTransition()
{
	if (menuChange)
	{
		// From Main menu to options
		if (mainmenu.menu == MainMenu::MENU::MENU_OPTION && mainmenu.option == MainMenu::OPTION::OPTION_MAINOPTION)
		{
			texture[MENUGUI_OPTION_ONE].textureArray[0] = TextureManager::GetInstance().AddTexture("Volume", "Image//Cyborg_Shooter//MenuUI//Volume.tga");
			texture[MENUGUI_OPTION_TWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Erase Data", "Image//Cyborg_Shooter//MenuUI//Erase_Data.tga");
			texture[MENUGUI_OPTION_THREE].textureArray[0] = TextureManager::GetInstance().AddTexture("Back", "Image//Cyborg_Shooter//MenuUI//Back.tga");
		}

		// From Options to Main Menu
		if (mainmenu.menu == MainMenu::MENU::MENU_OPTION && mainmenu.option == MainMenu::OPTION::OPTION_BACK)
		{
			texture[MENUGUI_OPTION_ONE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option One", "Image//Cyborg_Shooter//MenuUI//New_Game.tga");
			texture[MENUGUI_OPTION_TWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Two", "Image//Cyborg_Shooter//MenuUI//Continue_Game.tga");
			texture[MENUGUI_OPTION_THREE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Three", "Image//Cyborg_Shooter//MenuUI//Option.tga");
		}
		menuChange = false;
	}
	return false;
}

void SceneMainMenu::PointerPositionUpdate()
{
	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_SELECT])
		menuChange = true;


	if (mainmenu.option == MainMenu::OPTION::OPTION_BACK)
	{
		pointerPositionY = 3.5f;
		menuChange = true;
	}
}

void SceneMainMenu::Update(const double &deltaTime)
{
	if (mainmenu.menu == MainMenu::MENU::MENU_NEWGAME)
	{
		if (!SceneManager::GetInstance().CheckSceneExist("Daniu Level 1"))
		{
			new  SceneDaniu_1();
		}
		SceneManager::GetInstance().SetActiveScene("Daniu Level 1");
	}

	PointerPositionUpdate();
	mainmenu.MainMenuUpdate(deltaTime);
	//if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_SELECT])
	//{
	//	if (!SceneManager::GetInstance().CheckSceneExist("Daniu Level 1"))
	//	{
	//		new  SceneDaniu_1();
	//	}
	//	SceneManager::GetInstance().SetActiveScene("Daniu Level 1");
	//}
}

void SceneMainMenu::Render()
{
	GraphicsManager::GetInstance().Update();
	GraphicsManager::GetInstance().SetToCameraView(*camera);
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();
	EntityManager::GetInstance().Render(this->name);
	RenderMenuChoice();
	RenderMenuPointer();

	GraphicsManager::GetInstance().SetToHUD(-50, 50, -50, 50, -50, 50);
	GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::DEPTH_TEST>();
	EntityManager::GetInstance().RenderUI(this->name);
}

void SceneMainMenu::RenderMenuPointer()
{
	MS &modelStack = GraphicsManager::GetInstance().modelStack;

	if (!InTransition())
	{
		if (mainmenu.option != MainMenu::OPTION::OPTION_VOLUME)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-4.f, pointerPositionY - mainmenu.chooseMenu * 2.f, 1);
			modelStack.Scale(1.f, 1.f, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MENU_POINTER], false);
			modelStack.PopMatrix();
		}
	}
}

void SceneMainMenu::RenderMenuChoice() {

	float scale = 8;
	float translateX = 1;
	MS &modelStack = GraphicsManager::GetInstance().modelStack;

	modelStack.PushMatrix();
		modelStack.Translate(0, 0, -1);
		modelStack.Scale(25, 20, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_BACKGROUND], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
		modelStack.Translate(0, 5, 0);
		modelStack.Scale(17, 17, 1);
		RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TITLE], false);
	modelStack.PopMatrix();

	if (!InTransition())
	{
		if (mainmenu.menu == MainMenu::MENU::MENU_MAINMENU)
		{
			modelStack.PushMatrix();
				modelStack.Translate(translateX, 1.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_ONE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(translateX, -0.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_TWO], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(translateX, -2.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_THREE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(translateX, -4.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_FOUR], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(translateX, -6.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_FIVE], false);
			modelStack.PopMatrix();
		}

		if (mainmenu.menu == MainMenu::MENU::MENU_OPTION && mainmenu.option == MainMenu::OPTION::OPTION_MAINOPTION)
		{
			modelStack.PushMatrix();
				modelStack.Translate(translateX, 1.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_ONE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(translateX, -0.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_TWO], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(translateX, -2.5, 0);
				modelStack.Scale(scale, scale, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_THREE], false);
			modelStack.PopMatrix();
		}

		if (mainmenu.menu == MainMenu::MENU::MENU_OPTION && mainmenu.option == MainMenu::OPTION::OPTION_VOLUME)
		{
			modelStack.PushMatrix();
				modelStack.Translate(-5.f, 0, 0);
				modelStack.Scale(2, 2, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_VOLUMEMINUS], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(5.f, 0, 0);
				modelStack.Scale(2, 2, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_VOLUMEPLUS], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate((mainmenu.volume * 6) - 3, 0, 0);
			modelStack.Scale(2, 2, 2);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_VOLUMEICON], false);
			modelStack.PopMatrix();
		}
	}
}

void SceneMainMenu::Exit()
{

}