#ifndef GAME_DATA_H
#define GAME_DATA_H

#include "SingletonTemplate.h"
#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

class GameData : public Singleton<GameData> {

	friend class Singleton<GameData>;

private:
	//Variable(s)
	map<string, set<string> > unlockedParts;
	map<string, int> highscores;

	//Constructor(s) & Destructor
	GameData();
	virtual ~GameData();

public:
	bool SaveGameData(const string& filePath);
	bool LoadGameData(const string& filePath);
	bool DeleteGameData(const string& filePath);
	void UnlockPart(const string& partName, const string& characterName);
	bool CheckIfPartUnlocked(const string& partName, const string& characterName);
	void AddHighScore(const string& levelName, const int& score);
	const map<string, int>& GetHighScores() const;

};

#endif