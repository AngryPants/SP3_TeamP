#include "GameData.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Include our Scenes

GameData::GameData() {

}

GameData::~GameData() {

}

bool GameData::SaveGameData(const string& filePath) {

	return false;

}

bool GameData::LoadGameData(const string& filePath) {

	//Open the file.
	ifstream file(filePath.c_str());
	//If file is successfully opened.
	if (!file.is_open()) {
		cout << "Error: Cannot open file " << filePath << "." << endl;
		return false;
	}

	string currentLine = "";
	while (getline(file, currentLine)) {
		if (currentLine == "") {
			continue;
		}

		istringstream iss(currentLine);
		string token;

		//Let's see what this is
		getline(iss, token, '=');
		if (token == "Head") {
			
		}

		while (getline(iss, token, ',')) {
			
		}
	}

	return true;

}

bool GameData::DeleteGameData(const string& filePath) {

	std::ofstream file;
	file.open(filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
	file.close();

	std::cout << "File Content Removed!" << std::endl;

	return true;

}

void GameData::UnlockPart(const string& partName, const string& characterName) {

	map<string, set<string> >::iterator mapIter = unlockedParts.find(partName);
	if (mapIter == unlockedParts.end()) {
		set<string> characterList;
		unlockedParts.insert(pair<string, set<string> >(partName, characterList));
		mapIter = unlockedParts.find(partName);
	}

	mapIter->second.insert(characterName);

}

bool GameData::CheckIfPartUnlocked(const string& partName, const string& characterName) {

	map<string, set<string> >::iterator mapIter = unlockedParts.find(partName);
	if (mapIter == unlockedParts.end()) {
		return false;
	}

	set<string>::iterator setIter = mapIter->second.find(characterName);
	if (setIter == mapIter->second.end()) {
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