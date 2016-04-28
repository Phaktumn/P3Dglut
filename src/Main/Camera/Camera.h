#ifndef CAMERA_H_
#define CAMERA_H_

#pragma once
#include "../../Vars/vec3f.h"
#include "../Player/Player.h"
#include <Main/Globals.h>
#include <Misc/RenderText.h>

class Player;
 
class Camera
{
public:
	//gluLookAt()
	explicit Camera(Player& player);
	explicit Camera(const vec::Vector3& position);
	explicit Camera();
	virtual ~Camera();

	//Sets the player to follow!
	Player* player;

	virtual void Update(float deltaTime);
	virtual void Draw() const;

	vec::Vector3 get_loook_at_vector3() const
	{ return this->m_lookAt; }

	virtual void setLookAt(const vec::Vector3& vec)
	{ this->m_lookAt = vec; }

	vec::Vector3 get_pos_vector3() const
	{ return this->eye; }

	vec::Vector3 get_up_vector3() const
	{ return this->upVec; }

	float get_rotationangle_() const 
	{ return rotationAngle; }


	bool getInfoState() const
	{ return m_showInfo; }
	void setInfoState(const bool state_)
	{
		if (m_showInfo == state_) return;
		m_showInfo = state_;
	}
	void drawInfo() const
	{
		if (m_showInfo) {
			m_infoText->drawText(m_info);
		}
	}

protected:

	RenderText* m_infoText;

	float speed = speed_of_light_MS * Universal_Metric_Scale;

	std::string m_info;
	bool m_showInfo = false;

	vec::Vector3 m_lookAt;
	vec::Vector3 eye;
	vec::Vector3 upVec;

	vec::Vector3 rightVector;
	//vec::Vector3 upVec;
	vec::Vector3 forwardVec;

	vec::Vector3 m_Position;

	//Player angle rotation in Degrees
	float rotationAngle;
};

#endif


