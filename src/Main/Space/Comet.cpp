#include "Comet.h"
#include <Main/LoadBMP.h>
#include <Misc/Lights/Lightning.h>
#include <Main/FreeGlutWrap.h>

Comet::Comet(const std::string& texturePath, const  std::string& name, 
	const vec::Vector3& position, const float m_eccentricity, 
	const float m_orbit_duration, const float m_rotation_duration, float scale): 
	m_isSelected(false), m_orbitInclination(0), m_idtexture(0),m_eccentricity{m_eccentricity},
	m_orbitDuration{m_orbit_duration},m_rotationDuration{m_rotation_duration},
	m_size(0), m_orbit_Angle(0)
{
	m_Aphelion = position.z;
	m_Name = name;
	m_Position = position;
	m_size = scale;
	m_Texture_Path = texturePath;
}

void Comet::load()
{
	m_idtexture = _loadBMP(m_Texture_Path.c_str());

	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

	list = glGenLists(1);

	glNewList(list, GL_COMPILE);
	Lightning::applyMaterial1();
	gluSphere(sphere, 1, 15, 15);
	glEndList();

	//Orbit Inclination not implemented yet
	m_orbitInclination = 10;

	//Generate All orbit vertices
	for (float i = 0.0f; i <= 360.0f; i += 1) {
		float m = MathHelper::ToRadians(i);
		orbitVerices.push_back(vec::Vector3(cos(m) * calculateKeplerOrbit(m),
			m_Position.y, sin(m) * calculateKeplerOrbit(m)));
	}

	m_OrbitList = glGenLists(1);

	glNewList(m_OrbitList, GL_COMPILE);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_STRIP);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (int i = 0; i < orbitVerices.size(); i++) {
		_Vertex3(orbitVerices[i]);
	}
	glDisable(GL_BLEND);
	glEnd();
	glEnable(GL_LIGHTING);
	glEndList();
}

void Comet::simulate(float simulationDelta)
{
	m_orbit_Angle += simulationDelta * 360 / m_orbitDuration;
	if (m_orbit_Angle >= 360) {
		m_orbit_Angle -= 360;
	}

	float radians = MathHelper::ToRadians(m_orbit_Angle);

	m_Position.x = cos(radians) * calculateKeplerOrbit(radians);
	m_Position.y = 0;
	m_Position.z = sin(radians) * calculateKeplerOrbit(radians);
}

void Comet::draw() const
{
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	_glTranslate(m_Position);
	//Rodar o planeta para a textura parecer legit XD
	_glRotatef(90, Vector3(1,0,0));
	_Scale(Vector3(m_size));
	glBindTexture(GL_TEXTURE_2D, m_idtexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glCallList(list);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void Comet::renderOrbit() const
{
	glDisable(GL_TEXTURE_2D);
	//Draw Comet Orbit List
	glCallList(m_OrbitList);
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

float Comet::calculateKeplerOrbit(float radians)
{
	float semiLatus = m_Aphelion * (1 - m_eccentricity);
	float keplerOrbit = semiLatus / (1 + m_eccentricity * cos(radians));
	//just filter and set class variable m_... to keplerOrbit
	m_KeplerOrbitDistance = keplerOrbit;
	return keplerOrbit;
}
