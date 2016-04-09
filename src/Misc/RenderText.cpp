#include "RenderText.h"
#include "../Vars/vec3f.h"

RenderText::RenderText()
{
	rgb = vec::Vector3(1, 1, 1);
}

GLvoid RenderText::drawText(const std::string& text, 
	const vec::Vector3& position, float scale)
{
	string = reinterpret_cast<const unsigned char*>(text.c_str());
	////Suavizar a font!
#if RICH_TEXT 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
#endif
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH),
		0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_LIGHTING);

	glPushMatrix();
	glLoadIdentity();

	//espessura da linha
	glLineWidth(2.0);

	glScalef(scale, scale, 1);
	glColor3f(rgb.x, rgb.y, rgb.z);
	glRasterPos2f(position.x, position.z);
	glutBitmapString(GLUT_BITMAP_9_BY_15, string);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);

	glLineWidth(1.0);
}
