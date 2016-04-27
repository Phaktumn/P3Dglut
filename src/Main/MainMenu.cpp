#include "MainMenu.h"
#include "Space/Planets/SolarSystem.h"
#include "Game.h"
#include "Keyboard/Keyboard.h"

GLuint MainMenu::createMenu;
GLuint MainMenu::PlanetsMenu;
GLuint MainMenu::CameraOptions;
GLuint MainMenu::m_lastPrintIndex = 0;
GLuint MainMenu::m_currPrintIndex = 0;
int MainMenu::menuFlag;

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu(){
}

void MainMenu::start(){
	
	PlanetsMenu = glutCreateMenu(menuPlanets);
	glutAddMenuEntry("Sun",     0);
	glutAddMenuEntry("Mercury", 1);
	glutAddMenuEntry("Venus",   2);
	glutAddMenuEntry("Earth",   3);
	glutAddMenuEntry("Mars",    4);
	glutAddMenuEntry("Jupiter", 5);
	glutAddMenuEntry("Saturn",  6);
	glutAddMenuEntry("Urannus", 7);
	glutAddMenuEntry("Neptune", 8);
	glutAddMenuEntry("Pluto",   9);

	CameraOptions = glutCreateMenu(menuCamera);
	glutAddMenuEntry("Show Settings", 0);
	glutAddMenuEntry("Hide Settings", 1);


	createMenu = glutCreateMenu(menuCallback);
	glutAddSubMenu("Planets", PlanetsMenu);
	glutAddSubMenu("Camera Options", CameraOptions);
	glutAddMenuEntry("Exit", 10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMenuStatusFunc(processStatus);
	glutSetMenu(createMenu);
}

void MainMenu::update()
{
	if(Keyboard::getKeyPressed(KEY_F1)) {
		if(!menuFlag) {
			
		}
	}
}

void MainMenu::menuCallback(int _callBack)
{
	if (Game::solarSystem != nullptr)
	{
		switch (_callBack)
		{
		case 10:
			glutExit();
			break;
		default:
			break;
		}
	}
}

void MainMenu::menuPlanets(int _planetCallBack)
{
	Game::solarSystem->setSelectedObject(_planetCallBack);
}

void MainMenu::menuCamera(int)
{

}

void MainMenu::processStatus(int status, int, int)
{
	if (status == GLUT_MENU_IN_USE) {
		menuFlag = 1;
	}
	else{
		menuFlag = 0;
	}
}
