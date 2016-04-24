#ifndef MOUSE_H_
#define MOUSE_H_

#pragma once
#include <Vars/vec3f.h>

class Mouse
{
public:
	static Vector3& getMousePos(){
		return *mousePos;
	}

	static void mouseFunc(int, int, int, int);
	static void passiveMouseFunc(int, int);
private:
	//static bool justWarped;
	static Vector3* mousePos;
};

Vector3* Mouse::mousePos = new Vector3(300, 400, 0);
//bool Mouse::justWarped = false;

inline void Mouse::mouseFunc(int x, int y, int w, int r)
{
}

inline void Mouse::passiveMouseFunc(int x, int y)
{
	static bool justWarped = false;

	if (justWarped){
		justWarped = false;
		return;
	}

	mousePos->x = x;
	mousePos->y = y;
	//Ignore Mouse pos.z
	mousePos->z = 0;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2,
		glutGet(GLUT_WINDOW_HEIGHT) / 2);
	justWarped = true;
}

#endif

