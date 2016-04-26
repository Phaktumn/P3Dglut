#pragma once
#include <Misc/RenderText.h>
#include "Camera/Camera.h"


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	static void start();
	static void Update();
	static void Draw();

private:
	static int createMenu;
	static Camera* mainCamera;
	static void menuCallback(int);
};

