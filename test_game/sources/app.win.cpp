/*
	MAIN
*/
#include "app.hpp"

#ifdef _WINDOWS
//----------------------------------------------------------------------------
#define WINDOW_LEAN_AND_MEAN  
#include <windows.h>

App::~App() {
};

double App::get_time() const {
  // TODO: потом надо сделать, что бы, пока приложение не активно, то и
  // врем€ дл€ него бы не шло.
  return double(::timeGetTime()) / 1000.0;
};

int App::run() {
	MSG	msg;	// system message
  PeekMessage(&msg,NULL,0,0,PM_NOREMOVE);
/*
ну это самое простое решение
Ќадо бы вызывать update, скажем, каждые 5 - 15 msec...
ƒа, и ещЄ одно упрощение - тут нет обработки исключений...
*/
  while (msg.message!=WM_QUIT)
  {
      if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
      }
      else
      {
          this->update();
          this->render();
      }
  }
  this->shutdown();
  return msg.wParam;
};

void App::quit(int whith_error) {
  ::PostQuitMessage(whith_error);
};

#ifdef _DEBUG // отлавливаем утечки пам€ти 
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR cmdline, int) {
#ifdef _DEBUG // отлавливаем утечки пам€ти 
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//May Do:  _CrtSetBreakAlloc(54);
#endif

  int rez = 0;
  App* app = get_app_instance();

  if( app == 0 ) {
    rez = -1;
  }
  else {
    rez = app->run();
  };

  return rez;
};
//----------------------------------------------------------------------------
#endif // _WINDOWS