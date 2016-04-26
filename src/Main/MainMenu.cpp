#include "MainMenu.h"
#include "Space/Planets/SolarSystem.h"
#include "Game.h"

int MainMenu::createMenu;
Camera* MainMenu::mainCamera;

MainMenu::MainMenu()
{
	mainCamera = Game::m_camera;
}


MainMenu::~MainMenu(){
	delete mainCamera;
}

void MainMenu::start(){

	createMenu = glutCreateMenu(menuCallback);

	glutAddMenuEntry("Mercury", 0);
	glutAddMenuEntry("Venus",   1);
	glutAddMenuEntry("Earth",   2);
	glutAddMenuEntry("Mars",    3);
	glutAddMenuEntry("Jupiter", 4);
	glutAddMenuEntry("Saturn",  5);
	glutAddMenuEntry("Urannus", 6);
	glutAddMenuEntry("Neptune", 7);
	glutAddMenuEntry("Pluto",   8);

	glutAddMenuEntry("Exit",    9);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MainMenu::Update()
{

}

void MainMenu::Draw()
{

}

void MainMenu::menuCallback(int _callBack)
{
	Vector3 auxPos;
	if (Game::solarSystem != nullptr)
	{
		switch (_callBack)
		{
		case 1:
			auxPos = Game::solarSystem->getPlanetPostion(_callBack);
			Game::solarSystem->setPrintIndex(_callBack);
			mainCamera->setLookAt(Vector3::Normalize(mainCamera->get_pos_vector3() - auxPos));
			break;
		case 2:
			auxPos = Game::solarSystem->getPlanetPostion(_callBack);
			Game::solarSystem->setPrintIndex(_callBack);
			mainCamera->setLookAt(Vector3::Normalize(mainCamera->get_pos_vector3() - auxPos));
			break;
		case 3:
			auxPos = Game::solarSystem->getPlanetPostion(_callBack);
			Game::solarSystem->setPrintIndex(_callBack);
			mainCamera->setLookAt(Vector3::Normalize(mainCamera->get_pos_vector3()- auxPos));
			break;
		default:
			break;
		}
	}
}
