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
	set<string> unlockedHeads;
	set<string> unlockedBodies;
	set<string> unlockedArms;
	set<string> unlockedLegs;
	map<string, int> highscores;
	string currentLevel;

	//Constructor(s) & Destructor
	GameData();
	virtual ~GameData();

public:
	void SetCurrentLevel(const string& levelName);
	bool SaveGameData(const string& unlocks, const string& highscore);
	bool LoadGameData(const string& unlocks, const string& highscore);
	bool DeleteGameData(const string& filePath);
	void UnlockHead(const string& characterName);
	void UnlockBody(const string& characterName);
	void UnlockArms(const string& characterName);
	void UnlockLegs(const string& characterName);
	bool IsCharacterUnlocked(const string& characterName);
	void AddHighScore(const string& levelName, const int& score);
	const map<string, int>& GetHighScores() const;

};

#endif