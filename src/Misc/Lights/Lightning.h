#pragma once
#include "gl/freeglut.h"

namespace vec{
	class Vector3;
}

class Lightning
{
public:
	explicit Lightning(int enable);
	~Lightning();

	void setAmbientColor(vec::Vector3 ambient_rgb, GLfloat alpha);
	void setDiffuse(vec::Vector3 diffuse_rgb, GLfloat alpha);
	void setSpecular(vec::Vector3 specular_rgb, GLfloat alpha);

	void setLightPosition(vec::Vector3 position);

	int isEnabled() const;
	void enableLight() const;

	GLfloat light_ambient[4];
	GLfloat light_diffuse[4];
	GLfloat light_specular[4];
	GLfloat light_position[4]; 
	GLfloat mat_ambient_and_diffuse[4];
	GLfloat mat_specular[4];
	GLfloat mat_shininess[1];

private:
	int array_size = 4;
	int enable = 0;
};

