#ifndef GAMEINFORMATION_H
#define GAMEINFORMATION_H
#include "TileIndex.h"
#include "SingletonTemplate.h"
#include <vector>
#include <map>

class GameInformation : public Singleton<GameInformation>
{

	friend class Singleton<GameInformation>;

	private:
		// Variable(s)
		std::vector<int> highScore;

		// Constructor(s) and destructor
		GameInformation();
		virtual ~GameInformation();

	public:
		// Variable(s)
		std::map<TILE_INDEX, std::vector<std::string>> heroUnlocks;
		
		// Function(s)
		// Checks if a new player can be unlocked
		void UnlockPlayableCharacter(TILE_INDEX index, std::string name);

		// Set and get high score
		void SetHighScore(int highscore);
		const std::vector<int> &GetHighScore();
};

#endif