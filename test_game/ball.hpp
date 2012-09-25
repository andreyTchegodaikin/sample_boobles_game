#ifndef BALL_H
#define BALL_H
//----------------------------------------------------------------------------
#include "geometry.hpp"
#include <math.h>

#define MYGAME_BALL_MAX_SIZE 30
#define MYGAME_BALL_MIN_SIZE 5

struct Ball
{
  Point     _center;
  float     _r, _v;
  int       _cost;
  rgba32_t  _color;
public:
  void launch() {
    int r = rand() % 50 + 10;
    _r = (float)(r);
    _center.x = (float)(rand() % (800 - 2 * r)) + _r;
    _center.y = _r;
    _v = 5.0f * (70.0f - _r);
    _cost = (int)(_v);
    do {
      _color.red(rand() % 255);
      _color.green(rand() % 255);
      _color.blue(rand() % 255);
      _color.alpha(255);
    } while(_color.red() + _color.green() + _color.blue() < 10); // исключим чёрный цвет
  };
  // вернёт true когда долетит до пола
  bool move(double dt) {
    _center.y += (float)((double)_v * dt);
    return _center.y >= 800 - _r;
  };
  const Point& get_center() const {
    return _center;
  };
  float get_radiuse() const {
    return _r;
  };
  int get_cost() const {
    return _cost;
  };
  const rgba32_t get_color() const {
    return _color;
  };
};
//----------------------------------------------------------------------------
#endif // BALL_H