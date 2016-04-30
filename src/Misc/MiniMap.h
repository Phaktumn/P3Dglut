#pragma once
#include <Vars/vec3f.h>

class MiniMap
{
public:
	MiniMap(short int Width, short int height);
	~MiniMap();

	void load();
	void update();
	void draw();

private:
	vec::Vector3& convertFromPointToMiniMapPoint(const vec::Vector3& _vec) const;
	void drawQuad(vec::Vector3& pos, const vec::Vector3& color, const float scle) const;
	vec::Vector3 m_cameraPosition;

	short int m_Width;
	short int m_height;

	vec::Vector3 m_Camerargb;
	vec::Vector3 m_sunPos;
	vec::Vector3 m_earthPos;
	vec::Vector3 m_plutoPos;
	vec::Vector3 m_jupiterPos;

	int miniMaptexture;
};