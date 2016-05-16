#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"
#include "Keyboard/Keyboard.h"
#include <Misc/Lights/Lightning.h>
#include "Space/Planets/SolarSystem.h"
#include "Mouse/Mouse.h"
#include "Camera/FPScamera.h"

#define _CRT_SECURE_NO_WARNINGS
#define _DEBUG_                  1

Game* Game::instance = nullptr;
RenderText* Game::text;
GameTime* Game::gameTime = new GameTime();
Camera* Game::m_camera;
Camera* Game::orbitCamera;
int Game::cameraIndex = 0;
SolarSystem* Game::solarSystem;
Game::GameState Game::state = Menu;
UniverseSimulator* Game::universe;
GLuint Game::EvenFlag = 0;
GLUquadric* Game::m_Object = gluNewQuadric();
MainMenu* Game::menu = new MainMenu();
MiniMap* Game::m_miniMap = new MiniMap(short int(256), short int(256));
GLuint Game::entryMenuTexture = 0;

GLuint GLUT_WINDOW0_ID = 0;
GLuint GLUT_WINDOW1_ID = 0;

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	cout << "Game Initialized\n";
}

Game::~Game()
{
	delete universe;
	delete text;
	delete gameTime;
	cout << "\nClosed";
}

int Game::start(int windowHeigth, int windowWidth, string windowTitle)
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
	
	text = new RenderText(Vector3(20.0f, 20.0f, 0.0f), 0.1);

	entryMenuTexture = _loadBMP("Textures/entryMenuTexture.bmp");
}

void Game::resize(int width, int height)
{
	float ratio;
	if (height == 0) height = 1;
	ratio = 1.0 * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, ratio, 0.01, INFINITE);
	glClearDepth(1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthRange(0.0, 0.5);
	glDepthFunc(GL_LESS);
	EvenFlag = 1;
	glMatrixMode(GL_MODELVIEW);
}

//Use this to add some planets!
void Game::AddItems()
{
	float Time_scale = 1.0f;

	solarSystem = new SolarSystem("Solar System");	 //Create Solar System1
	//Only Sun was Pushed Back to the list
	solarSystem->Load();						     //Load all planets texture

	universe->add_SolarSystem(solarSystem, new Vector3(0, 0, 0));
	//																										Orbit Duration         planet Rotation     eccentricity      Planet Initial			            planet scale        orbit    planet
	//                                   Solar System                      texture path        Planet Name   in earth days	       in earth days       Value	      Position(Z = dist sun)            earth equals to 1.0f     inc     tilt
	//Add Only a sun to each System created
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/sun.bmp",     "Sun",        NULL,                     NULL,                        NULL,       Vector3(0, 0, 0),                                  150000.0f * Universal_Size_Scale, 0.0f,   0.0f    ));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/mercury.bmp", "Mercury",    88.0f    * Time_scale,	   58.0        * Time_scale,	EC_MERCURY, Vector3(0, 0, 57910000   * Universal_Metric_Scale),  4878.0f * Universal_Size_Scale, 12.0f,  0.0f	 ));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/venus.bmp",   "Venus",      225.0f   * Time_scale,    241.0f      * Time_scale,	EC_VENUS,   Vector3(0, 0, 108200000  * Universal_Metric_Scale), 12104.0f * Universal_Size_Scale, 3.4f ,  177.36f ));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/earth.bmp"  , "Earth",      365.0f   * Time_scale,	   1.0f        * Time_scale,    EC_EARTH,   Vector3(0, 0, 149600000  * Universal_Metric_Scale), 12756.0f * Universal_Size_Scale, 0.0f ,  23.45f  ));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/mars.bmp",    "Mars",       687.0f   * Time_scale,    1.01f       * Time_scale,	EC_MARS,    Vector3(0, 0, 227940000  * Universal_Metric_Scale),  6787.9f * Universal_Size_Scale, 1.85f,  25.19f  ));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/jupiter.bmp", "Jupiter",    4332.0f  * Time_scale,    9.8  / 24.0 * Time_scale,	EC_JUPITER, Vector3(0, 0, 778330000  * Universal_Metric_Scale),147796.5f * Universal_Size_Scale, 1.31f,  3.13f   ));
	universe->addPlanet_to_SolarSystem("Solar System",      new Planet("Textures/saturn.bmp",  "Saturn",     10760.0f * Time_scale,    10.5 / 24.0 * Time_scale,    EC_SATURN,  Vector3(0, 0, 1424600000 * Universal_Metric_Scale),120660.5f * Universal_Size_Scale, 2.49f,  26.73f  ));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/neptune.bmp", "Neptune",    60200.0f * Time_scale,    16.0 / 24.0 * Time_scale,    EC_NEPTUNE, Vector3(0, 0, 2873550000 * Universal_Metric_Scale), 51118.5f * Universal_Size_Scale, 0.77f,  97.77f  ));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/uranus.bmp",  "Uranus",     30700.0f * Time_scale,    17.0 / 24.0 * Time_scale,    EC_URANUS,  Vector3(0, 0, 4501000000 * Universal_Metric_Scale), 48600.5f * Universal_Size_Scale, 1.77f,  28.32f  ));
	universe->addPlanet_to_SolarSystem("Solar System",		new Planet("Textures/neptune.bmp", "Pluto",	     90600.0f * Time_scale,    0.6f        * Time_scale,	EC_PLUTO,   Vector3(0, 0, 5945900000 * Universal_Metric_Scale),  2274.5f * Universal_Size_Scale, 17.01f, 122.53f ));

	universe->add_Comet_to_SolarSystem("Solar System",      new Comet("Textures/Earth.bmp",   "Halley", 75.3f, 0.0f, /* Eccentricity */ 0.967 /* Eccentricity */,  Vector3(0, 0, 3200), 1000.0f * Universal_Size_Scale, 0.0f, 12.0f));

	//Add a moon to selected planet
	solarSystem->findPlanetByName("Earth").addMoon(370300.0f * Universal_Metric_Scale, 1737.0f * Universal_Size_Scale);

	//Add ring to selected planet
	solarSystem->findPlanetByName("Saturn").addRings(15000.0f * Universal_Metric_Scale,  19000.0f * Universal_Metric_Scale);
	solarSystem->findPlanetByName("Neptune").addRings(13000.0f * Universal_Metric_Scale,  14500.0f * Universal_Metric_Scale);
}

