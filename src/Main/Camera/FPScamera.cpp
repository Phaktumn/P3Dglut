#include "FPScamera.h"
#include <Vars/EulerAngle.h>
#include <Main/Mouse/Mouse.h>
#include <Main/Keyboard/Keyboard.h>

FPScamera::~FPScamera()
{
	if(angle != nullptr)
		delete angle;
	delete settings;
}

void FPScamera::Update(float deltaTime)
{
	computeMouse();
	if (diff.x != 0.0f || diff.y != 0.0f)
	{
		yaw += (currentMousePosition.x - viewPortCenter.x) * sensitivity;
		pitch -= (currentMousePosition.y - viewPortCenter.y) * sensitivity;
		pitch = MathHelper::Clampf(pitch, -89.0f, 89.0f);

		angle = new EulerAngle(yaw, pitch, 0);

		forwardVec = angle->toVector3();
		forwardVec.Normalized();

		rightVector = Vector3::Cross(Vector3::up(), forwardVec);
		rightVector.Normalized();

		upVec = forwardVec - Vector3(0,sin(180),0);
		//upVec = vec::Vector3::Cross(forwardVec, rightVector);
		upVec.Normalized();

		delete angle;
	}

	if(Keyboard::getKeyPressed(KEY_W)) 
	{
		m_Position += forwardVec * deltaTime * speed;
	}
	if (Keyboard::getKeyPressed(KEY_S)) 
	{
		m_Position -= forwardVec * deltaTime * speed;
	}
	if (Keyboard::getKeyPressed(KEY_D)) 
	{
		m_Position -= rightVector * deltaTime * speed;
	}
	if (Keyboard::getKeyPressed(KEY_A)) 
	{
		m_Position += rightVector * deltaTime * speed;
	}

	eye = m_Position;
	m_lookAt = m_Position + forwardVec;
	//upVec = upVec;
	Camera::Update(deltaTime);
}

void FPScamera::Draw() const
{
	Camera::Draw();
}

void FPScamera::computeMouse()
{
	viewPortCenter = Vector3(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, 0);
	prevMousePos = currentMousePosition;
	currentMousePosition = Mouse::getMousePos();
	diff = Vector3((currentMousePosition - prevMousePos).x,
		(currentMousePosition - prevMousePos).y, 0.0);
}
