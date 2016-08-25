#ifndef CONTROLLER_GAMEPAD_H_
#define CONTROLLER_GAMEPAD_H_
#include "SingletonTemplate.h"
#include <vector>
#include <bitset>
#include "GLFW\glfw3.h"

namespace controller {

	struct Gamepad {
		std::string name;
		bool active;
		std::vector<float> axes;
		std::vector<unsigned char> buttons;
	};

	class GamepadManager : public Singleton<GamepadManager> {

	public:
		using Gamepads = std::vector<Gamepad>;

		void SetWindow(GLFWwindow*const window);
		void SetDeadzone(const float deadzone);
		float GetDeadzone() const;

		void UpdateJoysticks();

		const Gamepads& GetGamepads() const;

	private:
		friend class Singleton<GamepadManager>;

		GamepadManager();
		virtual ~GamepadManager() = default;

		GLFWwindow* window;
		std::vector<Gamepad> gamepads;
		float deadzone;
	};

}
#endif