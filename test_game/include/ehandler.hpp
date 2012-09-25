/*
  EVENT HANDLER DELEGATE
Summary:
  ���� �����: ������� ��������� ������� ��������� ��������� �� ���������,
  ��������������� �������, � ���������� int - ��� ����� ��� ������: 0 -
  ������� ���� ����������, 1 - ������� ���� ���������������.

  ��� �� �������� �������� - ����������� ������ - ������ ��� �� ��� ����������
  �������������, ��� �� ������ ��������, � ���� �������� - �� ��������
  (�� ��� ������ �� �������� ������������� ������������ � �++).
  �������� FastDelegate - �� ��� ��� ������������...
  � ����� ��������� ���� �� ���� ��� �����, �� �� �� ���� �� ����� ����.
  ��� ��� ��� ���:
*/
#ifndef GEN12_SIGNAL_H
#define GEN12_SIGNAL_H
//----------------------------------------------------------------------------
#include <stdint.h>

struct Message;

namespace {
  // �� ���� ��������� �� ���� - ����� ����� ����� ����� ������ �������
  int nop(void*, Message*) {return 1; };
}
// "����� ��������" ����������� ������� �������, ������������ ����� � �����
// �� ����� ������ ������� ����������� - ����� ��� ������� ������� �������,
// ���� ����������� ��������� �� ������.
template <class T, int (T::*PMethod)(Message*)>
void make_callback(void* ptr) {
  (reinterpret_cast<T*>(ptr)->*PMethod)();
};
typedef int (*PFUN)(void*, Message*);

// class EHandler
// ������ ��������� �� ������� ������� � ���������������� ������;
// ��� �������-������ "����� ��������" ���������� ������� �������-�������.
// NOTE: ����������� ������������ �����������: �����������
// ����������� ������������ ����������� ����������� �� ���������, �� ��� �����
// �����c��� �� ������� disconnect.
class EHandler
{
public:
private:
  PFUN    _act;     // pointer to user on_signal function
  void*     _data;    // pointer to user data structure
public:
  EHandler(PFUN f = &nop, void* obj = 0): _act(f), _data(obj) {};
  ~EHandler(){
    _act = &nop;      // ����� ��������������� ������� �� ����� ���������
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