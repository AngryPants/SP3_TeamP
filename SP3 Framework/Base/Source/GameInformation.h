#ifndef GAMEINFORMATION_H
#define GAMEINFORMATION_H
#include "TileIndex.h"
#include "SingletonTemplate.h"
#include <vector>
#include <map>

using namespace std;

class GameInformation : public Singleton<GameInformation> {

	friend class Singleton<GameInformation>;

	private:
		// Variable(s)
		vector<int> highScore;

		// Constructor(s) and destructor
		GameInformation();
		virtual ~GameInformation();

	public:
		// Variable(s)
		map<TILE_INDEX, vector<string>> collectedParts;
		
		// Function(s)
		// Checks if a new player can be unlocked
		void CollectPart(TILE_INDEX index, std::string name);

		// Set and get high score
		void SetHighScore(int score);
		const vector<int>& GetHighScore();

		bool SaveToFile(const string& fileName);
		bool LoadFromFile(const string& fileName);

};

#endif