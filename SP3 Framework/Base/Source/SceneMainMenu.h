#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H
#include "Scene.h"
#include "MeshBuilder.h"
#include "CameraMainMenu.h"
#include "MainMenu.h"
#include "Texture.h"

class SceneMainMenu : public Scene
{
protected:
	float pointerPositionY;
	float defaultPointerPositionY;
	float pointerPositionX;
	float defaultPointerPositionX;

	bool menuChange;

	enum MENUGUI
	{
		// Pointer texture
		MENUGUI_MENU_POINTER,
		MENUGUI_MENU_BUTTONLEFT,
		MENUGUI_MENU_BUTTONRIGHT,

		// Title and background
		MENUGUI_TITLE,
		MENUGUI_BACKGROUNDONE,
		MENUGUI_BACKGROUNDTWO,
		MENUGUI_BACKGROUNDTHREE,

		// Volume graphics
		MENUGUI_VOLUMEICON,
		MENUGUI_VOLUMEPLUS,
		MENUGUI_VOLUMEMINUS,

		// All the options available for choosing in menu
		MENUGUI_MAIN_ONE,
		MENUGUI_MAIN_TWO,
		MENUGUI_MAIN_THREE,
		MENUGUI_MAIN_FOUR,
		MENUGUI_MAIN_FIVE,

		// All the options available for choosing in options
		MENUGUI_OPTION_ONE,
		MENUGUI_OPTION_TWO,
		MENUGUI_OPTION_THREE,
		MENUGUI_OPTION_FOUR,

		// Continue game options
		MENUGUI_CONTINUEGAME_DISPLAY,
		MENUGUI_CONTINUEGAME_OPTIONS,

		// Prompts
		MENUGUI_DELETEFILE_ONE,
		MENUGUI_DELETEFILE_TWO,
		MENUGUI_TWOCHOICE_YES,
		MENUGUI_TWOCHOICE_NO,
		MENUGUI_BACKTOMAIN,

		// Text Screen
		MENUGUI_TEXTSCREEN,
		MENUGUI_TEXTONSCREEN,

		MENUGUI_HOWTOPLAY_PAGEONE,
		MENUGUI_HOWTOPLAY_PAGETWO,

		MENU_GUI_TOTAL,
	};

	MainMenu mainmenu;
	MENUGUI MenuGUI;
	Texture texture[MENU_GUI_TOTAL];
	CameraMainMenu* camera;

	void DeleteSaveFileOrNot();
	void PointerPositionUpdate();

	void UpdateContinueGameToScene();
	void UpdateInTransition(const double &deltaTime);

	void RenderMenuPointer();
	void RenderMenuChoice();
	void RenderOptionChoice();

	void RenderHighScore();
	void RenderHowToPlayChoice(int chooseMenu);


public:
	Mesh* mesh;
	Mesh* textOnScreenMesh;
	string bgm;
	SceneMainMenu(const string& name);
	virtual ~SceneMainMenu();

	virtual void Init();
	virtual void Update(const double &deltaTime);
	virtual void Render();
	virtual void Exit();
};

#endif