#include "Lightning.h"

void Lightning::enableLight()
{
	// Permitir iluminação e activar fonte de luz #n
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat global_ambient[] =  { 0.0f, 0.0f, 0.0f, 1.0f };

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

	GLfloat light_ambient[]  = { 0.2f, 0.2f, 0.2f, 0.2f };
	GLfloat light_diffuse[]  = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.06);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0);

	// Configurar cor da fonte de luz
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
}

void Lightning::applyMaterial()
{
	GLfloat mat_ambient  [] = { 0.05f , 0.05f , 0.05f , 1.0f };
	GLfloat mat_specular [] = { 1.0f , 1.0f , 1.0f , 1.0f };
	GLfloat mat_shininess[] = { 40.0f };
	GLfloat mat_emission [] = { 0.1f , 0.1f , 0.1f , 1.0f };
	GLfloat mat_diffuse  [] = { 1.0f , 1.0f , 1.0f , 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void Lightning::applyLights()
{
	GLfloat light_position[] = { 0.0f, 0.0f, 0.0f , 1.0f };
	// Configurar a posição da fonte de luz
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

