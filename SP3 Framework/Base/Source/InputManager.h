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
	INPUT_MOVE_UP,
	INPUT_MOVE_DOWN,

	INPUT_JUMP,
	INPUT_SHOOT,

	INPUT_PLACE_TILE,

	//Debug
	INPUT_WIREFRAME_ON,
	INPUT_WIREFRAME_OFF,
	INPUT_CULLING_ON,
	INPUT_CULLING_OFF,

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
	InputInfo() {
		Reset();
	}
	virtual ~InputInfo() {}	

	void Reset() {
		keyDown.reset();
		keyReleased.reset();
		for (int i = 0; i < static_cast<int>(NUM_KEYS); ++i) {
			keyValue[i] = 0.0f;
		}
	}

	void ClampValues() {
		for (int i = 0; i < static_cast<int>(NUM_KEYS); ++i) {
			keyValue[i] = Math::Clamp(keyValue[i], 0.0f, 1.0f);
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