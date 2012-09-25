/*
  WINDOW

Summary:
  ���� ���������� (��� �����): � ���� ������ (view), � ���� ��������� ����
  �� ����� (������� �������) � ����������, � ��� �� � ��� ���������������
  ������������: �� ����� ����������� ����, ��������, ����������, �������...
  � �.�.
*/
#ifndef WINDOW_H
#define WINDOW_H
//----------------------------------------------------------------------------
#include "noncopyable.hpp"
#include "geometry.hpp"
#include "mouse.hpp"
//#include "ehandler.hpp"
//#include "keyboard.hpp"

struct WindowImpl;// platphorm-speciphic
class Window: NonCopyable
{
protected:
  WindowImpl*         _wimpl;
public:
  // ������� - ������������ ��� ����������� ����������������� �����������
  enum WndEvents {
    WE_Nothing = 0,
    WE_Should_close,  // ���� ����� ���� �������
    WE_Closed,        // ���� ���� �������
    WE_Resize,        // � ��� ����� maximize � normalise
    WE_Hide,          // ������ �������� � �������� ����
    WE_Show,          // ����� ���� �������� � �������� ����
    WE_Inactive,      // ��� �����, �� ����� ��������
    WE_Forse32   = 0xffffffff
  };
  enum MouseButton
  {
      MB_Left     = 0, // The left mouse button
      MB_Right    = 1, // The right mouse button
      MB_Middle   = 2, // The middle (wheel) mouse button
      MB_XButton1 = 3, // The first extra mouse button
      MB_XButton2 = 4, // The second extra mouse button
      MB_Count         // the total number of mouse buttons
  };
public:
  Window();
  virtual ~Window();

  operator bool() const {
    return _wimpl != 0;
  };

  // ������� ���� ���������� ������� � ��������� ����������
  bool create(int width, int height, const wchar_t* title);
  // ������� ���� �� ��������
  bool create(const wchar_t* resource_name);

  // ������� ����
  void close();

  // �������� ������� ����� � ����
  Pos& get_mouse_pos() const;
  // ��������� ��������� ������� �����
  // true ���� ������� ������
  bool is_mouse(MouseButton pressed) const;
  // TODO: keyboard

  // ���������� ����� ��������� ����
  void set_title(const wchar_t* title);
  // TODO: ������ � ������ ��� ��������� ������� ����... �����...

  // TODO: ������� � ��������
};

//----------------------------------------------------------------------------
#endif // WINDOW_H