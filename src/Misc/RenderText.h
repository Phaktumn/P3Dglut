#include "gl/freeglut.h"
#include <string>
#include "../Vars/vec3f.h"

#define RICH_TEXT 0

#pragma once

class RenderText
{
public:
	RenderText();
	GLvoid drawText(std::string& text, vec::Vector3& position, float scale) const;
private:
	vec::Vector3 rgb;
};

