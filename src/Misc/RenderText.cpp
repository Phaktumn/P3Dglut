#include "RenderText.h"
#include "../Vars/vec3f.h"

RenderText::RenderText(const vec::Vector3& position, float scale): string(nullptr)
{
	rgb = vec::Vector3(1, 1, 1);
	m_text_list = glGenLists(2);
	m_Position = position;
	m_scale = scale;
	initList(m_Position, m_scale);
}

GLvoid RenderText::drawText(const std::string& text)
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE);
	string = reinterpret_cast<const unsigned char*>(text.c_str());
	////Suavizar a font!
#if RICH_TEXT 1
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
#endif
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glCallList(m_text_list + 1);
	//glLoadIdentity();
	//gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH),
		//0.0, glutGet(GLUT_WINDOW_HEIGHT));
	//glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	glLoadIdentity();

	//espessura da linha
	glLineWidth(2.0);

	glCallList(m_text_list);
	glutBitmapString(GLUT_BITMAP_9_BY_15, string);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE);
	glLineWidth(1.0);
}

void RenderText::initList(const vec::Vector3& position, float scale) const
{
	glNewList(m_text_list, GL_COMPILE);
	glScalef(scale, scale, 1);
	glColor3f(rgb.x, rgb.y, rgb.z);
	glRasterPos2f(position.x, position.z);
	glEndList();

	glNewList(m_text_list + 1, GL_COMPILE);
	glLoadIdentity();
	gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH),
		0.0, glutGet(GLUT_WINDOW_HEIGHT));
	glMatrixMode(GL_MODELVIEW);
	glEndList();
}
