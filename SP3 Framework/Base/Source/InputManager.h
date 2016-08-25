#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SingletonTemplate.h"
#include <bitset>
#include <climits>
#include "MyMath.h"

using std::bitset;

//Some Example Controls
enum INPUT_TYPE {
	//Movement
	INPUT_MOVE_LEFT,
	INPUT_MOVE_RIGHT,
	
	INPUT_JUMP,
	INPUT_SHOOT,
	INPUT_ABILITY,

	INPUT_SELECT,

	INPUT_MENU_LEFT,
	INPUT_MENU_RIGHT,
	INPUT_MENU_UP,
	INPUT_MENU_DOWN,

	INPUT_QUIT,

	NUM_KEYS,
};

struct InputInfo {

public:
	//Variable(s)
	bitset<NUM_KEYS> keyDown;
	bitset<NUM_KEYS> keyReleased;
	float keyValue[NUM_KEYS];

	//Constructor(s) & Destructor
	InputInfo() = default;
	virtual ~InputInfo() = default;

	void ClampValues() {
		for (auto& value : keyValue) {
			value = Math::Clamp(value, 0.0f, 1.0f);
		}
	}

	void Reset() {
		keyDown.reset();
		keyReleased.reset();
		for (unsigned int i = 0; i < static_cast<unsigned int>(NUM_KEYS); ++i) {
			keyValue[i] = 0.0f;
		}
	}

};

//The job of the InputManager is to translate all the devices input into the inputs that will be used in the game.
//Therefore the InputManager will need to be edited for every game.

class InputManager : public Singleton<InputManager> {

	friend class Singleton<InputManager>;

private:
	//Variable(s)
	InputInfo inputInfo;

	//Constructor(s) & Destructor
	InputManager();
	virtual ~InputManager();

public:
	//Function(s)
	const InputInfo& GetInputInfo() const;
	void Update();

};

#endif