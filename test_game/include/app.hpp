#ifndef APPLICATION_H
#define APPLICATION_H
//----------------------------------------------------------------------------
// ������� ����� ����������
// �������������:
// 1) ���������� ���� �����, ��������� Application
// 2) ���������� ������� get_app_instance
// �� ��������� ��� �������
class App
{
private:
  virtual void setup_videomem() {}; // specialy for LOST_DEVICE
  virtual void update() = 0;
  virtual void render() = 0;
  virtual void shutdown() = 0;
public:
  // ���������� ����� ������ ����������
  double get_time() const; // in seconds
  int run();
  void quit(int whith_error);
  virtual ~App();
};

// ��� ������� ������ ���������� ������������
// � � ��� ������������ ������ ���������������� ��� ����������
extern App* get_app_instance();
//----------------------------------------------------------------------------
#endif // APPLICATION_H