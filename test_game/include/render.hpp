/*
  RENDER CONTEXT

Summary:
  ������� - � ����������� - ������������ - ��� OGL � DirectX

  ���� ������� - Renderable Window - ���������� ����, ������� ������ ��������
  rendering context � ������������� ������ � ����������� ����� ��������������
  ������� ��� ���������.
*/
#include "rgba32.hpp"
#include "window.hpp"
#include "geometry.hpp"

struct RenderContextImpl;
class RenderWindow: public Window
{
private:
  RenderContextImpl*  _device;
  void*               _dc;
public:
  RenderWindow(): _device(0), _dc(0) {};
  RenderWindow(RenderContextImpl* ptr): _device(ptr) {};
  int release(); // ���� ������ �� 0 - ���-�� ���-�� ������ release-����
  ~RenderWindow() {
    release();
  };

  // ������� ���� ���������� ������� � ��������� ����������
  bool create(int width, int height, const wchar_t * title);
  // ������� ���� �� ��������
  bool create(const wchar_t* resource_name);

  // ������� ���� � ���������� render device (render context)
  int close() {
    int rez = release();
    Window::close();
    return rez;
  };

  // ������� ������� rendering device (context)
  bool set_current();
  bool begin(); // if(begin()) { ����� ���������; ... display(); };
  void display(); // ���������� ��� ��, ��� �����������

  //TODO:
  void set_fullscreen();// not implemented ���� ���
  void set_windowed();// not implemented ���� ���

  void clear();
  void put_color(rgba32_t color);
  //TODO: ������ ������ render states

  // ������� � ��������� ������� ���� �� ��������� ������� � ������
  void set_view(Point& point, float zoom);
  // ��������� �� ��������� ��������� �����������
  void put_triangle(Point& p0, Point& p1, Point& p2);
  // TODO: ������

  // �������� �����
  void draw(char* text, int x, int y);
};
