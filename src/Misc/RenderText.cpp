#include "RenderText.h"


RenderText::RenderText() : windowWidth(0), windowHeight(0)
{
	rgb = new vec::Vector3(0, 0, 0);
}

GLvoid RenderText::drawText(const char text[], vec::Vector3* position, float scale)
{
	for (size_t i = 0; i < strlen(text); i++){
		str[i] = text[i];
	}

	//espessura da linha
	glLineWidth(2.0);

	////Suavizar a font!
#if RICH_TEXT 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
#endif


	glViewport(0, 0, this->windowWidth, this->windowHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0, static_cast<double>(this->windowWidth), 
		0.0, static_cast<double>(this->windowHeight));
	glTranslatef(0.0, this->windowHeight, 0.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(position->x, -position->y, position->z);
	glColor3f(rgb->x, rgb->y, rgb->z);
	glScalef(scale, scale, scale);
	
	for (size_t i = 0; i < strlen(str); i++) glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	delete position;
	glFlush();
}

GLvoid RenderText::setWindowHeight(float height)
{
	this->windowHeight = height;
}

GLvoid RenderText::setWindowWidth(float width)
{
	this->windowWidth = width;
}
