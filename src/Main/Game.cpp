#include "Game.h"
#include <iostream>
#include "../Misc/RenderText.h"

#define _CRT_SECURE_NO_WARNINGS
#define _RENDER_LANDSCAPE        1
#define _RENDER_PLANE            1
#define _DEBUG_                  1

Game* Game::instance = nullptr;
int Game::font = reinterpret_cast<int>(GLUT_BITMAP_8_BY_13);
bool Game::KEYS[];
float Game::deltaTime;
int Game::startTime;
int Game::frames = 0;
int Game::framesPS = 0;
float Game::time = 0;
float Game::speed;
float Game::posX = 0;
float Game::posY = 0.5;
float Game::posZ = 0;
GLfloat Game::lx = 0;
GLfloat Game::lz = 0;
float Game::x;
float Game::y;
float Game::z;
float Game::rotateX = 0;
float Game::rotateY = 1;
float Game::rotateZ = 0;
float Game::rotationAngle = 0;
float Game::windowHeigth = 0;
float Game::windowWidth = 0;
int Game::_INDEX = 0;
float Game::blue[] = { .0, .0, 1 };
float Game::red[] = { 1, .0, .0 };
float Game::green[] = { .0, 1, .0 };
float Game::violet[] = { 0.5, 0.1, 0.5 };
float Game::Colors[][3] = { {blue[0], blue[1] ,blue[2]},
	{red[0],red[1],red[2]},
	{green[0], green[1],green[2]},
	{violet[0],violet[1],violet[2]},
	{blue[0], blue[1] ,blue[2]},
	{red[0],red[1],red[2]},
	{green[0], green[1],green[2]},
	{violet[0],violet[1],violet[2]},
	{green[0], green[1],green[2]},
	{violet[0],violet[1],violet[2]} };
GLfloat Game::lModel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
RenderText* Game::text = new RenderText();
RenderText* Game::WTF = new RenderText();
Object * Game::Tree;
DisplayList * Game::list1 = new DisplayList(3);
Lightning * Game::lights = new Lightning(1);
BoxCollider * Game::colliderBox = new BoxCollider(
	vec::Vector3(10, 10, 10), vec::Vector3(12, 12, 12));
Player * Game::Gamer;

Game::Game(int argc, char** argv)
{
	glutInit(&argc, argv);
	deltaTime = 0;
	speed = 100;
	std::cout << "Game Initialized";
}

Game::~Game()
{
	std::cout << "Closed";
}

int Game::start(int windowHeigth, int windowWidth, std::string windowTitle) const
{
	this->windowHeigth = windowHeigth;
	this->windowWidth = windowWidth;
	glutInitWindowSize(windowWidth, windowHeigth);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow(windowTitle.c_str());

	glutDisplayFunc(render);
	glutIdleFunc(Update);
	glutReshapeFunc(resize);

	glutKeyboardFunc(keyboardCallback);
	glutKeyboardUpFunc(upCallback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Gamer = new Player();

	Tree = new Object("C:/Users/Jorge-Programar/OneDrive/P3D-master/Modelos3D/rose+vase.obj");
	Tree->loadModel();

	text->setWindowHeight(windowHeigth);
	text->setWindowWidth(windowWidth);

	WTF->setWindowHeight(windowHeigth);
	WTF->setWindowWidth(windowWidth);

	//224,255,255
	lights->setAmbientColor(vec::Vector3(MathHelper::normalizef(255, 255), 1, 1), 1);
	lights->setDiffuse(vec::Vector3(MathHelper::normalizef(255, 255)), 1);
	lights->setSpecular(vec::Vector3(255), 1);
	lights->enableLight();

	list1->GenLandScape(GL_MODELVIEW, Tree);
	list1->GenPlane(GL_QUADS, new vec::Vector3(MathHelper::normalizef(156, 255),
		MathHelper::normalizef(205, 255), MathHelper::normalizef(50, 255)));

	glutMainLoop();

	return 0;
}

void Game::resize(int width, int height)
{
	float ratio;
	if (height == 0) height = 1;
	ratio = 1.0 * width / height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 0.01, 1000);
	glMatrixMode(GL_MODELVIEW);
}

void Game::Update()
{
	Gamer->Update();
	Gamer->isColliding(colliderBox);
	glutPostRedisplay();
}

GLvoid Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 1.0, 1.0, 0.0);
	glCullFace(GL_BACK);
	glMatrixMode(GL_PROJECTION);	
	glViewport(0, 0, windowWidth, windowHeigth);
	glLoadIdentity();
	gluPerspective(45, windowWidth / windowHeigth, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Gamer->Draw();

#if _RENDER_LANDSCAPE 1
	glCallList(list1->getList(2));
#endif
#if _RENDER_PLANE 1
	//Desenhar plano
	glCallList(list1->getList(3));
#endif
#if _DEBUG_ 1
	deltaTime = (glutGet(GLUT_ELAPSED_TIME) * 0.001f) - time;
	frames++;
	time = glutGet(GLUT_ELAPSED_TIME) * 0.001f;
	if (time - startTime > 1.0f)
	{
		framesPS = frames / (time - startTime);
		startTime = time;
		frames = 0;
		system("cls");
		std::cout << "Elapsed Time: " << static_cast<int>(time) << std::endl;
		std::cout << "FPS: " << framesPS << std::endl;
	}
#endif
	glutSwapBuffers();
}

void Game::keyboardCallback(unsigned char KEY, int x, int y)
{
	std::cout << "Pressed: " << KEY << std::endl;
	KEYS[KEY] = true;
}

void Game::upCallback(unsigned char KEY, int x, int y)
{

	std::cout << "Released: " << KEY << std::endl;
	KEYS[KEY] = false;
}

char Game::getKeyPressed(unsigned char KEY)
{
	return KEYS[KEY];
}



