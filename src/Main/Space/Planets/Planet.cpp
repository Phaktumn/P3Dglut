#include "Planet.h"
#include <Misc/Lights/Lightning.h>
#include <Main/LoadBMP.h>
#include <Vars/EulerAngle.h>
#include <Main/Space/Rings.h>
#include <Main/FreeGlutWrap.h>

GLuint Planet::list;

Planet::Planet(): m_OrbitList(0), ring(nullptr), m_orbitInclination(0), m_idtexture(0), m_Aphelion(0), 
m_rotation(0), m_orbit_Angle(0), m_Orbit_Duration(0), m_Rotation_Duration(0), planetInclination(0), m_eccentricity(0)
{
}

Planet::Planet(const std::string& texturePath, const  std::string& name,
	float orbitDuration, float rotatioDuration, float eccentricity, 
	const Vector3& position, float scale, float orbitInclination, float planetInclnation) :
	m_OrbitList(0), ring(nullptr), m_idtexture(0), m_Aphelion(abs(position.z)),
	m_rotation(0), m_orbit_Angle(45), planetInclination(planetInclnation), m_eccentricity(eccentricity)
{
	m_Name = name;
	this->m_Position = Vector3(0,0,0);
	this->m_Orbit_Duration = orbitDuration;
	this->m_Rotation_Duration = rotatioDuration;
	m_scale = scale;
	m_texture_path = texturePath;
	m_orbitInclination = orbitInclination;
}

Planet::~Planet()
{
	//Delete all moons
	for (size_t i = 0; i < moons.size(); i++){
		delete moons[i];
	}
	free(sphere);
	delete ring;
}

void Planet::Load()
{
	loadTexture();

	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(  sphere, GL_TRUE);
	gluQuadricNormals(  sphere, GLU_SMOOTH);

	list = glGenLists(1);

	glNewList(list, GL_COMPILE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	Lightning::applyMaterial1();
	//Rodar o planeta para a textura parecer legit XD
	_glRotatef(90, Vector3(1,0,0));
	gluSphere(sphere, 1, 35, 35);
	glEndList();

	//Generate All orbit vertices
	for (float i = 0.0f; i <= 360.0f; i += 1) {
		float m = MathHelper::ToRadians(i);
		orbitVerices.push_back(
			Vector3(cos(m) * calculateKeplerOrbit(m) + calculateHeight(0.01f, m).x,
				calculateHeight(0.01f, m).y,
				sin(m)* calculateKeplerOrbit(m) + calculateHeight(0.01f, m).z));
	}

	m_OrbitList = glGenLists(1);

	glNewList(m_OrbitList, GL_COMPILE);
	glDisable(GL_LIGHTING);
	glBegin(GL_LINE_STRIP);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (int i = 0; i < orbitVerices.size(); i++){
		_Vertex3(orbitVerices[i]);
	}
	glDisable(GL_BLEND);
	glEnd();
	glEnable(GL_LIGHTING);
	glEndList();
}

float Planet::calculateKeplerOrbit(float radians)
{
	float semiLatus = m_Aphelion * (1 - m_eccentricity);
	float keplerOrbit = semiLatus / (1 + m_eccentricity * cos(radians));
	//just filter and set class variable m_... to keplerOrbit
	m_KeplerOrbitDistance = keplerOrbit;
	return keplerOrbit;
}

Vector3 Planet::calculateHeight(float deltaTime, float radians) const
{
	//Pitch max = orbit Inclination
	/*= MathHelper::ToRadians(m_orbitInclination)*/
	float maxHeigth = m_orbitInclination * m_Aphelion / 45.0f;
	float radians_Pitch = MathHelper::ToRadians(m_orbitInclination);
	EulerAngle inclination = EulerAngle(radians, radians_Pitch, 0.0f);
	Vector3 inc = inclination.toVector3();
	inc.y *= maxHeigth;
	return inc;
}

void Planet::Simulate(float deltaTime)
{
	//If is Sun -> just dont Simulate 
	//rotation Duration and orbit Duration == 0
	if (m_Rotation_Duration == 0 && m_Orbit_Duration == 0){
		return;
	}
	
    m_rotation += deltaTime * 360.0f / m_Rotation_Duration;
	if (m_rotation >= 360.0f) 
	{
		m_rotation -= 360;
		m_days_elapsed++;
	}

	float orbitDeltaStep = 360 / m_Orbit_Duration;
	m_orbit_Angle += deltaTime * orbitDeltaStep;
	if (m_orbit_Angle > 360)
	{
		m_years_elapsed++;
		m_orbit_Angle -= 360;
	}

	float radians = MathHelper::ToRadians(m_orbit_Angle);
	
	m_Position.x = cos(radians) *  calculateKeplerOrbit(radians)
		+ calculateHeight(deltaTime, radians).x;
	m_Position.y = calculateHeight(deltaTime, radians).y;
	m_Position.z = sin(radians) * calculateKeplerOrbit(radians) 
		+ calculateHeight(deltaTime, radians).z;

	//Dont Update Moons if moon list is equals to zero
	if (m_moon_index == 0) return;
	for (size_t i = 0; i < moons.size(); i++){
		moons[i]->Update(deltaTime);
	}
}

void Planet::Draw()
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
	glBindTexture(GL_TEXTURE_2D, m_idtexture);
	glCallList(list);
    glPopMatrix();
	if(ring != nullptr)
		ring->draw(*this);

	//Enable Light Again!
	if (m_Rotation_Duration == 0 && m_Orbit_Duration == 0)
		glEnable(GL_LIGHTING);

	//Dont Draw Moons if moon list size is equal to zero
	if (m_moon_index == 0) return;
	//Else draw this planet moons
	for (size_t i = 0; i < moons.size(); i++) {
		moons[i]->Draw();
	}
}

