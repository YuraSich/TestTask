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
public:
	float x, len, speed;
	Platform(float _x = WIN_WID / 2, float _len = 32, float _speed = 16) : x(_x), len(_len), speed(_speed) {};

	virtual void Draw();
	void IncreaseLen();
	void Move(int);
};