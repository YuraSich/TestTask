#include "Premetives.h"


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

void Platform::Move(int ax) {
	if ((this->x + this->len / 2 >= WIN_WID && ax > 0) || (this->x - this->len / 2 <= 0 && ax < 0))
		return;

	this->x += ax * this->speed;
	
		

}