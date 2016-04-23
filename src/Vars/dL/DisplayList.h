#include "gl/freeglut.h"

#pragma once
class Object;

namespace vec{
	class Vector3;
}

class DisplayList
{
public:
	explicit DisplayList(GLuint listCount);
	~DisplayList();
	void GenPlane(GLenum begin_Enum, vec::Vector3 * rgb);
	void GenLandScape(GLenum begin_Enum, Object * model);

	void RenderModel(Object * model);

	GLuint getList(int index) const{
		return list + index;
	}

private:
	GLuint list;
	int index;
};

