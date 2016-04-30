#include "MiniMap.h"
#include <Main/Game.h>

MiniMap::MiniMap(short int Width, short int height)
	: miniMaptexture(0)
{
	m_cameraPosition = Vector3::zero();
	m_Width = Width;
	m_height = height;
	m_Camerargb = Vector3(1, 0, 0);
}

MiniMap::~MiniMap()
{
}

void MiniMap::load()
{
	miniMaptexture = _loadBMP("Textures/miniMapSkin.bmp");
}

void MiniMap::update()
{
	auto activeCamera = Game::cameraIndex;
	switch (activeCamera)
	{
	case 0:
		// ReSharper disable once CppMsExtAddressOfClassRValue
		m_cameraPosition = convertFromPointToMiniMapPoint(Game::m_camera->get_pos_vector3());
		break;
	case 1:
		// ReSharper disable once CppMsExtAddressOfClassRValue
		m_cameraPosition = convertFromPointToMiniMapPoint(Game::orbitCamera->get_pos_vector3());
		break;
	default:
		break;
	}
	m_sunPos     = convertFromPointToMiniMapPoint(Game::solarSystem->getPlanetPostion(0));
	m_earthPos   = convertFromPointToMiniMapPoint(Game::solarSystem->getPlanetPostion(4));
	m_jupiterPos = convertFromPointToMiniMapPoint(Game::solarSystem->getPlanetPostion(5));
	m_plutoPos   = convertFromPointToMiniMapPoint(Game::solarSystem->getPlanetPostion(10));
}

void MiniMap::draw()
{
	glMatrixMode(GL_PROJECTION);
	{
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		{
			glPushMatrix();
			glLoadIdentity();

			glCullFace(GL_CCW);
			glFrontFace(GL_FRONT);

			glDisable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_TEXTURE);

			glPushMatrix();
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, miniMaptexture);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glBegin(GL_QUADS);
				glTexCoord3f(0, 0, 0);
				glVertex3f(0, 0, 0);
				glTexCoord3f(0,-1, 0);
				glVertex3f(0, m_height, 0);
				glTexCoord3f(1, -1, 0);
				glVertex3f(m_Width, m_height, 0);
				glTexCoord3f(1, 0, 0);
				glVertex3f(m_Width, 0, 0);
				glEnd();
				glDisable(GL_TEXTURE_2D);
			}
			glPopMatrix();

			//Draw Planets
			glPushMatrix();
			{
				drawQuad(m_sunPos, Vector3(0.7f, 0.3f, 0.1f), 2.0f);
				drawQuad(m_earthPos, Vector3(0.05f, 0.4f, 0.8f), 0.7f);
				drawQuad(m_jupiterPos, Vector3(0.4f, 0.25f, 0.15f), 1.3f);
				drawQuad(m_plutoPos, Vector3(0.9f, 0.7f, 0.9f), 0.7f);
			}
			glPopMatrix();

			glPushMatrix();
			{
				drawQuad(m_cameraPosition, m_Camerargb, 1.5f);
			}
			glPopMatrix();

			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_TEXTURE);

			glPopMatrix();
			glMatrixMode(GL_PROJECTION);
		}
	}
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

vec::Vector3& MiniMap::convertFromPointToMiniMapPoint(const Vector3& _vec) const
{
	// 0   ->  256
	// pos ->  x
	Vector3 aux = Vector3::zero();
	aux.x = _vec.x / m_Width;
	aux.z = _vec.z / m_height;
	float aux_X = (m_Width  / 2) + (_vec.x * 0.015f);
	float aux_Y = (m_height / 2) + (_vec.z * 0.015f);
	aux.x = aux_X;
	aux.z = aux_Y;
	return aux;
}

void MiniMap::drawQuad(vec::Vector3& pos, const vec::Vector3& color, const float scale) const
{
	glColor4f(color.x, color.y, color.z, 1.0f);
	glBegin(GL_QUADS);
	_Vertex3(Vector3(pos.x - scale, pos.z - scale, 0.1f));
	_Vertex3(Vector3(pos.x - scale, pos.z + scale, 0.1f));
	_Vertex3(Vector3(pos.x + scale, pos.z + scale, 0.1f));
	_Vertex3(Vector3(pos.x + scale, pos.z - scale, 0.1f));
	glEnd();
}
