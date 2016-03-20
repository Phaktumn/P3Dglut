#include "Player.h"
#include "../Game.h"

Player::Player()
{
	transform = new Transform();
	player = new Object("C:/Users/Jorge-Programar/Documents/GitHub/P3Dglut/Modelos3D/porsche.obj");
	player->loadModel();
	Game::list1->RenderModel(player);
}


Player::~Player()
{
}

void Player::Update()
{
	//Translate Player Positions
	if (Game::getKeyPressed('d'))
	{
		rotationAngle += 1 * Game::deltaTime;
		transform->Rotate(rotationAngle);
	}
	if (Game::getKeyPressed('a'))
	{
		rotationAngle -= 1 * Game::deltaTime;
		transform->Rotate(rotationAngle);
	}
	if (Game::getKeyPressed('s'))
	{
		transform->Move(-2, 0.01f);
	}
	if (Game::getKeyPressed('w'))
	{
		transform->Move(2, 0.01f);
	}
	transform->update(Game::deltaTime);
}

void Player::Draw() const
{
TODO: //CAMERA get a camera workin

	gluLookAt(transform->getPosition().x + -sin(rotationAngle) * 5, transform->getPosition().y + 2,
		transform->getPosition().z + cos(rotationAngle) * 5,
		transform->getPosition().x + transform->getRotation().x, transform->getPosition().y + transform->getRotation().y,
		transform->getPosition().z + transform->getRotation().z,
		transform->getRotation().x, 1.0, transform->getRotation().z);

	glPushMatrix();
	{
		glTranslatef(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
		glRotatef(180 - rotationAngle * 180 / 3.14, 0.0, 1.0, 0.0);
		glCallList(Game::list1->getList(1));
	}
	glPopMatrix();
}

void Player::isColliding(BoxCollider* collider) const
{
	transform->isColliding(collider);
}
