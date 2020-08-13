#include "Primitives.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

using namespace std;



vector <shared_ptr<Object>> objects;
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
		cout << "<-\n";
		player->Move(-1);
		break;
	case GLUT_KEY_RIGHT:
		if (GAME_ON_PAUSE) {
			GAME_ON_PAUSE = false;
			ball->SetDX(1);
			ball->SetDY(-1);
		}
		cout << "->\n";
		player->Move(1);
		break;
	}
}

void Timer(int value)
{
	glColor3f(1.0, 1.0, 1.0);
	if (ball->Move() != 0) {
		GAME_ON_PAUSE = true;
		player->Reset();
		ball->Reset();
	}
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}


void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& i : objects) {
		i->Draw();
	}
	glutSwapBuffers();
}

int main(int argc, char* argv[]){

	objects.clear();
	auto p = new Platform();
	auto b = new Ball();

	objects.emplace_back(p);
	objects.emplace_back(b);
	player = p;
	ball = b;


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