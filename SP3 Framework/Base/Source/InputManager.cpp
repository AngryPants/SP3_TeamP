#include "InputManager.h"

//Input Devices
#include "Controller_Keyboard.h"
#include "Controller_Mouse.h"

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

const InputInfo& InputManager::GetInputInfo() const {

	return this->inputInfo;

}

void InputManager::Update() {

	inputInfo.Reset();
	Controller_Keyboard& keyboard = Controller_Keyboard::GetInstance();
	keyboard.ReadInput();
	Controller_Mouse& mouse = Controller_Mouse::GetInstance();
	mouse.ReadInput();

	/********************************************************************************************************************/
	//This is where we start customising the controls for our game. It might get a little tedious.
	//For the sake of standardisation, ensure that keyValue is between 0.0f to 1.0f.
	//The point of keyValue is when using mouse or controller. When using a mouse, moving the mouse from the centre of
	//the screen all the way to the edge of the screen will be considered 1.0f.
	/********************************************************************************************************************/
	
	//Quit Button
	if (keyboard.IsKeyPressed(VK_ESCAPE)) {
		inputInfo.keyDown[INPUT_QUIT] = 1;
		inputInfo.keyValue[INPUT_QUIT] = 1.0f;
	}

	//Simple example player controls.
	if (keyboard.IsKeyPressed(VK_LEFT)) {
		inputInfo.keyDown[INPUT_MOVE_LEFT] = 1;
		inputInfo.keyValue[INPUT_MOVE_LEFT] = 1.0f;
	} else if (keyboard.IsKeyReleased(VK_LEFT)) {
		inputInfo.keyReleased[INPUT_MOVE_LEFT] = 1;
	}
	if (keyboard.IsKeyPressed(VK_RIGHT)) {
		inputInfo.keyDown[INPUT_MOVE_RIGHT] = 1;
		inputInfo.keyValue[INPUT_MOVE_RIGHT] = 1.0f;
	} else if (keyboard.IsKeyReleased(VK_RIGHT)) {
		inputInfo.keyReleased[INPUT_MOVE_RIGHT] = 1;
	}
	if (keyboard.IsKeyPressed(VK_SPACE)) {
		inputInfo.keyDown[INPUT_JUMP] = 1;
		inputInfo.keyValue[INPUT_JUMP] = 1.0f;
	}
	if (keyboard.IsKeyPressed(VK_DOWN)) {
		inputInfo.keyDown[INPUT_MOVE_DOWN] = 1;
		inputInfo.keyValue[INPUT_MOVE_DOWN] = 1.0f;
	} else if (keyboard.IsKeyReleased(VK_DOWN)) {
		inputInfo.keyReleased[INPUT_MOVE_DOWN] = 1;
	}
	if (keyboard.IsKeyPressed(VK_UP)) {
		inputInfo.keyDown[INPUT_MOVE_UP] = 1;
		inputInfo.keyValue[INPUT_MOVE_UP] = 1.0f;
	} else if (keyboard.IsKeyReleased(VK_UP)) {
		inputInfo.keyReleased[INPUT_MOVE_UP] = 1;
	}
	if (keyboard.IsKeyReleased(VK_RETURN)) {
		inputInfo.keyReleased[INPUT_PLACE_TILE] = 1;
	}

	if (keyboard.IsKeyPressed('F')) {
		inputInfo.keyDown[INPUT_SHOOT] = 1;
		inputInfo.keyValue[INPUT_SHOOT] = 1.0f;
	} else if (keyboard.IsKeyReleased('F')) {
		inputInfo.keyReleased[INPUT_SHOOT] = 1;
	}

	if (keyboard.IsKeyPressed(VK_SHIFT) && keyboard.IsKeyPressed('1')) {
		inputInfo.keyDown[INPUT_WIREFRAME_ON] = 1;
		inputInfo.keyValue[INPUT_WIREFRAME_ON] = 1;
	}
	if (keyboard.IsKeyPressed(VK_SHIFT) && keyboard.IsKeyPressed('2')) {
		inputInfo.keyDown[INPUT_WIREFRAME_OFF] = 1;
		inputInfo.keyValue[INPUT_WIREFRAME_OFF] = 1;
	}

	/********************************************************************************************************************/
	//Do not touch anything below unless you know what you're doing.
	/********************************************************************************************************************/
	
	inputInfo.ClampValues(); //This is to ensure that our keyValues are between 0.0f and 1.0f;

}