#include "Controller_Gamepad.h"

namespace controller {

	const unsigned int TOTAL_JOYSTICKS = GLFW_JOYSTICK_LAST;

	GamepadManager::GamepadManager()
	:
	window(nullptr),
	deadzone(0.15f) {


	}

	void GamepadManager::SetDeadzone(const float deadzone)
	{
		this->deadzone = std::abs(deadzone);
	}

	float GamepadManager::GetDeadzone() const
	{
		return deadzone;
	}

	const GamepadManager::Gamepads& GamepadManager::GetGamepads() const {

		return gamepads;

	}

	void GamepadManager::SetWindow(GLFWwindow*const window) {

		this->window = window;
		gamepads.resize(TOTAL_JOYSTICKS);

	}

	void GamepadManager::UpdateJoysticks() {

		for (unsigned index = 0; index < TOTAL_JOYSTICKS; ++index) {

			Gamepad& gamepad = gamepads[index];
			gamepad.active = glfwJoystickPresent(index);

			if (gamepad.active) {

				const float* axes;
				int axes_count;

				axes = glfwGetJoystickAxes(index, &axes_count);

				const unsigned char* buttons;
				int button_count;

				buttons = glfwGetJoystickButtons(index, &button_count);

				gamepad.name = glfwGetJoystickName(index);
				gamepad.buttons.resize(button_count);
				memcpy(&gamepad.buttons.front(), buttons, sizeof(gamepad.buttons.front()) * gamepad.buttons.size());
				gamepad.axes.resize(axes_count);
				memcpy(&gamepad.axes.front(), axes, sizeof(gamepad.axes.front()) * gamepad.axes.size());

			}

		}

	}

}