/*
  WINDOW

Summary:
  Окно приложения (или экран): в него рисуют (view), в него поступает ввод
  от мышки (касания пальцев) и клавиатуры, а так же с ним взаимодействует
  пользователь: он может переместить окно, свернуть, развернуть, закрыть...
  и т.п.
*/
#ifndef WINDOW_H
#define WINDOW_H
//----------------------------------------------------------------------------
#include "noncopyable.hpp"
#include "geometry.hpp"
#include "mouse.hpp"
//#include "ehandler.hpp"
//#include "keyboard.hpp"

struct WindowImpl;// platphorm-speciphic
class Window: NonCopyable
{
protected:
  WindowImpl*         _wimpl;
public:
  // события - используются при подключении пользовательского обработчика
  enum WndEvents {
    WE_Nothing = 0,
    WE_Should_close,  // окно может быть закрыто
    WE_Closed,        // окно было закрыто
    WE_Resize,        // в том числе maximize и normalise
    WE_Hide,          // нельзя рисовать и получать ввод
    WE_Show,          // снова надо рисовать и получать ввод
    WE_Inactive,      // нет ввода, но можно рисовать
    WE_Forse32   = 0xffffffff
  };
  enum MouseButton
  {
      MB_Left     = 0, // The left mouse button
      MB_Right    = 1, // The right mouse button
      MB_Middle   = 2, // The middle (wheel) mouse button
      MB_XButton1 = 3, // The first extra mouse button
      MB_XButton2 = 4, // The second extra mouse button
      MB_Count         // the total number of mouse buttons
  };
public:
  Window();
  virtual ~Window();

  operator bool() const {
    return _wimpl != 0;
  };

  // создать окно указанного размера с указанным заголовком
  bool create(int width, int height, const wchar_t* title);
  // создать окно из ресурсов
  bool create(const wchar_t* resource_name);

  // закрыть окно
  void close();

  // получить позицию мышки в окне
  Pos& get_mouse_pos() const;
  // проверить состояние клавиши мышки
  // true если клавиша нажата
  bool is_mouse(MouseButton pressed) const;
  // TODO: keyboard

  // установить текст заголовка окна
  void set_title(const wchar_t* title);
  // TODO: сетеры и гетеры для различных свойств окна... потом...

  // TODO: события и делегаты
};

//----------------------------------------------------------------------------
#endif // WINDOW_H