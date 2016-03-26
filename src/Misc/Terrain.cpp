#include "Terrain.h"
#include "imageloader.h"

Terrain::Terrain(int w2, int h2)
{
	width = w2;
	length = h2;

	heights = new float*[length];
	for (auto i = 0; i < length; i++){
		heights[i] = new float[width];
	}

	normals = new vec::Vector3*[length];
	for (auto i = 0; i < length; i++){
		normals[i] = new vec::Vector3[width];
	}

	computedNormals = false;
}

Terrain* Terrain::loadTerrain(const char* filename, float height) const
{
	auto image = loadBMP(filename);
	auto t = new Terrain(image->width, image->height);
	for (int y = 0; y < image->height; y++)
	{
		for (int x = 0; x < image->width; x++)
		{
			auto color = static_cast<unsigned char>(image->pixels[3 * (y * image->width + x)]);
			auto h = height * ((color / 255.0f) - 0.5f);
			t->setHeight(x, y, h);
		}
	}
	delete image;
	t->computeNormals();
	return t;
}

Terrain::~Terrain()
{
	for (auto i = 0; i < length; i++){
		delete[] heights[i];
	}

	for (auto i = 0; i < length; i++){
		delete[] normals;
	}
}

void Terrain::setHeight(int x, int z, float y)
{
	heights[z][x] = y;
	computedNormals = false;
}

void Terrain::computeNormals()
{
	//TODO ---------------------
}


