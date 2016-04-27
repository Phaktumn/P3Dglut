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
	glutAddMenuEntry("Show Orbits", 0);
	glutAddMenuEntry("Hide Orbits", 1);
	glutAddMenuEntry("Exit", 10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMenuStatusFunc(processStatus);
	glutSetMenu(createMenu);
}

void MainMenu::update()
{
	//Nothing Here
}

void MainMenu::menuCallback(int _callBack)
{
	//Call back do menu principal!
	if (Game::solarSystem != nullptr)
	{
		switch (_callBack)
		{
		case 0:
			//Ligar orbitas
			break;
		case 1:
			//Desligar Orbitas
			break;
		case 10:
			glutExit();
			break;
		default:
			break;
		}
	}
}

//Call back do menu dos planets
void MainMenu::menuPlanets(int _planetCallBack)
{
	//Diz para apresentar no ecran as informaçoes do planeta
	Game::solarSystem->setSelectedObject(_planetCallBack);
}

void MainMenu::menuCamera(int)
{
	//Codigo para escrever cenas da camara no ecran
	//Por na camara metodo para desenhar
}

//Acrescentar menu para ligar e desligar as orbitas!!!

void MainMenu::processStatus(int status, int, int)
{
	if (status == GLUT_MENU_IN_USE) {
		menuFlag = 1;
	}
	else{
		menuFlag = 0;
	}
}