void Game::Update()
{
	gameTime->start(glutGet(GLUT_ELAPSED_TIME) * 0.001);
	if (Keyboard::getKeyPressed(KEY_P))
		state = Exiting;
	switch (state) 
	{
	case Menu: {
		if (Keyboard::getKeyPressed(NUM_1)) 
		{
			state = InGame;
			glutFullScreen();
			//glutFullScreenToggle();
			orbitCamera = new SimpleCamera(Vector3(100, 0, 100), 0.0f, true);
			orbitCamera->setLookAt(Vector3(0, 0, 0));
			m_camera = new FPScamera(Vector3(0, 50, 0), false);
			universe = new UniverseSimulator();
			AddItems();									 //Get The universe Together
			init();							             //Initialize all glut Properties
			//Load Menus and minimaps
			//so they are able to use Planets Informations
			m_miniMap->load();
			menu->start();
		}
	} break;
		//Update everything that is included after the user started simulation
		//In game is called when simulation is started
	case InGame: 
	{	
		menu->update();
		if(cameraIndex == 0) m_camera->Update(gameTime->getDeltaTime());
		if(cameraIndex == 1) orbitCamera->Update(gameTime->getDeltaTime());
		universe->simulate(gameTime->getDeltaTime());
		m_miniMap->update();
	}
	break;
	default: break;
	case Exiting: 
	{
		glutExit();
	}break;
	}
	glutPostRedisplay();
}

GLvoid Game::render()
{
	if(EvenFlag) {
		glDepthFunc(GL_LESS);
		glDepthRange(0.0, 0.5);
	}
	else{
		glDepthFunc(GL_GREATER);
		glDepthRange(1.0, 0.5);
	}
	EvenFlag = !EvenFlag;

	/* Then Draw Scene */
	switch (state) {
	case Menu: {
		glMatrixMode(GL_PROJECTION);
		{
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0, -1, 1);
			glMatrixMode(GL_MODELVIEW);
			{
				glPushMatrix();
				glLoadIdentity();
				{
					glCullFace(GL_CCW);
					glFrontFace(GL_FRONT);
					glDisable(GL_LIGHTING);
					glBindTexture(GL_TEXTURE_2D, entryMenuTexture);
					glBegin(GL_QUADS);
					glTexCoord3f(0, 0, 0);  glVertex3f(0, 0, 0.1f);
					glTexCoord3f(0, 1, 0);  glVertex3f(0, glutGet(GLUT_WINDOW_HEIGHT), 0.1f);
					glTexCoord3f(-1, 1, 0); glVertex3f(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.1f);
					glTexCoord3f(-1, 0, 0); glVertex3f(glutGet(GLUT_WINDOW_WIDTH), 0, 0.1f);
					glEnd();
					glEnable(GL_LIGHTING);
				}
				glPopMatrix();
				glMatrixMode(GL_PROJECTION);
			}
		}
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}break;
		//All rendering and postUpdate stuff
		//included in In game
		//In game is called when simulation is started
	case InGame: 
	{
		glLoadIdentity();
		if(cameraIndex == 0) m_camera->Draw();
		if(cameraIndex == 1) orbitCamera->Draw();
		Lightning::applyLights();
		universe->draw();
		if(cameraIndex == 0) m_camera->drawInfo();
		if(cameraIndex == 1) orbitCamera->drawInfo();
		m_miniMap->draw();
	}break;
	default: break;
	}
#if _DEBUG_ 1
	auto fps = "FPS: " + to_string(gameTime->getFps());
	text->drawText(fps);
#endif
	glutSwapBuffers();	
	gameTime->end(glutGet(GLUT_ELAPSED_TIME) * 0.001);
}

