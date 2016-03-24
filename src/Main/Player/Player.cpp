#include "Player.h"
#include "../Keyboard/Keyboard.h"
#include "../Game.h"

Player::Player()
{
	Box = new PhysicsObject(vec::Vector3(0, 10, 0));
	player = new Object("../P3Dglut/Modelos3D/porsche.obj");
	player->loadModel();
	Game::list1->RenderModel(player);
	camera = new Camera(*this);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//Translate Player Positions
	if (Keyboard::getKeyPressed(KEY_D))
	{
		rotationAngle += deltaTime;
		Box->getRigidBody().rotate(rotationAngle);
	}
	if (Keyboard::getKeyPressed(KEY_A))
	{
		rotationAngle -= deltaTime;
		Box->getRigidBody().rotate(rotationAngle);
	}
	if (Keyboard::getKeyPressed(KEY_S)) {
		Box->getRigidBody().setFriction(0.96);
	}
	if (Keyboard::getKeyPressed(KEY_W))
	{
		Box->getRigidBody().setFriction(0.99);
		Box->getRigidBody().addForce(vec::Vector3(10000, 0, 10000));
	}
	camera->Update(deltaTime);
}

void Player::Draw() const
{
	camera->Draw();
	glPushMatrix();
	{
		glTranslatef(Box->getPosition().x, Box->getPosition().y, Box->getPosition().z);
		glRotatef(180 - rotationAngle * 180 / 3.14, 0.0, 1.0, 0.0);
		glRotatef(Box->getRigidBody().torque.x, 1.0, 0.0, 0.0);
		glRotatef(Box->getRigidBody().torque.y, 0.0, 1.0, 0.0);
		glRotatef(Box->getRigidBody().torque.z, 0.0, 0.0, 1.0);
		glCallList(Game::list1->getList(1));
	}
	glPopMatrix();
}

RigidBody& Player::getRigidBody() const
{
	return Box->getRigidBody();
}
