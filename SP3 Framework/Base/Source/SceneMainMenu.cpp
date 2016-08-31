#include "SceneMainMenu.h"
#include "InputManager.h"
#include "GraphicsManager.h"
#include "RenderHelper.h"
#include "MeshBuilder.h"
#include "TextureManager.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "AudioManager.h"

SceneMainMenu::SceneMainMenu(const string& name) : Scene(name)
{
	bgm = "";
}

SceneMainMenu::~SceneMainMenu()
{

}

void SceneMainMenu::Init()
{
	mainmenu.MainMenuInit();

	defaultPointerPositionY = 3.5f;
	pointerPositionY = defaultPointerPositionY;
	defaultPointerPositionX = -4.f;
	pointerPositionX = defaultPointerPositionX;
	menuChange = false;

	GraphicsManager::GetInstance().SetBackgroundColor(0, 0, 0, 0);
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::BLENDING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::CULLING>();
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();

	//Initialise the Shader.
	RenderHelper::GetInstance().LoadShader<SHADERS::SHADOW>();
	RenderHelper::GetInstance().EnableLight(false);
	RenderHelper::GetInstance().SetNumLights(0);
	RenderHelper::GetInstance().EnableFog(false);
	RenderHelper::GetInstance().SetAlphaDiscardValue(0.1f);

	mesh = MeshBuilder::GetInstance().GenerateQuad("StartGame", Color(0, 0, 0), 1.f);
	textOnScreenMesh = MeshBuilder::GetInstance().GenerateText("Text", 16, 16);
	// Pointer Texture
	texture[MENUGUI_MENU_POINTER].textureArray[0] = TextureManager::GetInstance().AddTexture("Buttons", "Image//Cyborg_Shooter//Buttons//ButtonRight_Select.tga");
	texture[MENUGUI_MENU_BUTTONLEFT].textureArray[0] = TextureManager::GetInstance().AddTexture("Button Left", "Image//Cyborg_Shooter//Buttons//ButtonLeft.tga");
	texture[MENUGUI_MENU_BUTTONRIGHT].textureArray[0] = TextureManager::GetInstance().AddTexture("Button Right", "Image//Cyborg_Shooter//Buttons//ButtonRight.tga");

	// Title and background
	texture[MENUGUI_TITLE].textureArray[0] = TextureManager::GetInstance().AddTexture("Title", "Image//Cyborg_Shooter//Others//DawnOfCyborgs.tga");
	texture[MENUGUI_BACKGROUNDONE].textureArray[0] = TextureManager::GetInstance().AddTexture("Menu Background One", "Image//Cyborg_Shooter//Tiles//Terrain//Terrain_Wall_2.tga");
	texture[MENUGUI_BACKGROUNDTWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Menu Background Two", "Image//Cyborg_Shooter//Tiles//Terrain//Terrain_Wall_3.tga");

	// Volume Graphics
	texture[MENUGUI_VOLUMEICON].textureArray[0] = TextureManager::GetInstance().AddTexture("VolumeUpDown", "Image//Cyborg_Shooter//Buttons//Button_Mute.tga");
	texture[MENUGUI_VOLUMEPLUS].textureArray[0] = TextureManager::GetInstance().AddTexture("Muted Volume", "Image//Cyborg_Shooter//Buttons//Button_Plus.tga");
	texture[MENUGUI_VOLUMEMINUS].textureArray[0] = TextureManager::GetInstance().AddTexture("Max Volume", "Image//Cyborg_Shooter//Buttons//Button_Minus.tga");

	// All the options avilable for choosing
	texture[MENUGUI_MAIN_ONE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option One", "Image//Cyborg_Shooter//MenuUI//New_Game.tga");
	texture[MENUGUI_MAIN_TWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Two", "Image//Cyborg_Shooter//MenuUI//Continue_Game.tga");
	texture[MENUGUI_MAIN_THREE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Three", "Image//Cyborg_Shooter//MenuUI//Option.tga");
	texture[MENUGUI_MAIN_FOUR].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Four", "Image//Cyborg_Shooter//MenuUI//How_To_Play.tga");
	texture[MENUGUI_MAIN_FIVE].textureArray[0] = TextureManager::GetInstance().AddTexture("Option Five", "Image//Cyborg_Shooter//MenuUI//Quit.tga");

	texture[MENUGUI_OPTION_ONE].textureArray[0] = TextureManager::GetInstance().AddTexture("High Score", "Image//Cyborg_Shooter//MenuUI//HighScore.tga");
	texture[MENUGUI_OPTION_TWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Erase Data", "Image//Cyborg_Shooter//MenuUI//Erase_Data.tga");
	texture[MENUGUI_OPTION_THREE].textureArray[0] = TextureManager::GetInstance().AddTexture("Back", "Image//Cyborg_Shooter//MenuUI//Back.tga");

	texture[MENUGUI_CONTINUEGAME_DISPLAY].textureArray[0] = TextureManager::GetInstance().AddTexture("Display", "Image//Cyborg_Shooter//MenuUI//ChooseLevel.tga");
	texture[MENUGUI_CONTINUEGAME_OPTIONS].textureArray[0] = TextureManager::GetInstance().AddTexture("Level 1", "Image//Cyborg_Shooter//MenuUI//Level1.tga");

	texture[MENUGUI_DELETEFILE_ONE].textureArray[0] = TextureManager::GetInstance().AddTexture("Delete Prompt", "Image//Cyborg_Shooter//MenuUI//SaveFileDetection.tga");
	texture[MENUGUI_DELETEFILE_TWO].textureArray[0] = TextureManager::GetInstance().AddTexture("Ask to delete", "Image//Cyborg_Shooter//MenuUI//DeletePrompt.tga");
	texture[MENUGUI_TWOCHOICE_YES].textureArray[0] = TextureManager::GetInstance().AddTexture("Yes", "Image//Cyborg_Shooter//Others//Yes.tga");
	texture[MENUGUI_TWOCHOICE_NO].textureArray[0] = TextureManager::GetInstance().AddTexture("No", "Image//Cyborg_Shooter//Others//No.tga");
	texture[MENUGUI_BACKTOMAIN].textureArray[0] = TextureManager::GetInstance().AddTexture("Back To Main", "Image//Cyborg_Shooter//Others//BackToMain.tga");
	texture[MENUGUI_TEXTSCREEN].textureArray[0] = TextureManager::GetInstance().AddTexture("TextScreen", "Image//Cyborg_Shooter//Others//TextScreen.tga");
	texture[MENUGUI_HOWTOPLAY_PAGEONE].textureArray[0] = TextureManager::GetInstance().AddTexture("HowToPageOne", "Image//Cyborg_Shooter//MenuUI//KeyboardControls.tga");
	texture[MENUGUI_HOWTOPLAY_PAGETWO].textureArray[0] = TextureManager::GetInstance().AddTexture("HowToPageTwo", "Image//Cyborg_Shooter//MenuUI//GamePadControls.tga");

	texture[MENUGUI_TEXTONSCREEN].textureArray[0] = TextureManager::GetInstance().AddTexture("Text On Screen", "Image//Fonts//Consolas.tga");
	texture[MENUGUI_HIGHSCORE].textureArray[0] = TextureManager::GetInstance().AddTexture("High score", "Image//Cyborg_Shooter//Others//Highscore.tga");

	camera = new CameraMainMenu(name);
	camera->SetPosition(Vector3(0, 0, 0));
	camera->SetYaw(180);
	camera->aspectRatio.Set(1024, 800);
	camera->SetOrtho();
	camera->SetFarClippingPlane(100);
	camera->SetNearClippingPlane(-200);
	camera->SetOrthoSize(9);

	//AudioManager::GetInstance().PlayAudio2D(bgm, true, 0.5f);
}

void SceneMainMenu::UpdateInTransition(const double &deltaTime)
{
	if (mainmenu.transitionInProgress)
	{
		// All menu transitions
		if (mainmenu.menu == MainMenu::MENU::MENU_OPTION)
		{
			camera->Pitch(90.f * (float)deltaTime);

			if (camera->GetRotation().x > 90)
			{
				camera->SetPitch(90);
				mainmenu.transitionInProgress = false;
			}
		}

		if (mainmenu.menu == MainMenu::MENU::MENU_HOWTOPLAY)
		{
			camera->Pitch(-90.f * (float)deltaTime);

			if (camera->GetRotation().x < -90.f)
			{
				camera->SetPitch(-90);
				mainmenu.howtoplay = MainMenu::HOWTOPLAY::HOWTOPLAY_MAINHOWTOPLAY;
				mainmenu.transitionInProgress = false;
			}
		}

		if (mainmenu.option == MainMenu::OPTION::OPTION_BACK)
		{
			camera->Pitch(-90.f * (float)deltaTime);

			if (camera->GetRotation().x < 0.f)
			{
				camera->SetPitch(0);
				mainmenu.option = MainMenu::OPTION::OPTION_MAINOPTION;
				mainmenu.transitionInProgress = false;
			}
		}

		if (mainmenu.howtoplay == MainMenu::HOWTOPLAY::HOWTOPLAY_BACK)
		{
			camera->Pitch(90.f * (float)deltaTime);

			if (camera->GetRotation().x > 0.f)
			{
				camera->SetPitch(0.f);
				mainmenu.howtoplay = MainMenu::HOWTOPLAY::HOWTOPLAY_MAINHOWTOPLAY;
				mainmenu.transitionInProgress = false;
			}
		}
	}
}

void SceneMainMenu::UpdateContinueGameToScene()
{
	if (mainmenu.menu == MainMenu::MENU::MENU_CONTINUEGAME)
	{
		GameManager::GetInstance().GoToScene(GameData::GetInstance().GetCurrentLevel());
		std::cout << "I'm here" << std::endl;
	}

}

void SceneMainMenu::PointerPositionUpdate()
{
	if (!mainmenu.transitionInProgress)
	{
		if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_SELECT])
			menuChange = true;

		pointerPositionY = defaultPointerPositionY;
		pointerPositionX = defaultPointerPositionX;

		if (mainmenu.option == MainMenu::OPTION::OPTION_BACK)
		{
			pointerPositionY = defaultPointerPositionY;
			menuChange = true;
		}

		if (mainmenu.option == MainMenu::OPTION::OPTION_ERASEDATA)
		{
			pointerPositionX = -10;
			pointerPositionY = 1;
		}

		if (mainmenu.menu == MainMenu::MENU::MENU_NEWGAME)
		{
			if (mainmenu.hasSavedFile)
			{
				pointerPositionY = -4.5f;
				pointerPositionX = -10.f;
			}
		}
	}
}

void SceneMainMenu::DeleteSaveFileOrNot()
{
	if (mainmenu.menu == MainMenu::MENU::MENU_NEWGAME)
	{
		if (mainmenu.hasSavedFile)
		{
			if (mainmenu.deletingFile == true)
			{
				GameManager::GetInstance().GoToScene("Level_1");
				std::cout << "I'm here" << std::endl;
				mainmenu.deletingFile = false;
			}
		}

		else
		{
			GameManager::GetInstance().GoToScene("Level_1");
			std::cout << "I'm here too" << std::endl;
		}
	}

	if (mainmenu.menu == MainMenu::MENU::MENU_OPTION && mainmenu.option == MainMenu::OPTION::OPTION_ERASEDATA)
	{
		if (mainmenu.hasSavedFile)
		{
			if (mainmenu.deletingFile == true)
			{
				GameData::GetInstance().DeleteGameData("SaveFile//DataOne.txt");
				std::cout << "File deleted" << std::endl;
				mainmenu.option = MainMenu::OPTION::OPTION_MAINOPTION;
				mainmenu.deletingFile = false;
				mainmenu.hasSavedFile = false;
			}
		}
	}
}

void SceneMainMenu::Update(const double &deltaTime)
{
	PointerPositionUpdate();
	mainmenu.MainMenuUpdate(deltaTime);
	DeleteSaveFileOrNot();
	UpdateContinueGameToScene();
	EntityManager::GetInstance().Update(name, deltaTime);
	UpdateInTransition(deltaTime);
}

void SceneMainMenu::Render()
{
	GraphicsManager::GetInstance().Update();
	GraphicsManager::GetInstance().SetToCameraView(*camera);
	GraphicsManager::GetInstance().Enable<GraphicsManager::MODE::DEPTH_TEST>();
	EntityManager::GetInstance().Render(this->name);
	RenderMenuPointer();
	RenderMenuChoice();

	GraphicsManager::GetInstance().SetToHUD(-50, 50, -50, 50, -50, 50);
	GraphicsManager::GetInstance().Disable<GraphicsManager::MODE::DEPTH_TEST>();
	EntityManager::GetInstance().RenderUI(this->name);
	RenderHighScore();
	RenderHowToPlayChoice(mainmenu.chooseMenu);
}

void SceneMainMenu::RenderMenuPointer()
{
	MS &modelStack = GraphicsManager::GetInstance().modelStack;

	if (!mainmenu.transitionInProgress)
	{
		switch (mainmenu.menu)
		{
		case MainMenu::MENU::MENU_MAINMENU:
			modelStack.PushMatrix();
			modelStack.Translate(pointerPositionX, pointerPositionY - mainmenu.chooseMenu * 2.f, 1);
			modelStack.Scale(1.f, 1.f, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MENU_POINTER], false);
			modelStack.PopMatrix();
			break;

		case MainMenu::MENU::MENU_NEWGAME:
		{
			if (mainmenu.hasSavedFile)
			{
				modelStack.PushMatrix();
				modelStack.Translate(pointerPositionX + mainmenu.chooseMenu * 6.f, pointerPositionY, 1);
				modelStack.Scale(1.f, 1.f, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MENU_POINTER], false);
				modelStack.PopMatrix();
			}
		}
		break;

		case MainMenu::MENU::MENU_CONTINUEGAME:
			break;

		case MainMenu::MENU::MENU_OPTION:
		{
			switch (mainmenu.option)
			{
			case MainMenu::OPTION::OPTION_MAINOPTION:
				modelStack.PushMatrix();
				modelStack.Translate(-4.f, pointerPositionY, pointerPositionX + mainmenu.chooseMenu * 2.f);
				modelStack.Rotate(-90, 1, 0, 0);
				modelStack.Scale(1.f, 1.f, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MENU_POINTER], false);
				modelStack.PopMatrix();
				break;

			case MainMenu::OPTION::OPTION_HIGHSCORE:
				break;

			case MainMenu::OPTION::OPTION_ERASEDATA:
			{
				modelStack.PushMatrix();
				modelStack.Translate(pointerPositionX + mainmenu.chooseMenu * 6.f, 1, pointerPositionY);
				modelStack.Rotate(-90, 1, 0, 0);
				modelStack.Scale(1.f, 1.f, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MENU_POINTER], false);
				modelStack.PopMatrix();

			}
			break;

			case MainMenu::OPTION::OPTION_BACK:
				break;
			}
		}
		break;

		case MainMenu::MENU::MENU_HOWTOPLAY:
			break;

		case MainMenu::MENU::MENU_QUIT:
			break;
		}
	}
}