void Planet::loadTexture()
{
	m_idtexture = _loadBMP(m_texture_path.c_str());
	 /*if (LoadTGA(&m_texture, const_cast<char*>(m_texture_path.c_str()))) {
		glGenTextures(1, &m_texture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, m_texture.texID / 8, m_texture.width,
			m_texture.height, 0, m_texture.type, GL_UNSIGNED_BYTE, m_texture.imageData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		IO::printMessage(std::string("Texture: " + m_texture_path + " Loaded sucesfully"));
		if(m_texture.imageData) {
			free(m_texture.imageData);
			IO::printMessage(std::string("Image Data freed"));
		}
	}
	else
	{
		IO::printError(std::string("TEXTURE NOT FOUND"));
	}*/
}

void Planet::addMoon(float distanceToPlantet, float radius)
{
	if (distanceToPlantet < m_scale) {
		distanceToPlantet = m_scale + 5;
	}
	moons.push_back(new Moon(*this, distanceToPlantet, radius, 0.0f));
	moons[m_moon_index]->Load();
	m_moon_index++;
}

void Planet::renderOrbit() const
{
	glDisable(GL_TEXTURE_2D);

	//Draw Planets Orbit Lists
	glCallList(m_OrbitList);

	//No moons just return
	if (m_moon_index == 0) return;
	//esle push new matrix and draw moon's orbits
	glPushMatrix();
	_glTranslate(m_Position);
	for (size_t i = 0; i < moons.size(); i++){
		moons[i]->renderOrbit();
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

std::string& Planet::planetSettigs()
{
	m_planetSettings = "Name: "                  + m_Name;
	m_planetSettings += "\n Position: "          + getPosition();
	m_planetSettings += "\n Distance to Sun: "   + std::to_string(m_KeplerOrbitDistance)              + "Mill km";
	m_planetSettings += "\n Rotation: "          + std::to_string(m_rotation);
	m_planetSettings += "\n Orbit Angle: "       + std::to_string(m_orbit_Angle);
	m_planetSettings += "\n Orbit Duration: "    + std::to_string(int(m_Orbit_Duration))              + " Earth Days";
	if(m_Rotation_Duration < 1.0f) 
		m_planetSettings +=  "\n Day Duration: " + std::to_string(double(m_Rotation_Duration * 24))   + " Earth Hours";
	else m_planetSettings += "\n Day Duration: " + std::to_string(int(m_Rotation_Duration))           + " Earth Days";
	m_planetSettings += "\n Days Elapsed on "    + m_Name + ": " + std::to_string(m_days_elapsed)     + " Days";
	m_planetSettings += "\n Years Elapsed on "   + m_Name + ": " + std::to_string(m_years_elapsed)    + " Years";
	
	return {m_planetSettings};
}

void Planet::addRings(float innerRadius, float outterRadius)
{
	ring = new Ring(innerRadius, outterRadius, 50, 1);
	ring->load();
	ring->attachToPlanet(*this);
}
