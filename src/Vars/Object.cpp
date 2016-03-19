#include "Object.h" 
#include <stdlib.h>
#include <iostream>

Object::Object(char path[]): model(nullptr)
{
	this->path = (char *) malloc(strlen(path) + 1);
	strcpy(this->path, path);
}


Object::~Object()
{
}

GLvoid Object::loadModel()
{
	if(model == NULL)
	{
		model = glmReadOBJ(path);
		if (model == nullptr){
			std::cout << "Error Loading Model!"; 
			exit(0);
		}
		
		glmUnitize(model);
		glmLinearTexture(model);
		glmScale(model, 1.0);
		glmFacetNormals(model);
		glmVertexNormals(model, 90.0f);
	}
}

GLvoid Object::renderModel() const
{
	glmDraw(model, GLM_SMOOTH | GLM_MATERIAL);
}

GLuint Object::getObjecTriangleCount() const
{
	return model->numtriangles;
}

std::string Object::debug() const
{
TODO:
	std::string debug;
	debug = "{ Object: " + std::string(model->groups->name) + " Triangles: " + std::to_string(getObjecTriangleCount()) + " }";
	return debug;
}
