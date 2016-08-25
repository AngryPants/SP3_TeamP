#ifndef INGAMEMENU_H
#define INGAMEMENU_H
#include "GameInformation.h"

class InGameMenu
{
	public:
		InGameMenu();
		virtual ~InGameMenu();

		enum IN_GAME_MENU
		{
			IN_GAME_MENUTYPE,
			IN_GAME_RESTART,
			IN_GAME_QUITLEVEL,
			IN_GAME_TOTAL,
		};

		void ChangeVolume(float volume);
		void RestartLevel();
		void QuitLevel();
};

#endif