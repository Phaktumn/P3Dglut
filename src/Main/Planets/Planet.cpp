#include "Planet.h"
#include "SolarSystem.h"
#include "Moon.h"
#include "Misc/Debug/IO.h"
#include "../Game.h"
#include "Misc/imageloader.h"

Planet::Planet(const std::string& texturePath, const  std::string& name,
	float orbitDuration, float rotatioDuration, vec::Vector3& position, float scale) :
	m_idtexture(0), list(0), m_orbit_distance(abs(position.z)), m_rotation(0)
{
	this->m_Position = position;
	this->m_Orbit_Duration = orbitDuration;
	this->m_Rotation_Duration = rotatioDuration;
	m_orbit_Angle = 0;
	m_scale = scale;
	m_texture_path = texturePath;
}

Planet::~Planet()
{
	for (size_t i = 0; i < moons.size(); i++){
		delete(moons[i]);
	}
}

void Planet::Load()
{
	loadTexture();
}

void Planet::Simulate(float deltaTime)
{
	m_rotation += m_Rotation_Duration;
	if (m_rotation >= 360) { m_rotation -= 360; }
	m_orbit_Angle += 10 / m_Orbit_Duration;
	if (m_orbit_Angle >= 360) { m_orbit_Angle -= 360; }
	float radians = MathHelper::ToRadians(m_orbit_Angle);
	m_Position.x = cos(radians) * m_orbit_distance;
	m_Position.z = sin(radians) * m_orbit_distance;

	for (size_t i = 0; i < moons.size(); i++)
	{
		moons[i]->Update(deltaTime);
	}
}

void Planet::Draw() const
{
	Lightning::applyMaterial();
	glBindTexture(GL_TEXTURE_2D, m_idtexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	//Rodar o planeta para a textura parecer legit XD
	glRotatef(90, 1, 0, 0);
	glRotatef(m_rotation, 0, 0, -1);
	glScalef(m_scale, m_scale, m_scale);
	glCallList(SolarSystem::m_list + 1);
    glPopMatrix();

	for (size_t i = 0; i < moons.size(); i++) {
		moons[i]->Draw();
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Planet::loadTexture()
{
	Image* image = loadBMP(m_texture_path.c_str());	
	GLuint textureId;
	glGenTextures(1, &textureId);			 //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,       //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB,					      //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE,			  //GL_UNSIGNED_BYTE, because pixels are stored
									  //as unsigned numbers
		image->pixels);               //The actual pixel data
	m_idtexture = textureId;		  //Returns the id of the texture
	delete image;
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
	moons.push_back(new Moon(*this, distanceToPlantet, radius, 30));
	moons[m_moon_index]->Load();
	m_moon_index++;
}

void Planet::renderOrbit()
{
	glBegin(GL_LINE_STRIP);
	for (float i = 0.0f; i < 6.28318530375f; i+= 3.14 / 180){
		glVertex3f(sin(i) * m_orbit_distance,
			m_Position.y, 
			cos(i) * m_orbit_distance);
	}
	glEnd();

	glPushMatrix();
	glTranslatef(m_Position.x, m_Position.y, m_Position.z);
	for (size_t i = 0; i < moons.size(); i++){
		moons[i]->renderOrbit();
	}
	glPopMatrix();
}
