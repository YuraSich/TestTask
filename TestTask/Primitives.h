#include <GL/glut.h>
#include <math.h>

const int WIN_WID = 512;  //Ширина экрана
const int WIN_HEI = 512;  //Высота экрана

// Базовый класс для всех объектов на сцене
class Object {
 protected:
  float x, y;
  float sizeX, sizeY;

 public:
  virtual void Draw() = 0;
  float GetX() { return x; };
  float GetY() { return y; };
  float GetSX() { return sizeX; };
  float GetSY() { return sizeY; };
};

// Класс платформы - игрок
class Platform : public Object {
 private:
  float len, speed;

 public:
  Platform(float _x = WIN_WID / 2, float _len = 64, float _speed = 16,
           float _y = WIN_HEI - 16) {
    this->x = _x;
    this->y = _y;
    this->sizeX = len / 2;
    this->sizeY = 8;

    //
    this->len = _len;
    this->speed = _speed;
  };
  virtual void Draw();
  void Reset();
  void Move(int);
};

// Класс шарика
class Ball : public Object {
 private:
  float x, y, dx, dy, speed;
  float r;

 public:
  Ball(float _x = WIN_WID / 2, float _y = WIN_HEI - 30, float _speed = 8,
       float _r = 4)
      : x(_x), y(_y), speed(_speed), dx(0), dy(0), r(_r){};
  virtual void Draw();
  void SetDX(int _dx) { this->dx = _dx; }
  void SetDY(int _dy) { this->dy = _dy; }
  void Reset();
  int Move();
  bool CheckCollision(Object*);
};

// Класс блоков
class Block : public Object {
 private:
 public:
  Block(float _x, float _y, float _sx = 44, float _sy = 16) {
    this->x = _x;
    this->y = _y;
    this->sizeX = _sx;
    this->sizeY = _sy;
  }
  virtual void Draw();
};