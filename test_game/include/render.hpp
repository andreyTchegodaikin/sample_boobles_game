/*
  RENDER CONTEXT

Summary:
  Адаптер - в перспективе - кроссапишный - над OGL и DirectX

  Этот вариант - Renderable Window - расширение окна, которое теперь содержит
  rendering context и предоставляет полный и достаточный набор низкоуровневых
  функций для рисования.
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
  int release(); // если вернул не 0 - где-то что-то забыли release-нуть
  ~RenderWindow() {
    release();
  };

  // создать окно указанного размера с указанным заголовком
  bool create(int width, int height, const wchar_t * title);
  // создать окно из ресурсов
  bool create(const wchar_t* resource_name);

  // закрыть окно и освободить render device (render context)
  int close() {
    int rez = release();
    Window::close();
    return rez;
  };

  // выбрать текущий rendering device (context)
  bool set_current();
  bool begin(); // if(begin()) { можно рендерить; ... display(); };
  void display(); // отобразить все то, что нарендерили

  //TODO:
  void set_fullscreen();// not implemented пока ещё
  void set_windowed();// not implemented пока ещё

  void clear();
  void put_color(rgba32_t color);
  //TODO: всякие прочие render states

  // создаст и установит матрицу вида по указанным позиции и скейлу
  void set_view(Point& point, float zoom);
  // отправить на рендеринг очередной треугольник
  void put_triangle(Point& p0, Point& p1, Point& p2);
  // TODO: прочее

  // печатать текст
  void draw(char* text, int x, int y);
};
