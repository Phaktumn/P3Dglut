#include "UniverseObject.h"
#include <Main/LoadBMP.h>
#include <Misc/Lights/Lightning.h>
#include <Main/FreeGlutWrap.h>
#include <Vars/EulerAngle.h>

UniverseObject::UniverseObject(const string& texturePath, const string& name, float orbitDuration, float rotationDuration, float eccentricity, 
	const Vector3& pos, float scale, float orbitInclination, float planetInclination) :
	list(0), m_idtexture(0), m_OrbitList(0), m_Aphelion(abs(pos.z)), m_rotation(0), m_orbit_Angle(0), planetInclination(planetInclination)
{
	m_Name = name;
	m_Position = Vector3(0, 0, 0);
	m_Orbit_Duration = orbitDuration;
	m_Rotation_Duration = rotationDuration;
	m_scale = scale;
	m_texture_path = texturePath;
	m_orbitInclination = orbitInclination;
	m_eccentricity = eccentricity;
	m_Position = pos;
	m_CurrPlanetInc = planetInclination;
}

void UniverseObject::load()
{
	if (sphere == nullptr) {
		IO::printError("No sphere was set! unable to continue...");
		exit(1);
	}
	
	loadTexture();

	/* This List will Render the spheres */
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Lightning::applyMaterial1();
	//Rodar o planeta para a textura parecer legit XD
	_glRotatef(90, Vector3(1, 0, 0));
	gluSphere(sphere, 1, 35, 35);
	glEndList();

	//Generate All orbit vertices
	for (float i = 0.0f; i <= 360.0f; i += 1) {
		float m = MathHelper::ToRadians(i);
		m_orbitVertexes.push_back(
			Vector3(cos(m) * calculateKeplerOrbit(m) + calculateHeight(m).x, 
				calculateHeight(m).y, 
				sin(m)* calculateKeplerOrbit(m) + calculateHeight(m).z));
	}

	/* This List will render the orbits */
	m_OrbitList = glGenLists(1);
	glNewList(m_OrbitList, GL_COMPILE);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_STRIP);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (int i = 0; i < m_orbitVertexes.size(); i++) {
		_Vertex3(m_orbitVertexes[i]);
	}
	glDisable(GL_BLEND);
	glEnd();
	glEnable(GL_LIGHTING);
	glEndList();
}

void UniverseObject::simulate(float deltaTime)
{
	//If is static -> just dont Simulate 
	//rotation Duration and orbit Duration == 0
	if (m_Rotation_Duration == 0 && m_Orbit_Duration == 0)  return;
	//ELSE ->
	m_rotation += deltaTime * 360.0f / m_Rotation_Duration;
	if (m_rotation >= 360.0f) m_rotation -= 360;
	float orbitDeltaStep = 360 / m_Orbit_Duration;
	m_orbit_Angle += deltaTime * orbitDeltaStep;
	if (m_orbit_Angle > 360) m_orbit_Angle -= 360;
	float radians = MathHelper::ToRadians(m_orbit_Angle);
	m_Position.x = cos(radians) * calculateKeplerOrbit(radians) + calculateHeight(radians).x;
	m_Position.y = calculateHeight(radians).y;
	m_Position.z = sin(radians) * calculateKeplerOrbit(radians) + calculateHeight(radians).z;
}

void UniverseObject::draw()
{
	//Disable light if its sun time to get draw
	if (m_Rotation_Duration == 0 && m_Orbit_Duration == 0)
		glDisable(GL_LIGHTING);
	glPushMatrix();
	_glTranslate(m_Position);
	_glRotatef(planetInclination, Vector3(0, 0, 1));
	_glRotatef(m_rotation, Vector3(0, -1, 0));
	_glRotatef(90, Vector3(0, 1, 0));
	_Scale(Vector3(m_scale));
	_BindTexture(m_idtexture);
	glCallList(list);
	glPopMatrix();
	//Enable Light Again!
	if (m_Rotation_Duration == 0 && m_Orbit_Duration == 0)
		glEnable(GL_LIGHTING);
}

void UniverseObject::renderOrbit() const
{
	//Draw Orbit List
	glCallList(m_OrbitList); 
}

void UniverseObject::loadTexture()
{
	m_idtexture = _loadBMP(m_texture_path.c_str());
}

float UniverseObject::calculateKeplerOrbit(float radians)
{
	float semiLatus = m_Aphelion * (1 - m_eccentricity);
	float keplerOrbit = semiLatus / (1 + m_eccentricity * cos(radians));
	//just filter and set class variable m_... to keplerOrbit
	m_KeplerOrbitDistance = keplerOrbit;
	return keplerOrbit;
}

Vector3& UniverseObject::calculateHeight(float angle_x)
{
	float radians_Pitch = MathHelper::ToRadians(m_orbitInclination);
	EulerAngle inclination = EulerAngle(angle_x, radians_Pitch, 0.0f);
	Vector3 inc = Vector3(0, calculateKeplerOrbit(angle_x) * inclination.toVector3Inv().y, 0);
	return inc;
}
