/*
эта штука может двигаться
абстрактный интерфейс для игровых объектов
*/
#ifndef MOVABLE_H
#define MOVABLE_H
//----------------------------------------------------------------------------

class Movable
{
protected:
  float _x, _y;
public:
  float get_x() const  {
    return _x;
  };
  float get_y() const  {
    return _y;
  };
  void set_x(float x) {
    _x = x;
  };
  void set_y(float y) {
    _y = y;
  };
  Movable() {};
  virtual ~Movable() {};
  virtual void reset();
  virtual void move(double dt);
  virtual bool check(float x, float y); 
};

//----------------------------------------------------------------------------
#endif // MOVABLE_H