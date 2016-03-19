#include "SnowMan.h"
#include <GL/freeglut.h>
#include <iostream>

void SnowMan::drawSnowMan(int radius, int slices, float Color[10][3], int i)
{
	//cabeça
	glColor3f(Color[i][0], Color[i][1], Color[i][2]);
	glTranslatef(0, 1.5, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.5, slices, slices);

	//tronco
	glColor3f(Color[i][0], Color[i][1], Color[i][2]);
	glTranslatef(0, -1.5, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(radius, slices, slices);

	//olho1
	glColor3f(1.0, 0, 0);
	glTranslatef(0.2, 1.65, -0.4);
	glutSolidSphere(0.1, slices, slices);
	glTranslatef(-0.2, -1.65, 0.4);

	//olho2
	glPushMatrix();
	glColor3f(1.0, 0, 0);
	glTranslatef(-0.2, 1.65, -0.4);
	glutSolidSphere(0.1, slices, slices);

	//NOSE
	glPopMatrix();
	glTranslatef(0, 1.55, -0.4);
	glutSolidCone(0.1, -0.5, 10, 10);
}

void SnowMan::drawSnowMan(int radius, int slices)
{
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, 1.5, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.5, slices, slices);

	//tronco
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0, -1.5, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(radius, slices, slices);

	//olho1
	glColor3f(1.0, 0, 0);
	glTranslatef(0.2, 1.65, -0.4);
	glutSolidSphere(0.1, slices, slices);
	glTranslatef(-0.2, -1.65, 0.4);

	//olho2
	glPushMatrix();
	glColor3f(1.0, 0, 0);
	glTranslatef(-0.2, 1.65, -0.4);
	glutSolidSphere(0.1, slices, slices);
	glPopMatrix();

	//NOSE
	glTranslatef(0, 1.55, -0.4);
	glutSolidCone(0.1, -0.5, 10, 10);
}
