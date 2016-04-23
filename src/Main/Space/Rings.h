#define RINGS_H
#ifdef RINGS_H

#pragma once

#include <Misc/Lights/Lightning.h>
#include <Main/LoadBMP.h>
#include <Main/Space/Planets/Planet.h>

class Ring
{
public:
	Ring(GLfloat innerRing, GLfloat outterRing ,GLuint slices, GLuint loop);
	~Ring();

	void load();
	void draw(Planet& planet) const;
	void attachToPlanet(Planet& planet) const;

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

inline void Ring::draw(Planet& planet) const
{
	glPushMatrix();
	glTranslatef(planet.getPositionVec().x, planet.getPositionVec().y, planet.getPositionVec().z);
	glScalef(planet.getScale(), planet.getScale(), planet.getScale());
	glBindTexture(GL_TEXTURE_2D, textureId);
	glCallList(listIndex);
	glPopMatrix();
}

inline void Ring::attachToPlanet(Planet& _planet) const
{
	glNewList(listIndex, GL_COMPILE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Lightning::applyMaterial1();
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	glRotatef(_planet.getPlanetInclination(), 0, -1, 0);
	gluDisk(m_ring, m_InnerRadius, m_OutterRadius, slices, loops);
	glPopMatrix();
	glEndList();
}

inline void Ring::loadTexture()
{
	textureId = _loadBMP("Textures/rings.bmp");
}
#endif
