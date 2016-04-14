#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include "Planets/SolarSystem.h"
#include <Misc/Lights/Lightning.h>
#include <Misc/Debug/IO.h>

#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_                  1

Game* Game::instance = nullptr;
RenderText* Game::text = new RenderText();
RenderText* Game::m_text1 = new RenderText();
GameTime Game::gameTime = GameTime();
StaticCamera* Game::m_camera;
SolarSystem* Game::solarSystem;
SolarSystem* Game::solarSystem_1;
Game::GameState Game::state = Menu;
UniverseSimulator* Game::universe;

GLuint GLUT_WINDOW0_ID = 0;
GLuint GLUT_WINDOW1_ID = 0;

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	std::cout << "Game Initialized\n";
}

Game::~Game()
{
	delete universe;
	delete text;
	delete m_text1;
	std::cout << "\nClosed";
}

int Game::start(int windowHeigth, int windowWidth, std::string windowTitle)
{
	glutInitWindowSize(windowWidth, windowHeigth);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	GLUT_WINDOW0_ID = glutCreateWindow(windowTitle.c_str());

	//Initialize variables
	init();

	glutMainLoop();

	return 0;
}

void Game::init()
{
	glShadeModel(GL_SMOOTH);						   // Enable Smooth Shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDepthFunc(GL_LEQUAL);							   // The Type Of Depth Testing To Do
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);             // Pixel Storage Mode To Byte Alignment
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			   // Black Background (CHANGED)
	glClearDepth(1.0f);								   // Depth Buffer Setup					
	glEnable(GL_DEPTH_TEST);						   // Enables Depth Testing						  
	glEnable(GL_COLOR_MATERIAL);					   // Enable Material Coloring
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutReshapeFunc(resize);

	glutKeyboardFunc(Keyboard::keydoardCallback);
	glutKeyboardUpFunc(Keyboard::keyboardUpCallback);

	Lightning::enableLight();		//enables all lights properties positional light
}

void Game::resize(int width, int height)
{
	float ratio;
	if (height == 0) height = 1;
	ratio = 1.0 * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, ratio, 0.01, 15000);
	glMatrixMode(GL_MODELVIEW);
}

//Use this to add some planets!
void Game::AddItems()
{
	universe->add_SolarSystem(solarSystem, new vec::Vector3(1,15,1));
	universe->addPlanet_to_SolarSystem("Jorge 01", new Planet("Textures/mercury.bmp", "Mercurio", 88.0f, 58.0f,EC_MERCURY, vec::Vector3(0, 0, 70), 0.3f));

	universe->add_SolarSystem(solarSystem_1, new vec::Vector3(500, 20, 500));
	//                                   Solar System                  texture path       Planet Name
	universe->addPlanet_to_SolarSystem("Jorge 02",		new Planet("Textures/mercury.bmp", "Mercurio", 88.0f , 58.0f, EC_MERCURY, vec::Vector3(0, 0, 70), 0.3f ));
	universe->addPlanet_to_SolarSystem("Jorge 02",		new Planet("Textures/earth.bmp"  , "Earth",    365.0f, 1.0f,  EC_EARTH,   vec::Vector3(0, 0, 150), 1.0f));
}

void Game::Update()
{
	gameTime.start(glutGet(GLUT_ELAPSED_TIME) * 0.001);
	if (Keyboard::getKeyPressed(KEY_P))
		state = Exiting;
	switch (state) {
	case Menu: {
		if (Keyboard::getKeyPressed(KEY_S)) {
		    glutGameModeString(_1366_BY_768);
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				state = InGame;
				// Creates a new Camera for InGame Scene
				glutDestroyWindow(GLUT_WINDOW0_ID);         //Destroy Window by ID
				glutEnterGameMode();  //Enter Full Screen Game Mode
				m_camera = new StaticCamera(vec::Vector3(0, 0, 0), 0.0f);
				universe = new UniverseSimulator();
				solarSystem = new SolarSystem("Jorge 01"); //Create Solar System1
				solarSystem->Load();    //Load all planets textures
				solarSystem_1 = new SolarSystem("Jorge 02"); //Create Solar System2
				solarSystem_1->Load();  //Load System Planets Textures
				glutSetCursor(GLUT_CURSOR_NONE); //Cursor will be invisible
				AddItems(); //Get The universe Together
				init();     //Initialize all glut Properties
			}
			else {
				IO::printError("The selected Mode is not Available\n");
			}
		}
	} break;
	case InGame: {	
		m_camera->Update(gameTime.getDeltaTime());
		universe->simulate(gameTime.getDeltaTime());
	}break;
	default: break;
	case Exiting: {
		glutExit();
	}break;
	}
	glutPostRedisplay();
}

GLvoid Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	switch (state) {
	case Menu: {
		//Draw a Simple text just to help player on how to start the Game
		m_text1->drawText("Press 'S' to Start",
			vec::Vector3(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50, glutGet(GLUT_WINDOW_HEIGHT) / 2), 1.0f);
	}break;
	case InGame: {	
			m_camera->Draw();
			Lightning::applyLights();
			universe->draw();
	}break;
	default: break;
	}
#if _DEBUG_ 1
	auto fps = "FPS: " + std::to_string(gameTime.getFps());
	// ReSharper disable once CppMsExtBindingRValueToLvalueReference
	text->drawText(fps, vec::Vector3(20, 20, 0), 0.1);
#endif
	glutSwapBuffers();	
	gameTime.end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}

