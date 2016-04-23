#include <string>
#include "../Misc/GLM/glm.h"

#pragma once
class Object
{
public:
	explicit Object(char path[]);
	~Object();

	GLvoid loadModel();
	GLvoid renderModel() const;

	GLMmaterial* getMaterial() const
	{ return model->materials; }

	GLuint getObjecTriangleCount() const;

	std::string debug() const;

private:
	GLMmodel* model;
	char *path;
};

