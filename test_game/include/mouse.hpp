/*
  class Mouse хранит состояние мышки
  надо подключить к окну через IWindow::connect(Mouse&)
  на мобильных устройствах используйте class Touch
  а Mouse на мобилах обрабатывает только касания одним пальцем
*/
#ifndef MOUSE_H
#define MOUSE_H
//----------------------------------------------------------------------------
#include "noncopyable.hpp"

class Mouse: NonCopyable
{
  friend class Window;
public:
  enum Button
  {
      LEFT,       // The left mouse button
      RIGHT,      // The right mouse button
      MIDDLE,     // The middle (wheel) mouse button
      XBUTTON1,   // The first extra mouse button
      XBUTTON2,   // The second extra mouse button
      ButtonCount // Keep last -- the total number of mouse buttons
  };
private:
  int _x, _y;
  int _keys[ButtonCount];
  void reset() {
    for(int i = 0; i < ButtonCount; ++i) {
      _keys[i] = 0;
    };
  };
  Mouse() {
    reset();
  };
public:
  bool is_pressed(const Button b) const {
    return _keys[b] > 0;
  };
  int get_pos_x() const {
    return _x;
  };
  int get_pos_y() const {
    return _y;
  };
};

//----------------------------------------------------------------------------
#endif // MOUSE_H