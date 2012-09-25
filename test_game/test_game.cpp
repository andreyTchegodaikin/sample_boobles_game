#include "app.hpp"
#include "window.hpp"
#include "render.hpp"
#include "err.hpp"
#include "geometry.hpp"

#include "resource.h"
#include "ball.hpp"

// ������������ ���������� �������
#define MYGAME_BALL_MAX 32
// ������ ��������� ������� (������)
#define MYGAME_BALL_APPEAR 0.66

class SampleGame: public App
{
private:
  RenderWindow  _main;
  Ball          _ball[MYGAME_BALL_MAX];
  int           _count;                 // ������� ���������� �������
  double        _time;                  // ������� �����
  double        _time_left;             // ������ ������� ������
  int           _score;
private:
  void update();
  void render();
  void shutdown();
public:
  virtual ~SampleGame();
  SampleGame();
  void init();
  // �������� ���� � ������� � x, y � �������� r
  void RenderCircle(float x, float y, float r);

  // ��������� ����� ������
  void launch_ball() {
    if(_count < 31) {
      _ball[_count].launch();
      ++_count;
    }
  };
  // ������ ��������� ������
  void delete_ball(Ball& b) {
    Ball* last = &(_ball[_count - 1]);
    if(&b != last) {
      b = *last;
    };
    --_count;
  };
} my_game;

SampleGame::SampleGame(): _count(0) {
}

void SampleGame::init() {
  _count = 0;
  _time = App::get_time();
  _time_left = MYGAME_BALL_APPEAR;
  _score = 0;
  if(!_main) {
    _main.create(800, 600, L"Hello!");
  };
}

// ��� ������� ���������� �� main() ������� ������ ����������
App* get_app_instance() {
  my_game.init();
  return &my_game;
}

SampleGame::~SampleGame() {
}

void SampleGame::update() {
  double tmp = App::get_time();
  double dt = tmp - _time;
  _time = tmp;

  // ������ ������ ������ ������ BALL_APPEAR sec
  _time_left -= dt;
  if(_time_left <= 0.0) {
    launch_ball();
    _time_left = MYGAME_BALL_APPEAR;
  }

  // ��� ������ �������� ����
  Ball* ptr = _ball;
  int i = 0;
  bool click = _main.is_mouse(Window::MB_Left);
  while(i < _count) {
    // �������� ��������� ����� � ����������� ������
    if(click) {
      Pos cur = _main.get_mouse_pos();
      Point tmp((float)cur.x, (float)cur.y);
      tmp -= ptr->get_center();
      float delta = ptr->get_radiuse();
      delta *= delta;
      delta -= tmp.x * tmp.x + tmp.y * tmp.y;
      if(delta > 0.001f) {// ������ ��� ������ ������
        _score += ptr->get_cost();
        delete_ball(*ptr);
      }
    }

    // ����������� ������
    if(ptr->move(dt)) {
      delete_ball(*ptr); // ������� ���������� �� ���� ������
    }
    else {
      ++i;
      ++ptr;
    }
  };
}

// ��� ������� ���������� ������ ����������
void SampleGame::render() {
  static char text[32] = "score:         ";
  _main.clear();
  _main.begin();

  Ball* ptr = _ball;
  for(int i = 0; i < _count; ++ptr, ++i) {
    _main.put_color(ptr->get_color());
    RenderCircle(ptr->get_center().x, ptr->get_center().y, ptr->get_radiuse());
  }

  _main.display();
  itoa(_score, &(text[7]), 10);
  _main.draw(text, 0, 0);
}

// ��� ������� ���������� ������ ���������� ��� ���������� ������ ����������
void SampleGame::shutdown() {
}

void SampleGame::RenderCircle(float x, float y, float r) {
  Point c(x, y);
  Point p1;
  Point p2;

  p1.x = x + r;
  p1.y = y;
  p2.x = x + 0.86602540378443864676372317075294f * r;
  p2.y = y + 0.5f * r;
  _main.put_triangle(c, p1, p2);
  p1.x = x + 0.5f * r;
  p1.y = y + 0.86602540378443864676372317075294f * r;
  _main.put_triangle(c, p2, p1);
  p2.x = x + 0.5f;
  p2.y = y + r;
  _main.put_triangle(c, p1, p2);
  p1.x = x - 0.5f * r;
  _main.put_triangle(c, p2, p1);
  p2.x = x - 0.86602540378443864676372317075294f * r;
  p2.y = y + 0.5f * r;
  _main.put_triangle(c, p1, p2);
  p1.x = x - r;
  p1.y = y;
  _main.put_triangle(c, p2, p1);
  p2.x = x - 0.86602540378443864676372317075294f * r;
  p2.y = y - 0.5f * r;
  _main.put_triangle(c, p1, p2);
  p1.x = x - 0.5f * r;
  p1.y = y - 0.86602540378443864676372317075294f * r;
  _main.put_triangle(c, p2, p1);
  p2.x = x;
  p2.y = y - r;
  _main.put_triangle(c, p1, p2);
  p1.x = x + 0.5f * r;
  p1.y = y - 0.86602540378443864676372317075294f * r;
  _main.put_triangle(c, p2, p1);
  p2.x = x + 0.86602540378443864676372317075294f * r;
  p2.y = y - 0.5f * r;
  _main.put_triangle(c, p1, p2);
  p1.x = x + r;
  p1.y = y;
  _main.put_triangle(c, p2, p1);
}

