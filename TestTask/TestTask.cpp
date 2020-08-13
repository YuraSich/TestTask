#include "Premetives.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

using namespace std;



vector <shared_ptr<Object>> objects;
Platform* player;


void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIN_WID, WIN_HEI, 0, -200.0, 200.0);
	glMatrixMode(GL_MODELVIEW);
}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a': 
		cout << "<-\n";
		player->Move(-1);
		break;
	case 'd': 	
		cout << "->\n";
		player->Move(1);
		break;
	}
}


void SKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: 
		cout << "<-\n";
		player->Move(-1);
		break;
	case GLUT_KEY_RIGHT:
		cout << "->\n";
		player->Move(1);
		break;
	}
}

void Timer(int value)
{
	glColor3f(1.0, 1.0, 1.0);
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

	objects.emplace_back(p);
	player = p;


	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WID, WIN_HEI);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Metelkin");

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);

	

	glutDisplayFunc(Draw);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Initialize();
	glutTimerFunc(1, Timer, 0);
	glutMainLoop();
}