#include "DisplayList.h"
#include "../vec3f.h"
#include "../Object.h"

DisplayList::DisplayList(GLuint listCount): index(0)
{
	if (int(listCount) <= 0) listCount = 1;
	list = glGenLists(listCount);
	index = 1;
}


DisplayList::~DisplayList()
{

}

void  DisplayList::GenPlane(GLenum begin_Enum, vec::Vector3 * rgb)
{
	glNewList(list + index, GL_COMPILE);
	glBegin(begin_Enum);

	glColor3f(rgb->x, rgb->y, rgb->z);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);

	glEnd();
	glEndList();
	index++;
}

void DisplayList::GenLandScape(GLenum begin_Enum, Object * model)
{
	glNewList(list + index, GL_COMPILE);
	glBegin(begin_Enum);

	for (auto i = 0; i < 100; i += 20){
		for (auto u = 0; u < 100; u += 20){
			glPushMatrix();
			glTranslatef(i, 1.3f, u);
				model->renderModel();
			glPopMatrix();
		}
	}
	glEnd();
	glEndList();
	index++;
}

void DisplayList::RenderModel(Object* model)
{
	glNewList(list + index, GL_COMPILE);
	model->renderModel();
	glEnd();
	glEndList();
	index++;
}
