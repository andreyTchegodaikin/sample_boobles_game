


class GameScene
{
  struct Ball
  {
    float _x, _y, _r;
  };
  Ball  _balls[32];
  int   _count;
  int   _timer;
  int   _time_left;
public:
  GameScene();
  ~GameScene();
  void reset_timer(int msec) {
    _timer = msec;
    _time_left = 0;
  };
  void render() {
    Ball* ptr = _balls;
    for(int i = 0; i < _count; ++i) {
    }
  };
  void update(double dt);
  void launch_ball(); // запуск нового м€чика в игру
};

GameScene(): _count(0){
}

~GameScene() {
}

void GameScene::launch_ball() {
}

void GameScene::update(double dt) {
  // таймер запуска новых шариков
  _time_left -= (int)(dt * 1000.0f);
  if(_time_left <= 0) {
    _time_left = _timer;
    launch_ball();
  }
  // пусть м€чики движутс€
}