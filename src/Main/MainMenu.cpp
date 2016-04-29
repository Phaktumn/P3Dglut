#include "MainMenu.h"
#include "Space/Planets/SolarSystem.h"
#include "Game.h"

GLuint MainMenu::createMenu;
GLuint MainMenu::PlanetsMenu;
GLuint MainMenu::CameraOptions;
GLuint MainMenu::m_lastPrintIndex = 0;
GLuint MainMenu::m_currPrintIndex = 0;
int MainMenu::menuFlag;

//************************************
// Method:    MainMenu
// FullName:  MainMenu::MainMenu
// Access:    public 
// Returns:   
// Qualifier:
//************************************
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
	glutAddMenuEntry("Uranus", 7);
	glutAddMenuEntry("Neptune", 8);
	glutAddMenuEntry("Pluto",   9);

	CameraOptions = glutCreateMenu(menuCamera);
	glutAddMenuEntry("Show Settings",  0);
	glutAddMenuEntry("Hide Settings",  1);
	glutAddMenuEntry("FPScamera",      2);
	glutAddMenuEntry("Orbital Camera", 3);


	createMenu = glutCreateMenu(menuCallback);
	glutAddSubMenu("Planets", PlanetsMenu);
	glutAddSubMenu("Camera Options", CameraOptions);
	glutAddMenuEntry("Show Orbits", 0);
	glutAddMenuEntry("Hide Orbits", 1);
	glutAddMenuEntry("Exit", 10);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutSetMenu(createMenu);
}

void MainMenu::update()
{
	//Nothing Here
}

void MainMenu::draw()
{
	//Obriga o Menu Desenhar as informaçoes da camara
	Game::m_camera->drawInfo();
}

void MainMenu::menuCallback(int _callBack)
{
	//Call back do menu principal!
	if (Game::solarSystem != nullptr)
	{
		switch (_callBack)
		{
		case 0:
			Game::solarSystem->setOrbitRenderState(1);
			break;
		case 1:
			Game::solarSystem->setOrbitRenderState(0);
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
	static_cast<SimpleCamera*>(Game::orbitCamera)->setFocus(Game::solarSystem->getPlanet(_planetCallBack));
}

void MainMenu::menuCamera(int _cameraCall)
{
	//Codigo para escrever cenas da camara no ecran
	//Por na camara metodo para desenhar
	switch (_cameraCall)
	{
	case 0: Game::m_camera->setInfoState(true);
		break;
	case 1: Game::m_camera->setInfoState(false);
		break;
	case 2: Game::setActiveCamera(0);
		break;
	case 3: Game::setActiveCamera(1);
		break;
	default:
		break;
	}
}
