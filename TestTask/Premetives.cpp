#include "Premetives.h"

void Platform::Draw() {
	glBegin(GL_QUADS);
	glVertex3f(this->x - this->len / 2, 20.0f, 0.0f);	// ����� ������
	glVertex3f(this->x + this->len / 2, 20.0f, 0.0f);	// ������ ������
	glVertex3f(this->x + this->len / 2, 10.0f, 0.0f);	// ������ �����
	glVertex3f(this->x - this->len / 2, 10.0f, 0.0f);	// ����� �����
	glEnd();
}