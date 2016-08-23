#include "Controller_Keyboard.h"

Controller_Keyboard::Controller_Keyboard() {
}

Controller_Keyboard::~Controller_Keyboard() {
}

bool Controller_Keyboard::IsKeyPressed(unsigned int key) {

	if (key < 0 || key >= MAX_KEYS) {
		return false;
	}

	return currentState[key];

}

bool Controller_Keyboard::IsKeyReleased(unsigned int key) {

	if (key < 0 || key >= MAX_KEYS) {
		return false;
	}

	//Check if the previous update we were pressing the key and now we're not.
	if (currentState[key] == 0 && previousState[key] == 1) {
		return true;
	}

	return false;

}

void Controller_Keyboard::ReadInput() {

	previousState.reset();

	for (int i = 0; i < MAX_KEYS; ++i) {
		previousState[i] = currentState[i];
	}
	currentState.reset();

	for (int j = 0; j < MAX_KEYS; ++j) {
		currentState[j] = ((GetAsyncKeyState(j) & 0x8001) != 0);
	}

}

void Controller_Keyboard::Reset() {

	previousState.reset();
	currentState.reset();

}