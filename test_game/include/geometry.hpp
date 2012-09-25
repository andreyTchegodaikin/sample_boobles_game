/*
*/
#ifndef GEOMETRY_H
#define GEOMETRY_H

struct Rect
{
public:
  int x, y, w, h;
public:
  Rect(): x(0), y(0), w(800), h(600) {};
  Rect(int left, int right, int width, int height):
       x(left), y(right), w(width), h(height) {};
  Rect(int width, int height): x(0), y(0), w(width), h(height) {};
};

struct Pos
{
  int x, y;
public:
  Pos(): x(0), y(0) {};
  Pos(int x, int y): x(x), y(y) {};
};

struct Point
{
  float x, y;
public:
  Point(): x(0.0f), y(0.0f) {};
  Point(float x, float y): x(x), y(y) {};
	Point(const Point& other): x(other.x), y(other.x)
	{ };
	operator float*()
	{
		return &x;
	};
  Point& operator -= (const Point& v)
  {
    x -= v.x;
    y -= v.y;
    return *this;
  };
  Point& operator += (const Point& v)
  {
    x += v.x;
    y += v.y;
    return *this;
  };
  Point& operator *= (const float a)
  {
    x *= a;
    y *= a;
    return *this;
  };
  Point& operator /= (const float a)
  {
    x /= a;
    y /= a;
    return *this;
  };
  // scalar product
  float operator | (const Point& v){
    return x*v.x + y*v.y;
  };
};

#endif // GEOMETRY_H