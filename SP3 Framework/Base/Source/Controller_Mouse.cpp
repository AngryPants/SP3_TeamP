#include "Controller_Mouse.h"
#include "Application.h"

namespace controller {

	Mouse::Mouse() {

		window = nullptr;
		deadZone = 0.05f;
		travelDistanceX = 0.0f;
		travelDistanceY = 0.0f;

	}

	Mouse::~Mouse() {
	}

	void Mouse::SetWindow(GLFWwindow*const window) {

		this->window = window;

	}

	bool Mouse::IsKeyPressed(unsigned int key) { //0 - Left, 1 - Right, 2 - Middle

		if (key < 0 || key >= MAX_KEYS) {
			return false;
		}

		return currentState[key];

	}

	bool Mouse::IsKeyReleased(unsigned int key) {

		if (key < 0 || key >= MAX_KEYS) {
			return false;
		}

		if (currentState[key] == 0 && previousState[key] == 1) {
			return true;
		}

		return false;

	}

	CursorPosition Mouse::GetCursorPosition() {

		return this->cursorPosition;

	}

	float Mouse::GetTravelDistanceX() {

		return travelDistanceX;

	}

	//NOTE: THE 0 VALUE FOR Y IS AT THE TOP OF THE SCREEN.
	float Mouse::GetTravelDistanceY() {

		return travelDistanceY;

	}

	void Mouse::SetDeadZone(const float& deadZone) {

		if (deadZone < 0.0f) {
			this->deadZone = 0.0f;
		}
		else if (deadZone > 1.0f) {
			this->deadZone = 1.0f;
		}
		else {
			this->deadZone = deadZone;
		}

	}

	void Mouse::ReadInput() {

		//Mouse Clicks
		for (int i = 0; i < MAX_KEYS; ++i) {
			previousState[i] = currentState[i];
		}
		currentState.reset();

		for (int j = 0; j < MAX_KEYS; ++j) {
			if (glfwGetMouseButton(window, j) == 0) {
				currentState[j] = 0;
			}
			else {
				currentState[j] = 1;
			}
		}

		//Mouse Movement
		glfwGetCursorPos(window, &cursorPosition.x, &cursorPosition.y);

		int windowWidth = 0;
		int windowHeight = 0;
		glfwGetWindowSize(window, &windowWidth, &windowHeight);

		CursorPosition windowCentre;
		windowCentre.Set(static_cast<float>(windowWidth / 2), static_cast<float>(windowHeight / 2));
		glfwSetCursorPos(window, windowCentre.x, windowCentre.y);

		travelDistanceX = static_cast<float>(cursorPosition.x) / static_cast<float>(windowWidth / 2);
		travelDistanceY = static_cast<float>(cursorPosition.y) / static_cast<float>(windowHeight / 2);

		if (travelDistanceX < deadZone && travelDistanceX > -deadZone) {
			travelDistanceX = 0.0f;
		}
		if (travelDistanceY < deadZone && travelDistanceY > -deadZone) {
			travelDistanceY = 0.0f;
		}

	}

	void Mouse::Reset() {

		previousState.reset();
		currentState.reset();

	}

}