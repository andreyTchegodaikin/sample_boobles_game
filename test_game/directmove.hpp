/*
эта штука может двигаться прямо
один из возможных вариантов реализации абстрактной идеи подвижной штуки
*/
#ifndef DIRECT_MOVE_H
#define DIRECT_MOVE_H
//----------------------------------------------------------------------------
#include "movable.hpp"

class DirectMove: public Movable
{
  float _vx, _vy; // скорость
public:
  DirectMove();
  DirectMove(float vx, float vy) _vx(vx), _vy(vy) {};
  void set_velosity(float vx, float vy) {
    _vx = vx;
    _vy = vy;
  };
  virtual ~DirectMove() {};
  virtual void reset();
  virtual void move(double dt) {
    _x += _vx * dt;
    _y += _vy * dt;
  };
  // проверяет на попадание в область с центром в x y и радиусом r
  virtual bool check(float x, float y, float r);
};


//----------------------------------------------------------------------------
#endif // DIRECT_MOVE_H 