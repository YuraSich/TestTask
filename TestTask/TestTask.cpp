#include "Primitives.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <vector>

using namespace std;
 
vector <Block*> blocks;		// Вектор Блоков
Platform* player;			// Игрок - платформа
Ball* ball;					// Шарик


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

	// Взависимости от первой нажатой кнопки шар примет то раправление и игра "снимается" с паузы
	//TODO По хорошему стоит передать ответственность за выбор направления какой-нибудь другой функции
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


//Новая игра
void Restart() {
	GAME_ON_PAUSE = true;
	player->Reset();
	ball->Reset();
	blocks.clear();
	
	// Создать новые блоки
	for (int ax = 0 + 52; ax < WIN_HEI - 52; ax += 52) {
		for (int ay = 0 + 32; ay < WIN_HEI / 2; ay += 32) {
			// Шанс, что блок появится 70%
			//TODO По хорошему, шанс должен хоть как-то меняться (Например от уровня сложности)
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
	glutTimerFunc(10, Timer, 0);
}


// Функция отрисовки кадра
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

	//Инициализация игрвой логики
	auto p = new Platform();
	auto b = new Ball();
	player = p;
	ball = b;
	Restart();

	//Инициализация графики
	glutInit(&argc, argv);
	glutInitWindowSize(WIN_WID, WIN_HEI);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Metelkin");
	glutSpecialFunc(SKeyboard);
	glutDisplayFunc(Draw);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Initialize();
	glutTimerFunc(10, Timer, 0);
	glutMainLoop();
}