void SceneMainMenu::RenderMenuChoice() {

	float scale = 8;
	float translateX = 1;
	MS &modelStack = GraphicsManager::GetInstance().modelStack;

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -10);
	modelStack.Scale(25, 20, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_BACKGROUNDONE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 10, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(25, 20, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TEXTSCREEN], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -10, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(25, 20, 1);
	RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_BACKGROUNDTWO], false);
	modelStack.PopMatrix();

	if (!mainmenu.transitionInProgress)
	{
		switch (mainmenu.menu)
		{
		case MainMenu::MENU::MENU_MAINMENU:
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, 5, 0);
			modelStack.Scale(17, 17, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TITLE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(translateX, 1.5, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MAIN_ONE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(translateX, -0.5, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MAIN_TWO], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(translateX, -2.5, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MAIN_THREE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(translateX, -4.5, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MAIN_FOUR], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(translateX, -6.5, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_MAIN_FIVE], false);
			modelStack.PopMatrix();
		}
		break;

		case MainMenu::MENU::MENU_NEWGAME:
		{
			if (mainmenu.hasSavedFile)
			{
				modelStack.PushMatrix();
				modelStack.Translate(1.5f, 0.5f, 0);
				modelStack.PushMatrix();
				modelStack.Translate(0.f, -2.5f, 0);
				modelStack.Scale(7, 7, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_DELETEFILE_TWO], false);
				modelStack.PopMatrix();
				modelStack.Scale(10, 10, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_DELETEFILE_ONE], false);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				modelStack.Translate(-0.f, -4.5f, 0);

				modelStack.PushMatrix();
				modelStack.Translate(6.f, 0, 0);
				modelStack.Scale(7, 7, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TWOCHOICE_NO], false);
				modelStack.PopMatrix();

				modelStack.Scale(7, 7, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TWOCHOICE_YES], false);
				modelStack.PopMatrix();

				modelStack.PushMatrix();
				modelStack.Translate(0.f, -2.f, -0.5f);
				modelStack.Scale(12, 9, 1);
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TEXTSCREEN], false);
				modelStack.PopMatrix();
			}
		}
		break;

		case MainMenu::MENU::MENU_CONTINUEGAME:
			break;

		case MainMenu::MENU::MENU_OPTION:
			RenderOptionChoice();
			break;

		case MainMenu::MENU::MENU_HOWTOPLAY:
			modelStack.PushMatrix();
			modelStack.Translate(0, 0, -7);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(8, 8, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_BACKTOMAIN], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0, 6.5f, 4);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(12, 12, 1);
			switch (mainmenu.chooseMenu)
			{
			default:
				break;

			case 1:
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_HOWTOPLAY_PAGEONE], false);
				break;

			case 2:
				RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_HOWTOPLAY_PAGETWO], false);
				break;
			}

			modelStack.PopMatrix();
			break;

		case MainMenu::MENU::MENU_QUIT:
			break;
		}
	}
}

