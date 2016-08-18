#include "GameInformation.h"

using namespace std;

GameInformation::GameInformation()
{

}

GameInformation::~GameInformation()
{

}

void GameInformation::UnlockPlayableCharacter(TILE_INDEX index, std::string name)
{
	map<TILE_INDEX, vector<string>>::iterator it = heroUnlocks.find(index);
	if (it == heroUnlocks.end()) { //We don't have a slot for this body part yet.

		vector<string> heroNames;
		heroNames.push_back(name);
		heroUnlocks.insert(std::pair<TILE_INDEX, vector<string>>(index, heroNames));
		return;
	}
	
	for (vector<string>::iterator nameiter = it->second.begin(); nameiter != it->second.end(); ++nameiter)
	{
		if (*nameiter == name)
			return;
	}

	it->second.push_back(name);
}

void GameInformation::SetHighScore(int highscore)
{
	highScore.push_back(highscore);
}

const std::vector<int>& GameInformation::GetHighScore()
{
	return highScore;
}