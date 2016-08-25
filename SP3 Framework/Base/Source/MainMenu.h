#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameInformation.h"

class MainMenu
{
	public:
		int chooseMenu;
		int previousMenu;
		bool hasSavedFile;
		float volume;

		enum class MENU
		{
			MENU_MAINMENU,
			// Main Menu
			MENU_NEWGAME,
			MENU_CONTINUEGAME,
			MENU_OPTION,
			MENU_HOWTOPLAY,
			MENU_QUIT,

			MENU_TOTAL,
		};

		enum class OPTION
		{
			OPTION_MAINOPTION,

			// Options
			OPTION_VOLUME,
			OPTION_ERASEDATA,
			OPTION_BACK,

			OPTION_TOTAL,
		};
		MENU menu;
		OPTION option;

		MainMenu();
		virtual ~MainMenu();

		// Main Menu Functions
		void MainMenuChoice();
		void MainOptionChoice();

		void MainMenuUpdates(MENU menu, const double &deltaTime);
		void OptionUpdates(OPTION option, const double &deltaTime);

		void MainMenuInit();
		void MainMenuUpdate(const double &deltaTime);
		void MainMenuRender();
};

#endif