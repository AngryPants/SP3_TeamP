#include "Controller_Keyboard.h"

namespace controller {

	Key::Key(KEYS key, KEY_STATE state, int scancode, Modifiers modifiers)
	:
	key(key),
	state(state),
	scancode(scancode),
	modifiers(modifiers) {
	}

	KEYS Key::GetKey() const {
		return key;
	}

	KEY_STATE Key::GetState() const {
		return state;
	}

	template<>
	bool Key::GetModifier<MODIFIERS::SHIFT>() const {
		return modifiers[0];
	}

	template<>
	bool Key::GetModifier<MODIFIERS::CTRL>() const {
		return modifiers[1];
	}

	template<>
	bool Key::GetModifier<MODIFIERS::ALT>() const {
		return modifiers[2];
	}

	template<>
	bool Key::GetModifier<MODIFIERS::SUPER>() const {
		return modifiers[3];
	}

	int Key::GetScancode() const {
		return scancode;
	}

	Keyboard::Keyboard() : window(nullptr) {	
	}

	void Keyboard::SetWindow(GLFWwindow*const window) {
		this->window = window;
		static std::queue<Key>* queue = nullptr;
		queue = &GetInstance().key_queue;
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			switch (action) {
				case GLFW_PRESS:
					queue->push(Key(KEYS(key), KEY_STATE::PRESS, scancode, mods));
					break;
				case GLFW_RELEASE:
					queue->push(Key(KEYS(key), KEY_STATE::RELEASE, scancode, mods));
					break;
			}
		});
	}

	Key Keyboard::GetKey() {
		if (key_queue.empty())
		{
			throw std::exception("We ran out of keys!");
		}

		Key key = key_queue.front();
		key_queue.pop();
		return key;
	}

	int Keyboard::GetUnicode() {
		if (unicode_queue.empty())
		{
			throw std::exception("We ran out of unicode characters!");
		}

		int unicode = unicode_queue.front();
		unicode_queue.pop();
		return unicode;
	}

	std::string Keyboard::GetClipboard() {
		return glfwGetClipboardString(window);
	}

	void Keyboard::SetClipboard(std::string string) {
		glfwSetClipboardString(window, string.c_str());
	}

	void Keyboard::ClearInput() {
		unicode_queue.swap(std::queue<int>());
		key_queue.swap(std::queue<Key>());
	}

}