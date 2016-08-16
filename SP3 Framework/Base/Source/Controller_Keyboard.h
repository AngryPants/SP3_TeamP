#ifndef CONTROLLER_KEYBOARD_H
#define CONTROLLER_KEYBOARD_H

#include "SingletonTemplate.h"
#include <windows.h>
#include <bitset>

using std::bitset;

class Controller_Keyboard : public Singleton<Controller_Keyboard> {

	friend class Singleton<Controller_Keyboard>;

public:
	//Static Variable(s)
	static const int MAX_KEYS = 256;

	//Function(s)
	bool IsKeyPressed(unsigned int key);
	bool IsKeyReleased(unsigned int key);

	void ReadInput();
	void Reset();

private:
	//Constructor(s) & Destructor
	Controller_Keyboard();
	virtual ~Controller_Keyboard();

	//Variable(s)
	bitset<MAX_KEYS> currentState;
	bitset<MAX_KEYS> previousState;

};

#endif