#define RENDER_TEXT_H
#ifdef RENDER_TEXT_H

#include "gl/freeglut.h"
#include <string>
#include "../Vars/vec3f.h"

#define RICH_TEXT 0

#pragma once

class RenderText
{
public:
	RenderText(const vec::Vector3& position, float scale);
	GLvoid drawText(const std::string& text);
private:

	vec::Vector3 m_Position;
	float m_scale;

	void initList(const vec::Vector3& position, float scale) const;

	vec::Vector3 rgb;
	const unsigned char* string;
	GLuint m_text_list;
};

#endif