void SceneMainMenu::RenderOptionChoice()
{
	float scale = 8;
	float translateZ = 2.f;

	MS &modelStack = GraphicsManager::GetInstance().modelStack;

	if (!mainmenu.transitionInProgress && !mainmenu.transitionInProgress)
	{
		switch (mainmenu.option)
		{
		case MainMenu::OPTION::OPTION_MAINOPTION:
		{
			modelStack.PushMatrix();
			modelStack.Translate(1, 3.5, -translateZ);

			modelStack.PushMatrix();
			modelStack.Translate(0, -0.5, translateZ);

			modelStack.PushMatrix();
			modelStack.Translate(0, -2.5, translateZ);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_THREE], false);
			modelStack.PopMatrix();

			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_TWO], false);
			modelStack.PopMatrix();

			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(scale, scale, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_OPTION_ONE], false);
			modelStack.PopMatrix();
		}
		break;

		case MainMenu::OPTION::OPTION_HIGHSCORE:
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, -0.5, 0);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(25, 20, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TEXTSCREEN], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0, 0, -5.f);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(10, 10, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_HIGHSCORE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0, 0, 5.f);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(7, 7, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_BACKTOMAIN], false);
			modelStack.PopMatrix();
		}
		break;

		case MainMenu::OPTION::OPTION_ERASEDATA:
		{
			modelStack.PushMatrix();
			modelStack.Translate(1.f, 0.5f, -3.f);

			modelStack.PushMatrix();
			modelStack.Translate(0.5f, 0.f, 2.f);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(6, 6, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_DELETEFILE_TWO], false);
			modelStack.PopMatrix();

			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(6, 6, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_DELETEFILE_ONE], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.5f, 1.f);

			modelStack.PushMatrix();
			modelStack.Translate(6.f, 0, 0);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(7, 7, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TWOCHOICE_NO], false);
			modelStack.PopMatrix();

			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(7, 7, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TWOCHOICE_YES], false);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
			modelStack.Translate(0.f, 0.f, -0.5f);
			modelStack.Rotate(-90, 1, 0, 0);
			modelStack.Scale(12, 9, 1);
			RenderHelper::GetInstance().RenderMesh(*mesh, texture[MENUGUI_TEXTSCREEN], false);
			modelStack.PopMatrix();
		}
		break;

		case MainMenu::OPTION::OPTION_BACK:
			break;
		}
	}
}

