#pragma once
#include "gl/freeglut.h"

namespace vec{
	class Vector3;
}

struct light
{
	GLfloat mat_specular[4];
	GLfloat mat_shininess[1];
	GLfloat mat_emission[4];
	GLfloat mat_diffuse[4];
};

class Lightning
{
public:
	static void enableLight();
	static void applyMaterial1();
	static void applyMaterial2();
	static void applyLights();
};

