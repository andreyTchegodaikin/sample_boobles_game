/*
  NONCOPYABLE
Summary:
  �� ������: �����, ��������������� �� �����, ����� ������������.
  ������ � boost.
*/
#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class NonCopyable
{
 protected:
    NonCopyable() {}
    ~NonCopyable() {}
 private:  // emphasize the following members are private
    NonCopyable( const NonCopyable& );
    const NonCopyable& operator=( const NonCopyable& );
};

#endif // NONCOPYABLE_H