#include "MainMenu.h"
#include "InputManager.h"
#include <iostream>

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{

}

void MainMenu::MainMenuChoice()
{
	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MENU_DOWN])
	{
		cout << "Menu Down" << endl;
		++chooseMenu;
		if (chooseMenu > 5)
			chooseMenu = 1;

		if (!hasSavedFile && chooseMenu == 2)
			chooseMenu = 3;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MENU_UP])
	{
		cout << "Menu Up" << endl;
		--chooseMenu;
		if (chooseMenu < 1)
			chooseMenu = 5;		

		if (!hasSavedFile && chooseMenu == 2)
			chooseMenu = 1;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_SELECT])
	{
		previousMenu = chooseMenu;
		menu = static_cast<MENU>(chooseMenu);
		chooseMenu = 1;
	}
}

void MainMenu::MainOptionChoice()
{
	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MENU_DOWN])
	{
		chooseMenu++;
		if (chooseMenu > 3)
			chooseMenu = 1;
		return;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_MENU_UP])
	{
		chooseMenu--;
		if (chooseMenu < 1)
			chooseMenu = 3;
		return;
	}

	if (InputManager::GetInstance().GetInputInfo().keyReleased[INPUT_SELECT])
	{
		if (option == OPTION::OPTION_BACK)
		{
			chooseMenu = previousMenu;
			option = OPTION::OPTION_MAINOPTION;
			previousMenu = 0;
			return;
		}

		previousMenu = chooseMenu;
		option = static_cast<OPTION>(chooseMenu);
		chooseMenu = 1;
	}
}

void MainMenu::MainMenuUpdates(MENU menu, const double &deltaTime)
{
	this->menu = menu;
	switch (menu)
	{
		default:
			MainMenuChoice();
			break;

		case MENU::MENU_NEWGAME:
			break;

		case MENU::MENU_CONTINUEGAME:
			break;

		case MENU::MENU_OPTION:
			OptionUpdates(option, deltaTime);
			break;

		case MENU::MENU_HOWTOPLAY:
				break;

		case MENU::MENU_QUIT:
			break;
	}
}

void MainMenu::OptionUpdates(OPTION option, const double &deltaTime)
{
	this->option = option;
	switch (option)
	{
		case OPTION::OPTION_MAINOPTION:
			MainOptionChoice();
			break;

		case OPTION::OPTION_VOLUME:
		{
			if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_LEFT])
			{
				volume -= 0.5f * (float)deltaTime;

				if (volume < Math::EPSILON)
					volume = Math::EPSILON;
			}

			if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_RIGHT])
			{
				volume += 0.5f * (float)deltaTime;

				if (volume > 1.f)
					volume = 1.f;
			}

			GameInformation::GetInstance().SetVolume(volume);

			if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_MENU_DOWN])
			{
				this->option = OPTION::OPTION_MAINOPTION;
			}
		}
			break;

		case OPTION::OPTION_ERASEDATA:
			break;

		case OPTION::OPTION_BACK:
			menu = MENU::MENU_MAINMENU;
			this->option = OPTION::OPTION_MAINOPTION;
			chooseMenu = previousMenu;
			previousMenu = 0;
				break;
	}
}

void MainMenu::MainMenuInit()
{
	chooseMenu = 1;
	previousMenu = 0;
	hasSavedFile = false;
	menu = MENU::MENU_MAINMENU;
	option = OPTION::OPTION_MAINOPTION;

	volume = GameInformation::GetInstance().GetVolume();
}

void MainMenu::MainMenuUpdate(const double &deltaTime)
{
	MainMenuUpdates(menu, deltaTime);

	std::cout << chooseMenu << "  " << static_cast<int>(menu) << "  " << static_cast<int>(option) <<  "  " << GameInformation::GetInstance().GetVolume() << std::endl;
}

void MainMenu::MainMenuRender()
{

}