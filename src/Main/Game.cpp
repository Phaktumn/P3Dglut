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
Game::GameState Game::state = Menu;

GLuint GLUT_WINDOW0_ID = 0;
GLuint GLUT_WINDOW1_ID = 0;

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	std::cout << "Game Initialized\n";
}

Game::~Game()
{
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

void Game::Update()
{
	gameTime.start(glutGet(GLUT_ELAPSED_TIME) * 0.001);
	if (Keyboard::getKeyPressed(KEY_P))
		state = Exiting;
	switch (state) {
	case Menu: {
		if (Keyboard::getKeyPressed(KEY_S)) {
		    glutGameModeString(_1920_BY_1080_RR_60);
			if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				state = InGame;
				// Creates a new Camera for InGame Scene
				glutDestroyWindow(GLUT_WINDOW0_ID);         //Destroy Window by ID
				glutEnterGameMode();  //Enter Full Screen Game Mode
				// ReSharper disable once CppNonReclaimedResourceAcquisition
				m_camera = new StaticCamera(vec::Vector3(0, 0, 0), 0.0f);
				// ReSharper disable once CppNonReclaimedResourceAcquisition
				solarSystem = new SolarSystem();
				solarSystem->Load();  //Load all planets textures
				glutSetCursor(GLUT_CURSOR_NONE);
				init();
			}
			else {
				IO::printError("The selected Mode is not Available\n");
				glutFullScreen();
			}
		}
	} break;
	case InGame: {	
		m_camera->Update(gameTime.getDeltaTime());
		solarSystem->Simulate(gameTime.getDeltaTime());
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
			solarSystem->Draw();
			solarSystem->renderOrbits();
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


