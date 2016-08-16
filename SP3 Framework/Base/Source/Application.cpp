#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "AudioManager.h"
#include "InputManager.h"
#include "SceneManager.h"

//Include Scenes

GLFWwindow* m_window;
const unsigned char FPS = 60; //FPS of this game
const unsigned int frameTime = 1000 / FPS; //time for each frame

//Define an error callback
static void error_callback(int error, const char* description) {

	fputs(description, stderr);
	_fgetchar();

}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

}

void resize_callback(GLFWwindow* window, int w, int h) {

	glViewport(0, 0, w, h);

}

Application& Application::GetInstance() {

	static Application application;

	return application;

}

int Application::GetWindowWidth() {

	return this->m_window_width;

}

int Application::GetWindowHeight() {

	return this->m_window_height;

}

Application::Application() {
}

Application::~Application() {
}

void Application::Init() {

	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	//m_window = glfwCreateWindow(m_window_width, m_window_height, "150496F_ACG", NULL, NULL); //Windowed
	m_window = glfwCreateWindow(m_window_width, m_window_height, "150496F_Game_Dev", NULL, NULL); //Windowed
	//m_window = glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "150496F_ACG", glfwGetPrimaryMonitor(), NULL);

	//If the window couldn't be created
	if (!m_window) {
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	//Hide the cursor
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		
	//Initialise Threads
	elapsedTime = 0.0;
	for (unsigned int t = 0; t < NUM_THREAD; ++t) {
		accumulatedTime[t] = 0.0;
	}

	quit = false;

}

void Application::Run() {

	//Main Loop
	
	m_timer.startTimer(); //Start timer to calculate how long it takes to render this frame
	while (glfwWindowShouldClose(m_window) == false && quit == false) {

		elapsedTime = m_timer.getElapsedTime();
		SceneManager::GetInstance().Update(elapsedTime);

		//Threads
		if (accumulatedTime[UPDATE_USER_INPUT] >= 0.03) {
			InputManager::GetInstance().Update();
			if (InputManager::GetInstance().GetInputInfo().keyDown[INPUT_QUIT] == true) {
				quit = true;
			}
			accumulatedTime[UPDATE_USER_INPUT] = 0.0;
		}

		SceneManager::GetInstance().Render();
		glfwSwapBuffers(m_window); //Swap buffers

		for (unsigned int t = 0; t < NUM_THREAD; ++t) {
			accumulatedTime[t] += elapsedTime;
		}

		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

	} //Check if the ESC key had been pressed or if the window had been closed
	
}

void Application::Exit() {
	
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();

}