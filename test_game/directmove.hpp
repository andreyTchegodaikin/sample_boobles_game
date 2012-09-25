/*
��� ����� ����� ��������� �����
���� �� ��������� ��������� ���������� ����������� ���� ��������� �����
*/
#ifndef DIRECT_MOVE_H
#define DIRECT_MOVE_H
//----------------------------------------------------------------------------
#include "movable.hpp"

class DirectMove: public Movable
{
  float _vx, _vy; // ��������
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
  // ��������� �� ��������� � ������� � ������� � x y � �������� r
  virtual bool check(float x, float y, float r);
};


//----------------------------------------------------------------------------
#endif // DIRECT_MOVE_H 