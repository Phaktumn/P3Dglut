#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include <Misc/Lights/Lightning.h>
#include <Misc/Debug/IO.h>
#include "Space/Planets/SolarSystem.h"
#include "Mouse/Mouse.h"
#include "Camera/FPScamera.h"

#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_                  1

Game* Game::instance = nullptr;
RenderText* Game::text;
RenderText* Game::m_text1;
GameTime Game::gameTime = GameTime();
Camera* Game::m_camera;
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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);			   // Black Background (CHANGED)
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
	glutPassiveMotionFunc(Mouse::passiveMouseFunc);

	Lightning::enableLight();		//enables all lights properties positional light
	
	text = new RenderText(vec::Vector3(20, 20, 0), 0.1);
	m_text1 = new RenderText(vec::Vector3(glutGet(GLUT_WINDOW_WIDTH) / 2 - 50,
		glutGet(GLUT_WINDOW_HEIGHT) / 2), 1.0f);
}

void Game::resize(int width, int height)
{
	float ratio;
	if (height == 0) height = 1;
	ratio = 1.0 * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 0.01, 15000);
	glMatrixMode(GL_MODELVIEW);
}

//Use this to add some planets!
void Game::AddItems()
{
	float scale = 1.0f;
	float scaled = 1.0f;
	float planetSizeScale = 4.0f;

	solarSystem = new SolarSystem("Solar System");	 //Create Solar System1
	//Only Sun was Pushed Back to the list
	solarSystem->Load();						     //Load all planets texture

	universe->add_SolarSystem(solarSystem, new vec::Vector3(0, 0, 0));
	//																										Orbit Duration         planet Rotation     eccentricity      Planet Initial			planet scale
	//                                   Solar System                      texture path        Planet Name   in earth days	       in earth days	      Value	      Position(Z = dist sun)     earth equals to 1.0f
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/mercury.bmp", "Mercurio",   88.0f    * scale,	  58.0       * scale,	EC_MERCURY, vec::Vector3(0, 0, 70   + 40 * scaled),	 0.3f * planetSizeScale, 12.0f));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/venus.bmp",   "Venus",      225.0f   * scale,    241.0f     * scale,	EC_VENUS,   vec::Vector3(0, 0, 108  + 40 * scaled),	 0.4f * planetSizeScale, 3.4f));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/earth.bmp"  , "Earth",      365.0f   * scale,	  1.0f       * scale,   EC_EARTH,   vec::Vector3(0, 0, 150  + 40 * scaled),	 1.0f * planetSizeScale, 0.0f));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/mars.bmp",    "Mars",       687.0f   * scale,    1.01f      * scale,	EC_MARS,    vec::Vector3(0, 0, 228  + 40 * scaled),	 0.9f * planetSizeScale, 1.85f));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/jupiter.bmp", "Jupiter",    4332.0f  * scale,    9.8  / 24.0* scale,   EC_JUPITER, vec::Vector3(0, 0, 772  + 40 * scaled),	 11.5 * planetSizeScale, 1.31f));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/saturn.bmp",  "Saturn",     10760.0f * scale,    10.5 / 24.0* scale,   EC_SATURN,  vec::Vector3(0, 0, 1443 + 40 * scaled),	 9.5f * planetSizeScale, 2.49f));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/neptune.bmp", "Neptune",    60200.0f * scale,    16.0 / 24.0* scale,   EC_NEPTUNE, vec::Vector3(0, 0, 4504 + 40 * scaled),	 9.5f * planetSizeScale, 0.77f));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/uranus.bmp",  "Uranus",     30700.0f * scale,    17.0 / 24.0* scale,   EC_URANUS,  vec::Vector3(0, 0, 5871 + 40 * scaled),	 9.5f * planetSizeScale, 1.77f));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/neptune.bmp", "Pluto",	     90600.0f * scale,    0.6f       * scale,	EC_PLUTO,   vec::Vector3(0, 0, 5913 + 40 * scaled),	 9.5f * planetSizeScale, 17.01f));

	universe->add_Comet_to_SolarSystem("Solar System",      new Comet("Textures/Earth.bmp",   "Halley",   vec::Vector3(0, 0, 3200),/* Eccentricity */ 0.967 /* Eccentricity */, 75.3f, 0.0f, 0.4f));

	//Add a moon to selected planet
	solarSystem->findPlanetByName("Earth").addMoon(4.5f, 0.3f);
}

void Game::Update()
{
	gameTime.start(glutGet(GLUT_ELAPSED_TIME) * 0.001);
	if (Keyboard::getKeyPressed(KEY_P))
		state = Exiting;
	switch (state) {
	case Menu: {
		if (Keyboard::getKeyPressed(KEY_S)) {
		    //glutGameModeString(_1366_BY_768);
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				state = InGame;
				//glutDestroyWindow(GLUT_WINDOW0_ID);         //Destroy Window by ID
			    //glutEnterGameMode();						//Enter Full Screen Game Mode
				//glutSetCursor(GLUT_CURSOR_NONE);             //Cursor will be invisible
				//m_camera = new SimpleCamera(vec::Vector3(0, 0, 0), 0.0f);
				m_camera = new FPScamera(vec::Vector3(0, 50, 0));
				universe = new UniverseSimulator();
				AddItems();									 //Get The universe Together
				init();							             //Initialize all glut Properties
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
		m_text1->drawText("Press 'S' to Start");
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
	text->drawText(fps);
#endif
	glutSwapBuffers();	
	gameTime.end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}

