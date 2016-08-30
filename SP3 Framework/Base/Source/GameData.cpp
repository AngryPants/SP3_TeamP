#include "GameData.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Include our Scenes

GameData::GameData() {

	currentLevel = "Level 1";

}

GameData::~GameData() {
}

void GameData::SetCurrentLevel(const string& levelName) {

	currentLevel = levelName;

}

string GameData::GetCurrentLevel()
{
	return this->currentLevel;
}

bool GameData::SaveGameData(const string& unlocks, const string& highscore) {

	ofstream file;
	file.open(unlocks, std::ofstream::out | std::ofstream::trunc);
	//Save our current level
	file << "Current_Level: " + currentLevel + "\n";
	//Save our unlocked body parts.
	file << "Head=";
	for (set<string>::iterator setIter = unlockedHeads.begin(); setIter != unlockedHeads.end(); ++setIter) {
		file << *setIter + ",";
	}
	file << "\n";

	file << "Body=";
	for (set<string>::iterator setIter = unlockedBodies.begin(); setIter != unlockedBodies.end(); ++setIter) {
		file << *setIter + ",";
	}
	file << "\n";

	file << "Arms=";
	for (set<string>::iterator setIter = unlockedArms.begin(); setIter != unlockedArms.end(); ++setIter) {
		file << *setIter + ",";
	}
	file << "\n";

	file << "Legs=";
	for (set<string>::iterator setIter = unlockedLegs.begin(); setIter != unlockedLegs.end(); ++setIter) {
		file << *setIter + ",";
	}
	file << "\n";

	file.close();

	//Save our highscores
	file.open(highscore, std::ofstream::out | std::ofstream::trunc);
	for (map<string, int>::iterator mapIter = highscores.begin(); mapIter != highscores.end(); ++mapIter) {
		file << mapIter->first + "=" + to_string(mapIter->second) + "\n";
	}

	file.close();

	return false;

}

bool GameData::LoadGameData(const string& unlocks) {

	unlockedHeads.clear();
	unlockedArms.clear();
	unlockedBodies.clear();
	unlockedLegs.clear();
	highscores.clear();
	currentLevel = "Level_1";

	//Load our unlocks
	string filePath = unlocks;
	ifstream file(filePath);
	string currentLine = "";
	//If file is successfully opened.
	if (file.is_open()) 
	{
		if (filePath == "")
		{
			cout << "Error: Cannot open file " << filePath << "." << endl;
			return false;
		}

		else
		{
			while (file.good())
			{
				while (getline(file, currentLine)) {
					if (currentLine == "" || currentLine == "\n") {
						continue;
					}

					istringstream iss(currentLine);
					string headerToken = "";
					string dataToken = "";
					getline(iss, headerToken, '=');
					if (headerToken == "Current_Level") {
						getline(iss, dataToken);
						currentLevel = dataToken;
					}
					else if (headerToken == "Head") {
						while (getline(iss, dataToken, ',')) {
							unlockedHeads.insert(dataToken);
						}
					}
					else if (headerToken == "Body") {
						while (getline(iss, dataToken, ',')) {
							unlockedBodies.insert(dataToken);
						}
					}
					else if (headerToken == "Arms") {
						while (getline(iss, dataToken, ',')) {
							unlockedArms.insert(dataToken);
						}
					}
					else if (headerToken == "Legs") {
						while (getline(iss, dataToken, ',')) {
							unlockedLegs.insert(dataToken);
						}
					}
				}

				file.close();
			}

		}
	}

	else
		return false;
}

void GameData::LoadHighScore(const string &highscore)
{
	string filePath = highscore;
	ifstream file(filePath);
	string currentLine = "";
	//If file is successfully opened.
	if (file.is_open()) {

		if (filePath == "")
		{
			cout << "Error: Cannot open file " << filePath << "." << endl;
			return;
		}

		else
		{
			while (file.good())
			{
				currentLine = "";
				while (getline(file, currentLine)) {
					if (currentLine == "" || currentLine == "\n") {
						continue;
					}

					istringstream iss(currentLine);
					string headerToken;
					string dataToken;
					getline(iss, headerToken, '=');
					getline(iss, dataToken);

					highscores.insert(std::pair<string, int>(headerToken, atoi(dataToken.c_str())));
				}
			}

			file.close();
		}
	}
}

bool GameData::DeleteGameData(const string& filePath) {

	std::ofstream file;
	file.open(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
	file.close();
	std::cout << "File Content Removed!" << std::endl;

	return true;

}

void GameData::UnlockHead(const string& characterName) {

	unlockedHeads.insert(characterName);

}

void GameData::UnlockArms(const string& characterName) {

	unlockedArms.insert(characterName);

}

void GameData::UnlockBody(const string& characterName) {

	unlockedBodies.insert(characterName);

}

void GameData::UnlockLegs(const string& characterName) {

	unlockedLegs.insert(characterName);

}

bool GameData::IsCharacterUnlocked(const string& characterName) {

	if (unlockedHeads.find(characterName) == unlockedHeads.end()) {
		return false;
	}
	if (unlockedBodies.find(characterName) == unlockedBodies.end()) {
		return false;
	}
	if (unlockedArms.find(characterName) == unlockedArms.end()) {
		return false;
	}
	if (unlockedLegs.find(characterName) == unlockedLegs.end()) {
		return false;
	}

	return true;

}

void GameData::AddHighScore(const string& levelName, const int& score) {

	map<string, int>::iterator mapIter = highscores.find(levelName);
	if (mapIter == highscores.end()) {
		highscores.insert(std::pair<string, int>(levelName, score));
	} else {
		if (mapIter->second < score) {
			mapIter->second = score;
		}
	}

}

const map<string, int>& GameData::GetHighScores() const {

	return this->highscores;

}