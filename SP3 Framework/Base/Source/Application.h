#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application {

public:
	//Getter(s)
	static Application& GetInstance();
	int GetWindowWidth();
	int GetWindowHeight();

	//Function(s)
	void Init();
	void Run();
	void Quit();
	void Exit();

private:
	//Constructor(s) & Destructor
	Application();
	~Application();

	//Declare the window width and height as constant integer
	int m_window_width;
	int m_window_height;
	
	//Declare a window object
	StopWatch m_timer;

	//Threads
	enum THREAD {
		THREAD_UPDATE_WINDOW_SIZE,

		NUM_THREAD,
	};

	bool quit;

	double elapsedTime;
	double accumulatedTime[NUM_THREAD];

};

#endif