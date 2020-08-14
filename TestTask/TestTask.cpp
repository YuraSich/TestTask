#include "Primitives.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

using namespace std;



vector <Block*> blocks; 
Platform* player;
Ball* ball;
static bool GAME_ON_PAUSE = true;


void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIN_WID, WIN_HEI, 0, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}

void SKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: 
		if (GAME_ON_PAUSE) {
			GAME_ON_PAUSE = false;
			ball->SetDX(-1);
			ball->SetDY(-1);
		}
		player->Move(-1);
		break;
	case GLUT_KEY_RIGHT:
		if (GAME_ON_PAUSE) {
			GAME_ON_PAUSE = false;
			ball->SetDX(1);
			ball->SetDY(-1);
		}
		player->Move(1);
		break;
	}
}

void Restart() {
	GAME_ON_PAUSE = true;
	player->Reset();
	ball->Reset();
	blocks.clear();
	for (int ax = 0 + 52; ax < WIN_HEI - 52; ax += 52) {
		for (int ay = 0 + 32; ay < WIN_HEI / 2; ay += 32) {
			if (rand()%10 < 7) {
				blocks.emplace_back(new Block(ax, ay));
			}
		}
	}
}

void Timer(int value)
{
	glColor3f(1.0, 1.0, 1.0);
	ball->CheckCollision(player);
	for (auto& pointer : blocks)
	{
		if (ball->CheckCollision(pointer))
		{
			delete pointer;
			pointer = nullptr;
		}
	}
	blocks.erase(remove(blocks.begin(), blocks.end(), nullptr), blocks.end());
	if (ball->Move() != 0 || blocks.empty()) {
		Restart();
	}
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}


void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	player->Draw();
	ball->Draw();
	for (auto& i : blocks) {
		i->Draw();
	}
	glutSwapBuffers();
}

int main(int argc, char* argv[]){

	auto p = new Platform();
	auto b = new Ball();

	player = p;
	ball = b;

	Restart();


	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WID, WIN_HEI);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Metelkin");

	glutSpecialFunc(SKeyboard);

	glutDisplayFunc(Draw);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Initialize();

	glutTimerFunc(50, Timer, 0);

	glutMainLoop();
}