#pragma once
#include "../Vars/vec3f.h"

class Terrain
{
public:
	Terrain(int w2, int h2);
	Terrain* loadTerrain(const char* filename, float height);
	~Terrain();

	int getWidth() const
	{ return width; }
	int getLength() const
	{ return length; }

	float getHeight(int x, int z) const
	{ return heights[z][x]; }

	void setHeight(int x, int z, float y);
	void computeNormals();

	vec::Vector3 getNormal(int x, int z) 
	{ if (!computedNormals)computeNormals(); return normals[z][x]; }

private:
	int width;
	int length;
	float** heights;
	vec::Vector3** normals;
	bool computedNormals;
};

