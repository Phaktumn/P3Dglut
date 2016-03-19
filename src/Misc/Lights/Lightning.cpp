#include "Lightning.h"
#include "../../Vars/vec3f.h"

Lightning::Lightning(int enable)
{
	if (enable > 1) enable == 1;
	if (enable < 0) enable == 0;
	this->enable = enable;
	for (size_t i = 0; i < array_size; i++)
	{
		if (i == 0){
			light_position[i] = 1;
			mat_ambient_and_diffuse[i] = 1.0;
			mat_specular[i] = 1;
		}
		if (i == 1){
			light_position[i] = 1;
			mat_ambient_and_diffuse[i] = 1.0;
			mat_specular[i] = 1;
		}
		if (i == 2){
			light_position[i] = 1;
			mat_ambient_and_diffuse[i] = 1.0;
			mat_specular[i] = 1;
		}
		if (i == 3) { 
			light_position[i] = 0;
			mat_ambient_and_diffuse[i] = 1.0;
			mat_specular[i] = 1;
		}
		light_ambient[i] = 0;
		light_diffuse[i] = 0; 
		light_specular[i] = 0;
	}
	mat_shininess[0] = 30.0;
}

Lightning::~Lightning()
{
}

void Lightning::setAmbientColor(vec::Vector3 ambient_rgb, GLfloat alpha)
{
	if (isEnabled() == 1)
	{
		light_ambient[0] = ambient_rgb.x;
		light_ambient[1] = ambient_rgb.y;
		light_ambient[2] = ambient_rgb.z;
		light_ambient[3] = alpha;
	}
}

void Lightning::setDiffuse(vec::Vector3 diffuse_rgb, GLfloat alpha)
{
	if (isEnabled() == 1)
	{
		light_diffuse[0] = diffuse_rgb.x;
		light_diffuse[1] = diffuse_rgb.y;
		light_diffuse[2] = diffuse_rgb.z;
		light_diffuse[3] = alpha;
	}
}

void Lightning::setSpecular(vec::Vector3 specular_rgb, GLfloat alpha)
{
	if (isEnabled() == 1)
	{
		light_specular[0] = specular_rgb.x;
		light_specular[1] = specular_rgb.y;
		light_specular[2] = specular_rgb.z;
		light_specular[3] = alpha;
	}
}

void Lightning::setLightPosition(vec::Vector3 position)
{
	if (isEnabled() == 1)
	{
		light_position[0] = position.x;
		light_position[1] = position.y;
		light_position[2] = position.z;
		light_position[3] = 1.0f;
	}
}

void Lightning::enableLight() const
{
	// Permitir iluminação e activar fonte de luz #n
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Configurar cor da fonte de luz
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	// Configurar a posição da fonte de luz
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	// Configurar material
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

int Lightning::isEnabled() const
{ return enable; }
