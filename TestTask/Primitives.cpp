#include "Primitives.h"


void Platform::Draw(){
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(this->x - this->len / 2, this->y - 4);	// ����� ������
	glVertex2f(this->x + this->len / 2, this->y - 4);	// ������ ������
	glVertex2f(this->x + this->len / 2, this->y + 4);	// ������ �����
	glVertex2f(this->x - this->len / 2, this->y + 4);	// ����� �����
	glEnd();
}


void Platform::Reset() {
	this->x = WIN_WID / 2;
}

// ax - ����������� (>0 - ������/ <0 �����)
// �������� ������������ ��� ��������� �������� (�� �����������)
void Platform::Move(int ax) {
	if ((this->x + this->len / 2 >= WIN_WID && ax > 0) || (this->x - this->len / 2 <= 0 && ax < 0))
		return;
	this->x += ax * this->speed;
}

void Ball::Draw() {
	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	for (float i = 0.0; i < 2 * 3.14; i += 3.14 / 12)
	{
		glVertex2f(this->x + this->r * sin(i), this->y + this->r * cos(i));
	}
	glEnd();
}


void Ball::Reset() {
	this->dx = 0;
	this->dy = 0;
	this->y = WIN_HEI - 30;
	this->x = WIN_WID / 2;
	this->speed = 4;
}

// ���������� 1 - � ����� ������� ������ ������ ����
// � ��������� ������� 0
int Ball::Move() {
	// ��������� �������� �� ��������
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


// ��������� ������������ � �������
//
// return	true -  ���� ������������
//			false - ���
//
//TODO �������� ���������� ������������ � ������ �����
//TODO �� ������ ��������� �������� �������� � ����� ������� ����� ����������� ���
bool Ball::CheckCollision(Object* o) {
	float x_right, x_left, y_top, y_bot;
	x_right = o->GetX() + o->GetSX();
	x_left	= o->GetX() - o->GetSX();
	y_top	= o->GetY() - o->GetSY();
	y_bot	= o->GetY() + o->GetSY();

	if (this->x - this->r <= x_right &&
		this->x + this->r >= x_left && 
		this->y - this->r <= y_bot &&
		this->y + this->r >= y_top)
	{
		//TODO �� ������ ����������� �� ����� ������, ���� ������� �����������
		if (x_left < this->x && this->x < x_right)
			this->dy = -this->dy;
		if (y_top < this->y && this->y < y_bot)
			this->dx = -this->dx;
		return true;
	}
	return false;

}



void Block::Draw()
{
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2f(this->x - this->sizeX / 2, this->y - this->sizeY / 2);	// ����� ������
	glVertex2f(this->x + this->sizeX / 2, this->y - this->sizeY / 2);	// ������ ������
	glVertex2f(this->x + this->sizeX / 2, this->y + this->sizeY / 2);	// ������ �����
	glVertex2f(this->x - this->sizeX / 2, this->y + this->sizeY / 2);	// ����� �����
	glEnd();
}
