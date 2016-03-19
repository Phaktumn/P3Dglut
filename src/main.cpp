#include "../src/Main/Game.h"

//void createRotation(float x, float y, float z)
//{
//	if (x < 0) x == 0; else x == 1;
//	if (y < 0) y == 0; else y == 1;
//	if (z < 1) z == 0; else z == 1;
//	static float angle;
//	angle = 90.0 * deltaTime;
//	glRotatef(angle, x, y, z);
//	glRotatef(std::cos(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 100, 0, 1, 0);
//	glRotatef(std::sin(glutGet(GLUT_ELAPSED_TIME) * 0.001) * 100, 1, 0, 0);
//}
//
//void prespectiveView() {
//	static int startTime = glutGet(GLUT_ELAPSED_TIME);
//
//	glLoadIdentity();
//	gluLookAt(camPos.X, camPos.Y, camPos.Z, 
//		      0.0, 0.0, 0.0, 
//		      0.0, 1.0, 0.0);
//	
//	//createRotation(0, 1, 0);
//
//	glColor3f(0.5, 0.1, 0.8);
//	glutWireTeapot(1);
//
//	glColor3f(0.0, 0.2, 1.0);
//	glScalef(5.0, 5.0, 5.0);
//	glutWireOctahedron();
//
//	deltaTime = (glutGet(GLUT_ELAPSED_TIME) - startTime) * 0.001;
//}
//
//void testDraw() {
//	//Draw Lines
//	glBegin(GL_LINES);
//	glColor3f(0.3, 1.0, 0.0);
//	glVertex3f(0.0, 1.0, 0.0);
//	glVertex3f(0.0, 0.0, 0.0);
//	glEnd();
//
//	//Draw Line Strip
//	glBegin(GL_LINE_STRIP);
//	glColor3f(1.0, 0.2, 0.6);
//	glVertex3f(-1.0, -1.0, 0.0);
//	glVertex3f(-0.5, 0.0, 0.0);
//	glVertex3f(-0.5, -0.5, 0.0);
//	glEnd();
//
//	//Draw Line Loop
//	glBegin(GL_LINE_LOOP);
//	glColor3f(0.0, 0.0, 1.0);
//	glVertex3f(-0.5, 0.5, 0.0);
//	glVertex3f(-0.5, -0.5, 0.0);
//	glVertex3f(0.0, 0.0, 0.0);
//	glEnd();
//
//	//Draw Triangle
//	glBegin(GL_TRIANGLES);
//	glColor3f(1, 1, 1);
//	glVertex3f(0.0, 1, 0.0);
//	glColor3f(0, 1, 0);
//	glVertex3f(-1, 0.0, 0.0);
//	glColor3f(0, 0.0, 1);
//	glVertex3f(1, 0.0, 0.0);
//	glEnd();
//}

int main(int argc, char **argv) 
{
	auto game = Game::getInstance(argc, argv);
    return game->start(600, 800, "A game! tho");
}