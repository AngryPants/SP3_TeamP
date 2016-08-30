#include "MainMenu.h"
#include "InputManager.h"
#include "Application.h"
#include "GameManager.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{

}

void MainMenu::MainMenuChoice()
{
	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_DOWN])
	{
		++chooseMenu;
		if (chooseMenu > 5)
			chooseMenu = 1;

		if (!hasSavedFile && chooseMenu == 2)
			chooseMenu = 3;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_UP])
	{
		--chooseMenu;
		if (chooseMenu < 1)
			chooseMenu = 5;		

		if (!hasSavedFile && chooseMenu == 2)
			chooseMenu = 1;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_SELECT])
	{		
		previousMenu = chooseMenu;
		menu = static_cast<MENU>(chooseMenu);
		chooseMenu = 1;

		switch (menu)
		{
			default:
				break;

			case MENU::MENU_NEWGAME:
				break;

			case MENU::MENU_CONTINUEGAME:
				//transitionInProgress = true;
				break;

			case MENU::MENU_OPTION:
				option = OPTION::OPTION_MAINOPTION;
				transitionInProgress = true;
				break;

			case MENU::MENU_HOWTOPLAY:
				transitionInProgress = true;
				break;

			case MENU::MENU_QUIT:
				break;
		}
	}
}

void MainMenu::NewGameChoice()
{
	if (hasSavedFile)
	{
		if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_RIGHT])
		{
			++chooseMenu;
			if (chooseMenu > 2)
				chooseMenu = 1;
		}

		if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_LEFT])
		{
			--chooseMenu;
			if (chooseMenu < 1)
				chooseMenu = 2;
		}

		if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_SELECT])
		{
			if (chooseMenu == 1)
			{
				GameData::GetInstance().DeleteGameData("SaveFile//DataOne.txt");
				deletingFile = true;
			}

			if (chooseMenu == 2)
			{
				chooseMenu = previousMenu;
				menu = MENU::MENU_MAINMENU;
				previousMenu = 0;
			}
		}
	}
}

void MainMenu::MainOptionChoice()
{
	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_DOWN])
	{
		chooseMenu++;
		if (chooseMenu > 3)
			chooseMenu = 1;

		if (!hasSavedFile)
		{
			if (chooseMenu == 2)
				chooseMenu = 3;
		}
		return;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_UP])
	{
		chooseMenu--;
		if (chooseMenu < 1)
			chooseMenu = 3;

		if (!hasSavedFile)
		{
			if (chooseMenu == 2)
				chooseMenu = 1;
		}

		return;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_SELECT])
	{
		option = static_cast<OPTION>(chooseMenu);

		if (option == OPTION::OPTION_BACK)
		{
			transitionInProgress = true;
			menu = MENU::MENU_MAINMENU;
			chooseMenu = previousMenu;
			previousMenu = 0;
		}

		if (option == OPTION::OPTION_ERASEDATA)
		{
			chooseMenu = 1;
		}
	}
}

void MainMenu::EraseDataChoice()
{
	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_LEFT])
	{
		chooseMenu--;
		if (chooseMenu < 1)
			chooseMenu = 2;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_RIGHT])
	{
		chooseMenu++;
		if (chooseMenu > 2)
			chooseMenu = 1;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_SELECT])
	{
		switch (chooseMenu)
		{
			default:
				break;

			case 1:
			{
				deletingFile = true;
				chooseMenu = previousMenu;
			}
			break;

			case 2:
			{
				option = OPTION::OPTION_MAINOPTION;
				chooseMenu = previousMenu;
			}
			break;
		}
	}
}

void MainMenu::HowToPlayChoice()
{
	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_LEFT])
	{
		--chooseMenu;

		if (chooseMenu < 1)
			chooseMenu = 5;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_MENU_RIGHT])
	{
		++chooseMenu;

		if (chooseMenu > 5)
			chooseMenu = 1;
	}

	if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_BACK])
	{
		howtoplay = HOWTOPLAY::HOWTOPLAY_BACK;

		if (howtoplay == HOWTOPLAY::HOWTOPLAY_BACK)
		{
			transitionInProgress = true;
			menu = MENU::MENU_MAINMENU;
			chooseMenu = previousMenu;
			previousMenu = 0;
		}
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
			NewGameChoice();
			break;

		case MENU::MENU_CONTINUEGAME:
			break;

		case MENU::MENU_OPTION:
			OptionUpdates(option, deltaTime);
			break;

		case MENU::MENU_HOWTOPLAY:
			HowToPlayChoice();
				break;

		case MENU::MENU_QUIT:
		Application::GetInstance().Quit();
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

		case OPTION::OPTION_HIGHSCORE:
		{
			if (InputManager::GetInstance().GetInputInfo().keyPressed[INPUT_BACK])
				this->option = OPTION::OPTION_MAINOPTION;
		}
			break;

		case OPTION::OPTION_ERASEDATA:
			EraseDataChoice();
			break;

		case OPTION::OPTION_BACK:
			break;
	}
}

std::vector<std::string> MainMenu::TextFileToScreen(std::string howtext)
{
	std::ifstream file;
	file.open(howtext, std::ifstream::in);
	std::vector<std::string> text;

	if (file.is_open())
	{
		while (file.good())
		{
			std::string howToPlayText;
			std::getline(file, howToPlayText);
			text.push_back(howToPlayText);
		}

		file.close();
		return text;
	}

	else
		std::cout << "Unable to locate/ open file" << std::endl;
}

void MainMenu::MainMenuInit()
{
	chooseMenu = 1;
	previousMenu = 0;
	deletingFile = false;
	transitionInProgress = false;

	if (GameData::GetInstance().LoadGameData("SaveFile//DataOne.txt")) {
		hasSavedFile = true;
	} else {
		hasSavedFile = false;
	}

	GameData::GetInstance().LoadHighScore("SaveFile//Highscore.txt");

	menu = MENU::MENU_MAINMENU;
	option = OPTION::OPTION_MAINOPTION;
	howtoplay = HOWTOPLAY::HOWTOPLAY_MAINHOWTOPLAY;
}

void MainMenu::MainMenuUpdate(const double &deltaTime)
{
	MainMenuUpdates(menu, deltaTime);
	//std::cout << chooseMenu << "  " << static_cast<int>(menu) << "  " << static_cast<int>(option) <<  "  " << GameInformation::GetInstance().GetVolume() << std::endl;
	//std::cout << GameInformation::GetInstance().GetDataSaveNum() << " " << GameInformation::GetInstance().GetDataSaveLevel();
}

void MainMenu::MainMenuRender()
{

}