#ifndef SCENEMAINMENU_H
#define SCENEMAINMENU_H
#include "Scene.h"
#include "MeshBuilder.h"
#include "Camera.h"
#include "MainMenu.h"
#include "Texture.h"

class SceneMainMenu : public Scene
{
	protected:
		float pointerPositionY;
		bool menuChange;

		enum MENUGUI
		{
			// Pointer texture
			MENUGUI_MENU_POINTER,

			// Title and background
			MENUGUI_TITLE,
			MENUGUI_BACKGROUND,

			// Volume graphics
			MENUGUI_VOLUMEICON,
			MENUGUI_VOLUMEPLUS,
			MENUGUI_VOLUMEMINUS,

			// All the options available for choosing
			MENUGUI_OPTION_ONE,
			MENUGUI_OPTION_TWO,
			MENUGUI_OPTION_THREE,
			MENUGUI_OPTION_FOUR,
			MENUGUI_OPTION_FIVE,
			MENU_GUI_TOTAL,
		};

		MainMenu mainmenu;
		MENUGUI MenuGUI;
		Texture texture[MENU_GUI_TOTAL];
		Camera* camera;

		bool InTransition();

		void PointerPositionUpdate();

		void RenderMenuPointer();
		void RenderMenuChoice();

	public:
		Mesh* mesh;
		SceneMainMenu();
		virtual ~SceneMainMenu();

		virtual void Init();
		virtual void Update(const double &deltaTime);
		virtual void Render();
		virtual void Exit();
};

#endif