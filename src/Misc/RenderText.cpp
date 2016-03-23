#include "RenderText.h"
#include "../Vars/vec3f.h"

RenderText::RenderText()
{
	rgb = vec::Vector3(1, 1, 1);
}

GLvoid RenderText::drawText(std::string& text, vec::Vector3& position, float scale) const
{
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
	glPushMatrix();
	glLoadIdentity();

	//espessura da linha
	glLineWidth(2.0);

	glTranslatef(position.x, position.y, 0);
	glColor3f(rgb.x, rgb.y, rgb.z);
	glScalef(scale, scale, 1);
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*)text.c_str());
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glLineWidth(1.0);
}
