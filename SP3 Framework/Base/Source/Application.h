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
	void Exit();

private:
	//Constructor(s) & Destructor
	Application();
	~Application();

	//Declare the window width and height as constant integer
	const static int m_window_width = 1024;
	const static int m_window_height = 800;
	
	//Declare a window object
	StopWatch m_timer;

	//Threads
	enum THREAD {
		THREAD_PLACEHOLDER,

		NUM_THREAD,
	};

	bool quit;

	double elapsedTime;
	double accumulatedTime[NUM_THREAD];

};

#endif