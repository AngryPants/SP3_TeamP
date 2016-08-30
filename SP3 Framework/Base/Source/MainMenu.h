#ifndef MAINMENU_H
#define MAINMENU_H
#include "GameData.h" 
#include <fstream>
#include <iostream>

class MainMenu
{
	public:
		int chooseMenu;
		int previousMenu;
		bool hasSavedFile;
		bool deletingFile;
		bool transitionInProgress;
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
			OPTION_HIGHSCORE,
			OPTION_ERASEDATA,
			OPTION_BACK,

			OPTION_TOTAL,
		};

		enum class HOWTOPLAY
		{
			HOWTOPLAY_MAINHOWTOPLAY,
			HOWTOPLAY_BACK,

			HOWTOPLAY_TOTAL,
		};


		MENU menu;
		OPTION option;
		HOWTOPLAY howtoplay;

		MainMenu();
		virtual ~MainMenu();

		// Main Menu Functions
		void MainMenuChoice();
		void NewGameChoice();
		void MainOptionChoice();
		void EraseDataChoice();
		void HowToPlayChoice();

		void MainMenuUpdates(MENU menu, const double &deltaTime);
		void OptionUpdates(OPTION option, const double &deltaTime);

		std::vector<std::string> TextFileToScreen(std::string howtext);

		void MainMenuInit();
		void MainMenuUpdate(const double &deltaTime);
		void MainMenuRender();
};

#endif