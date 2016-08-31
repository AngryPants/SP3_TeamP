#include "Application.h"

void main(void) {

	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();

	//system("pause");

}