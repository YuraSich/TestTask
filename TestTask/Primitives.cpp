#include "Primitives.h"
#include<math.h>


void Platform::Draw(){
	glBegin(GL_QUADS);
	glVertex2f(this->x - this->len / 2, WIN_HEI - 20.0f);	// Слева вверху
	glVertex2f(this->x + this->len / 2, WIN_HEI - 20.0f);	// Справа вверху
	glVertex2f(this->x + this->len / 2, WIN_HEI - 10.0f);	// Справа внизу
	glVertex2f(this->x - this->len / 2, WIN_HEI - 10.0f);	// Слева внизу
	glEnd();
}

void Platform::IncreaseLen()
{
	this->len += 16;
}

void Platform::Reset() {
	this->x = WIN_WID / 2;
}

void Platform::Move(int ax) {
	if ((this->x + this->len / 2 >= WIN_WID && ax > 0) || (this->x - this->len / 2 <= 0 && ax < 0))
		return;
	this->x += ax * this->speed;
}

void Ball::Draw() {
	glBegin(GL_LINE_LOOP);
	for (float i = 0.0; i < 2 * 3.14; i += 3.14 / 12)
	{
		glVertex2f(this->x + 4 * sin(i), this->y +4 * cos(i));
	}
	glEnd();
}


void Ball::Reset() {
	this->dx = 0;
	this->dy = 0;
	this->y = WIN_HEI - 25;
	this->x = WIN_WID / 2;
	this->speed = 8;
}

int Ball::Move() {
	if (this->x + 2 >= WIN_WID)
		this->dx = -1;
	else if (this->x - 2 <= 0)
		this->dx = 1;
	if (this->y - 2 <= 0)
		this->dy = 1;
	if (this->y + 2 >= WIN_HEI)
		return 1;
	this->x += this->dx * this->speed;
	this->y += this->dy * this->speed;
	return 0;
}