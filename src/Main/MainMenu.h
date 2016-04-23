#pragma once
#include <Misc/RenderText.h>


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void start();
	void Update() const;
	void Draw() const;

private:
	RenderText* text;
};

