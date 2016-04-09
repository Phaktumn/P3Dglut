#include "gl/freeglut.h"
#include <string>
#include "../Vars/vec3f.h"

#define RICH_TEXT 0

#pragma once

class RenderText
{
public:
	RenderText();
	GLvoid drawText(const std::string& text, 
		const vec::Vector3& position, float scale);
private:
	vec::Vector3 rgb;
	const unsigned char* string;
};

