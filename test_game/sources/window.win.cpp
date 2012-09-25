#include "window.hpp"
#ifdef _WINDOWS
//----------------------------------------------------------------------------
#define WINDOW_LEAN_AND_MEAN  
#include <windows.h>

/*
  TODO
  надо реализовать сигналы для событий с окном
*/
// установить обработчик для сигнала о событии
//void Window::set_handle(wnd_events on_event, bool (*pfun)(void*), void* obj) {
// TODO
//}

LRESULT CALLBACK wndproc (HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
  static int count = 0;
  // TODO: добавить отправку сигналов
  LRESULT rez = 0;
  switch(message)
  {
  case WM_CREATE:
    ++count;
	  break;
  case WM_DESTROY:
    --count;
    if(count == 0) {
      ::PostQuitMessage(0);
    }
	  break;
    
/*
 WM_MOUSEMOVE
 WM_LBUTTONDOWN
 WM_LBUTTONUP
 WM_LBUTTONDBLCLK
 WM_RBUTTONDOWN
 WM_RBUTTONUP
 WM_RBUTTONDBLCLK
 WM_MBUTTONDOWN
 WM_MBUTTONUP
 WM_MBUTTONDBLCLK
 WM_XBUTTONDOWN
 WM_XBUTTONUP
*/
  default:
    rez = DefWindowProc(hwnd, message, wParam, lParam);
  }
  return rez;
};

// регистрирует класс окна
// wchar_t* name - имя класса окна; 0 - допустимое значение.
// wchar_t* icon, small_icon - либо идентификатор ресурса либо имя внешнего
// файла; 0 - допустимое значение.
ATOM registration(HINSTANCE inst, wchar_t* name,
                  wchar_t* icon,  wchar_t* small_icon) 
// TODO: можно сделать, что бы, если не задана иконка явно, всё же поискать
// в ресурсах exe иконку (по типу ресурса поиск - и брать первую найденную)
// то же можно бы и для курсора делать
{
  WNDCLASSEXW wc;
  HICON hicon = 0;
  HICON hicon2 = 0;
  if(name == 0) {
    name = L"GameWnd";
  }

  if(icon != 0) {
    hicon = ::LoadIconW(inst, icon);
    if(hicon == 0) { // load from file
      hicon = (HICON)::LoadImageW(0, icon, IMAGE_ICON, 0, 0, LR_LOADFROMFILE|LR_SHARED);
    }
  }
  if(small_icon != 0) {
    hicon2 = ::LoadIconW(inst, small_icon);
    if(hicon2 == 0) { // load from file
      hicon2 = (HICON)::LoadImageW(0, small_icon, IMAGE_ICON, 0, 0, LR_LOADFROMFILE|LR_SHARED);
    }
  }

  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style =  CS_OWNDC | CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
  wc.lpfnWndProc = wndproc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = ::GetModuleHandleW(NULL);
  wc.hIcon = hicon;
  wc.hCursor = LoadCursorW( NULL, IDC_ARROW );
  wc.hbrBackground = (HBRUSH)( COLOR_WINDOW+1 );
  wc.lpszMenuName = 0;
  wc.lpszClassName = name;
  wc.hIconSm = hicon2;

  return RegisterClassExW( &wc );
}

void Window::close() {
  if(_wimpl != 0) {
    ::CloseWindow(reinterpret_cast<HWND>(_wimpl));
    _wimpl = 0;
  }
}

Window::Window(): _wimpl(0) {};
Window::~Window() {
  close();
}

bool Window::create(int width, int height, const wchar_t* title){
  // регистрируем класс окна
  HINSTANCE inst = ::GetModuleHandleW(NULL);
  ATOM a = registration( inst, 0, 0, 0);
  DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN
               | WS_OVERLAPPED | WS_MAXIMIZEBOX | WS_MINIMIZEBOX
               | WS_BORDER | WS_CAPTION | WS_SYSMENU;
	// выровняем окно по центру экрана
	int x = (GetSystemMetrics(SM_CXSCREEN) - width)  / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
  RECT rect;
	rect.left   = x;
  rect.right  = x + width;
	rect.top    = y;
  rect.bottom = y + height;

	// подгоним размер окна под стили
  AdjustWindowRect(&rect, style, FALSE);
  // создаем окно
  _wimpl = reinterpret_cast<WindowImpl*>(CreateWindowExW( 0,
					  MAKEINTRESOURCE(a), 
					  title,
					  style,
            rect.left, rect.top,
            rect.right - rect.left, rect.bottom - rect.top,
					  0, 0,
            ::GetModuleHandleW(NULL),
					  0 ));

  ShowWindow((HWND)_wimpl, SW_NORMAL);
  return _wimpl != 0;
}

Pos& Window::get_mouse_pos() const {
  static Pos cur;
  GetCursorPos(reinterpret_cast<POINT*>(&cur));
  ScreenToClient(reinterpret_cast<HWND>(_wimpl), reinterpret_cast<POINT*>(&cur));
  return cur;
}

const int mk[] = {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON1};
bool Window::is_mouse(MouseButton key) const {
  return (GetAsyncKeyState(mk[key])& 0x8000) != 0;
}

void Window::set_title(const wchar_t *title) {
  SetWindowTextW(reinterpret_cast<HWND>(_wimpl), title);
}

//TODO: bool Window::create(const wchar_t* resource_name) {

//----------------------------------------------------------------------------
#endif // _WINDOW
/*
NSRect frame = NSMakeRect(0, 0, 200, 200);
NSWindow* window  = [[[NSWindow alloc] initWithContentRect:frame
                    styleMask:NSBorderlessWindowMask
                    backing:NSBackingStoreBuffered
                    defer:NO] autorelease];
[window setBackgroundColor:[NSColor blueColor]];
[window makeKeyAndOrderFront:NSApp];

//Don't forget to assign window to a strong/retaining property!
//Under ARC, not doing so will cause it to disappear immediately;
//  without ARC, the window will be leaked.
*/
