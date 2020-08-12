#include "Premetives.h"
#include <memory>
#include <vector>

using namespace std;

vector <unique_ptr<Object>> objects;

void Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& i : objects) {
		i->Draw();
	}
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutCreateWindow("Metelkin");

	auto player = make_unique<Object>(new Platform());
	objects.push_back(player);

	glutDisplayFunc(Draw);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glutMainLoop();
}