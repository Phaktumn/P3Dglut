#ifndef  LOAD_BMP_H
#define LOAD_BMP_H

#pragma once
#include <Misc/imageloader.h>
#include <Misc/Debug/IO.h>
#include <GL/freeglut.h>

inline GLuint _loadBMP(const std::string& texturePath)
{
	GLuint textureId = 0;
	Image* image = loadBMP(texturePath.c_str());
	IO::printMessage("Image: {"+ texturePath + "} Loaded with Success ");
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
		image->pixels);				//The actual pixel data          
	delete image;					//free memory from image data
	return textureId;				//Returns the id of the texture
}

#endif

