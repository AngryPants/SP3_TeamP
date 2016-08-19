#include "GameInformation.h"

GameInformation::GameInformation()
{
}

GameInformation::~GameInformation()
{
}

void GameInformation::CollectPart(TILE_INDEX index, std::string name)
{
	map<TILE_INDEX, vector<string>>::iterator it = collectedParts.find(index);
	if (it == collectedParts.end()) { //We don't have a slot for this body part yet.

		vector<string> heroNames;
		heroNames.push_back(name);
		collectedParts.insert(pair<TILE_INDEX, vector<string>>(index, heroNames));
		return;
	}
	
	for (vector<string>::iterator nameiter = it->second.begin(); nameiter != it->second.end(); ++nameiter)
	{
		if (*nameiter == name)
			return; //Already unlocked it.
	}

	it->second.push_back(name);
}

void GameInformation::SetHighScore(int highscore)
{
	highScore.push_back(highscore);
}

const vector<int>& GameInformation::GetHighScore()
{
	return highScore;
}

bool GameInformation::SaveToFile(const string& fileName)
{
	return false;
}

bool GameInformation::LoadFromFile(const string& fileName)
{
	return false;
}