/*
эта штука может рисоваться
абстрактный интерфейс для игровых объектов
*/
#ifndef DRAWABLE_H
#define DRAWABLE_H
//----------------------------------------------------------------------------
#include "rgba32.hpp"

class Drawable
{
protected:
  rgba32_t  _color;
  float     _scale;
public:
  Drawable(): _scale(1.0f) {};
  void set_color(rgba32_t color) {
    _color = color;
  };
  void set_scale(float scale) {
    _scale = scale;
  };
  virtual ~Drawable {};
  virtual void draw(float x, float y);
  virtual void reset();
};


//----------------------------------------------------------------------------
#endif // DRAWABLE_H