#include <GL/glut.h>

const int WIN_WID = 512;
const int WIN_HEI = 512;

class Object
{
public:
	virtual void Draw() = 0;
};

class Platform : public Object
{
private:
	float x, len, speed;
public:	
	Platform(float _x = WIN_WID / 2, float _len = 32, float _speed = 16) : x(_x), len(_len), speed(_speed) {};
	virtual void Draw();
	void IncreaseLen();
	void Reset();
	void Move(int);
};

class Ball: public Object
{

private:
	float x, y, dx, dy, speed;
	
public:
	Ball(float _x = WIN_WID / 2, float _y = WIN_HEI - 25, float _speed = 8) : x(_x), y(_y), speed(_speed) , dx(0), dy(0) {};
	virtual void Draw();
	void SetDX(int _dx) { this->dx = _dx; }
	void SetDY(int _dy) { this->dy = _dy; }
	void Reset();
	int Move();
};


