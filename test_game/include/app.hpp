#ifndef APPLICATION_H
#define APPLICATION_H
//----------------------------------------------------------------------------
// базовый класс приложения
// использование:
// 1) определить свой класс, наследник Application
// 2) определить функцию get_app_instance
// всё остальное уже сделано
class App
{
private:
  virtual void setup_videomem() {}; // specialy for LOST_DEVICE
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;
public:
  // возвращает время работы приложения
  double get_time() const; // in seconds
  int run();
  void quit(int whith_error);
  virtual ~App();
};

// эту функцию должен определить пользователь
// и в ней пользователь должен инициализировать своё приложение
extern App* get_app_instance();
//----------------------------------------------------------------------------
#endif // APPLICATION_H