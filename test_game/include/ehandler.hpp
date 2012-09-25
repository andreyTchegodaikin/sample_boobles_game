/*
  EVENT HANDLER DELEGATE
Summary:
  Идея такая: Функция обработки события принимает указатель на структуру,
  соответствующую событию, и возвращает int - это вроде код ошибки: 0 -
  событие было обработано, 1 - событие было проигнорировано.

  Мне не нравятся делегаты - виртуальные классы - потому что от них необходимо
  наследоваться, что не всегда возможно, а если возможно - то неудобно
  (не мне одному не нравится множественное наследование в С++).
  Нравится FastDelegate - но там хак используется...
  В новом стандарте было бы куда как проще, но он же пока не везде есть.
  Так что вот так:
*/
#ifndef GEN12_SIGNAL_H
#define GEN12_SIGNAL_H
//----------------------------------------------------------------------------
#include <stdint.h>

struct Message;

namespace {
  // не хочу проверять на ноль - пусть лучше будет вызов пустой функции
  int nop(void*, Message*) {return 1; };
}
// "магия шаблонов" сгенерирует внешнюю функцию, делегирующую вызов в класс
// Не хотим лишний уровень косвенности - пишем для событий внешние функции,
// явно принимающие указатель на объект.
template <class T, int (T::*PMethod)(Message*)>
void make_callback(void* ptr) {
  (reinterpret_cast<T*>(ptr)->*PMethod)();
};
typedef int (*PFUN)(void*, Message*);

// class EHandler
// хранит указатель на внешнюю функцию и пользовательский объект;
// для функций-членов "магия шаблонов" генерирует внешнюю функцию-адаптер.
// NOTE: копирование потенциально небезопасно: компилятору
// позволяется генерировать конструктор копирования по умолчанию, но для копии
// Подпиcчик не вызовет disconnect.
class EHandler
{
public:
private:
  PFUN    _act;     // pointer to user on_signal function
  void*     _data;    // pointer to user data structure
public:
  EHandler(PFUN f = &nop, void* obj = 0): _act(f), _data(obj) {};
  ~EHandler(){
    _act = &nop;      // вызов неподключенного сигнала не будет фатальным
    _data = 0;
  };
  operator bool() const {
      return _act != &nop;
  };
  bool is_used() const {
    return this->operator bool();
  };
  bool operator ==(const EHandler& other){
      return _act == other._act && _data == other._data;
  };
  void connect(PFUN pfun, void* pobj = 0){
    _data = pobj;
    _act = pfun;
  };
  template <class T, void (T::*PMethod)()>
  void connect(T* obj){
    connect(make_callback<T, PMethod>, obj);
  };
  void disconnect() {
    _data = 0;
    _act = &nop;
  };
  int call(Message* m) {
    return (*_act)(_data, m);
  };
};

//----------------------------------------------------------------------------
#endif // GEN12_SIGNAL_H