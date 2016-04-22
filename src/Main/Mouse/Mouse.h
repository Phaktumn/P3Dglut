#pragma once
#include <Vars/vec3f.h>

class Mouse
{
public:
	static vec::Vector3& getMousePostion()
	{
		return mousePos;
	}

	static void mouseFunc();

private:
	static vec::Vector3 mousePos;
};

inline void Mouse::mouseFunc()
{
	//Do stuff 
	//Update mousePos
}
