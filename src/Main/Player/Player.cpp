#include "Player.h"
#include "../Keyboard/Keyboard.h"
#include "../Game.h"
#include "../../Misc/Physics/Mesh/AABB.h"
#include "../../Misc/Debug/IO.h"

Player::Player() 
	: collider(vec::Vector3(0, 0.5, 0), vec::Vector3(1, 1.5, 1))
{
	Box = new PhysicsObject(vec::Vector3(0, 1, 0), collider);
	//player = new Object("../P3Dglut/Modelos3D/porsche.obj");
	player->loadModel();
	camera = new Camera(*this);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//Translate Player Positions
	if (Keyboard::keyPressed())
	{
		rotationAngle += deltaTime;
		Box->getRigidBody().rotate(rotationAngle);
	}
	if (Keyboard::keyPressed())
	{
		rotationAngle -= deltaTime;
		Box->getRigidBody().rotate(rotationAngle);
	}
	if (Keyboard::keyPressed()) {
		Box->getRigidBody().setFriction(0.96);
	}
	if (Keyboard::keyPressed())
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
	}
	glPopMatrix();
}

RigidBody& Player::getRigidBody() const
{
	return Box->getRigidBody();
}
