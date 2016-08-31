#include "Application.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

void main(void) {

	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();

	//Check for memory leaks.
	_CrtDumpMemoryLeaks();

	system("pause");

}