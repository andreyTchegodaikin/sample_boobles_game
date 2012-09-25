/*
игровой объект
*/
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
//----------------------------------------------------------------------------
#include "drawable.hpp"
#include "movable.hpp"

class GameObject
{
  int         _cost;
  Drawable*   _view;
  Movable*    _motor;
private:
  GameObject() {};
public:
  GameObject(Drawable* d, Movable* m): _cost(1), _view(d), _motor(m) {};
  void set_cost(int x) {
    _cost = x;
  };
  int get_cost() const {
    return _cost;
  };
};

//----------------------------------------------------------------------------
#endif // GAME_OBJECT_H