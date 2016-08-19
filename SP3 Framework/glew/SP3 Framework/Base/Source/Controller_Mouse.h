#ifndef CONTROLLER_MOUSE_H
#define CONTROLLER_MOUSE_H

#include "SingletonTemplate.h"
#include <climits>
#include <bitset>

using std::bitset;

struct CursorPosition {

public:
	//Variable(s)
	double x, y;

	//Constructor(s) & Destructor
	CursorPosition(double x = 0.0, double y = 0.0) {
		Set(x, y);
	}
	~CursorPosition() {}

	//Setter(s)
	void Set(double x, double y) {
		this->x = x;
		this->y = y;
	}

	//Operator Overload
	CursorPosition operator=(const CursorPosition& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;

		return *this;
	}
	CursorPosition operator-(const CursorPosition& rhs) const {
		return CursorPosition(this->x - rhs.x, this->y - rhs.y);
	}
	CursorPosition& operator-=(const CursorPosition& rhs) {
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}
	CursorPosition operator+(const CursorPosition& rhs) const {
		return CursorPosition(this->x + rhs.x, this->y + rhs.y);
	}
	CursorPosition& operator+=(const CursorPosition& rhs) {
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

};

//NOTE: DO NOT USE CONTROLLER MOUSE DIRECTLY!
//USE THE INPUTMANAGER INSTEAD.
class Controller_Mouse : public Singleton<Controller_Mouse> {

	friend class Singleton<Controller_Mouse>;

public:
	//Static Variable(s)
	static const int MAX_KEYS = 3;

private:
	//Constructor(s) & Destructor
	Controller_Mouse();
	virtual ~Controller_Mouse();

	//Mouse Clicks
	bitset<MAX_KEYS> currentState;
	bitset<MAX_KEYS> previousState;

	//Mouse Movement
	CursorPosition cursorPosition;
	float deadZone;
	float travelDistanceX, travelDistanceY;

public:
	//Mouse Clicks
	bool IsKeyPressed(unsigned int key);
	bool IsKeyReleased(unsigned int key);

	//Cursor Movement
	CursorPosition GetCursorPosition();
	float GetTravelDistanceX();
	float GetTravelDistanceY();
	void SetDeadZone(const float& deadZone);

	void ReadInput();
	void Reset();

};

#endif