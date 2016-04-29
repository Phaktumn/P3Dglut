#ifndef RINGS_H
#define RINGS_H

#pragma once

#include <Misc/Lights/Lightning.h>
#include <Main/LoadBMP.h>
#include <Main/Space/Planets/Planet.h>
#include <Main/FreeGlutWrap.h>

class Ring
{
public:
	Ring(GLfloat innerRing, GLfloat outterRing ,GLuint slices, GLuint loop);
	~Ring();

	void load();
	void draw(UniverseObject& planet) const;
	void attachToPlanet(UniverseObject& planet) const;

private:

	void loadTexture();
	GLUquadric* m_ring;

	GLuint listIndex;
	GLuint textureId;

	float m_InnerRadius;
	float m_OutterRadius;
	float slices;
	float loops;
};

inline Ring::Ring(GLfloat innerRadius, GLfloat outterRadius, GLuint slices, GLuint loop)
	: m_ring(nullptr), listIndex(0), textureId(0), m_InnerRadius(innerRadius), 
	m_OutterRadius(outterRadius), slices(slices), loops(loop)
{

}

inline Ring::~Ring()
{
	free(m_ring);
}

inline void Ring::load()
{
	loadTexture();

	listIndex = glGenLists(1);

	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	m_ring = gluNewQuadric();
	gluQuadricDrawStyle(m_ring, GLU_FILL);
	gluQuadricTexture(m_ring, GLU_TRUE);
	gluQuadricNormals(m_ring, GLU_SMOOTH);
}

inline void Ring::draw(UniverseObject& planet) const
{
	glPushMatrix();
	_glTranslate(planet.getPositionVec());
	_Scale(Vector3(planet.getScale()) * 115.0f);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glCallList(listIndex);
	glPopMatrix();
}

inline void Ring::attachToPlanet(UniverseObject& _planet) const
{
	glNewList(listIndex, GL_COMPILE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Lightning::applyMaterial1();
	glPushMatrix();
	_glRotatef(-90, Vector3(1,0,0));
	_glRotatef(_planet.getInclination(), Vector3(0, -1, 0));
	gluDisk(m_ring, m_InnerRadius, m_OutterRadius, slices, loops);
	glPopMatrix();
	glEndList();
}

inline void Ring::loadTexture()
{
	textureId = _loadBMP("Textures/rings.bmp");
}
#endif
