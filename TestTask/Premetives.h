#include <GL/glut.h>


class Object
{
public:
	virtual void Draw() = 0;
private:

};

class Platform : Object
{
public:
	float x, len;
	void Draw();
	Platform(float _x = 300, float _len = 20) : x(_x), len(_len) {};
};