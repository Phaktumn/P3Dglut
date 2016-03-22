#pragma once
#include "gl/freeglut.h"
#include "src/Vars/vec3f.h"

class Traslate
{
public:
	static void Traslatef(vec::Vector3 pos)
	{
		return glTranslatef(pos.x, pos.y, pos.z);
	}
};

