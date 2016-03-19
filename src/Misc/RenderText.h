#include "../Vars/vec3f.h"
#include "gl/freeglut.h"

#define RICH_TEXT 0

#pragma once
class RenderText
{
public:
	RenderText();
	GLvoid drawText(const char text[], vec::Vector3* position, float scale);
	GLvoid setWindowHeight(float height);
	GLvoid setWindowWidth(float width);
private:
	vec::Vector3 * rgb;
	float windowWidth, windowHeight;
	char str[];
};