void SceneMainMenu::RenderHighScore()
{
	const map<string, int>& highscore = GameData::GetInstance().GetHighScores();

	MS &modelStack = GraphicsManager::GetInstance().modelStack;
	float initialTranslateY = 15.f;
	if (mainmenu.option == MainMenu::OPTION::OPTION_HIGHSCORE)
	{
		int count = 0;
		for (map<string, int>::const_iterator mapIter = highscore.begin(); mapIter != highscore.end(); ++mapIter)
		{
			modelStack.PushMatrix();
			//std::cout << mapIter->first << ": " << to_string(mapIter->second) << std::endl;
			modelStack.Translate(-21.f, initialTranslateY - static_cast<float>(count * 4), 0.f);
			modelStack.Scale(4, 4, 1);
			RenderHelper::GetInstance().RenderText(*textOnScreenMesh, texture[MENUGUI_TEXTONSCREEN], mapIter->first + ": " + to_string(mapIter->second), Color(1, 1, 1));
			modelStack.PopMatrix();
			++count;
		}
	}
}

void SceneMainMenu::RenderHowToPlayChoice(int chooseMenu)
{
	MS &modelStack = GraphicsManager::GetInstance().modelStack;
	std::vector<std::string> howToPlayText;
	float initialTranslateY = 15.f;

	if (mainmenu.menu == MainMenu::MENU::MENU_HOWTOPLAY && !mainmenu.transitionInProgress)
	{
		switch (chooseMenu)
		{
		default:
			break;

		case 1:
		{
			howToPlayText = mainmenu.TextFileToScreen("MenuFile//HowToPageOne.txt");
			modelStack.PushMatrix();
			float count = 2;

			modelStack.Translate(-37.5f, initialTranslateY, 0);
			modelStack.Scale(3.5, 3.5, 1);

			for (std::vector<std::string>::iterator it = howToPlayText.begin(); it != howToPlayText.end(); ++it)
			{
				modelStack.Translate(0, -count, 0);
				RenderHelper::GetInstance().RenderText(*textOnScreenMesh, texture[MENUGUI_TEXTONSCREEN], *it, Color(1, 1, 1));
			}

			modelStack.PopMatrix();
		}
		break;

		case 2:
		{
			howToPlayText = mainmenu.TextFileToScreen("MenuFile//HowToPageTwo.txt");
			modelStack.PushMatrix();
			float count = 2;
			modelStack.Translate(-37.5f, initialTranslateY, 0);
			modelStack.Scale(3.5, 3.5, 1);

			for (std::vector<std::string>::iterator it = howToPlayText.begin(); it != howToPlayText.end(); ++it)
			{
				modelStack.Translate(0, -count, 0);
				RenderHelper::GetInstance().RenderText(*textOnScreenMesh, texture[MENUGUI_TEXTONSCREEN], *it, Color(1, 1, 1));
			}

			modelStack.PopMatrix();
		}
		break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;
		}
	}
}

void SceneMainMenu::Exit()
{
	//AudioManager::GetInstance().ClearAudioList();
	EntityManager::GetInstance().DestroyScene(name);
}