#include "Player.h"
#include "../Keyboard/Keyboard.h"
#include "../Game.h"

Player::Player()
{
	transform = new Transform();
	player = new Object("../P3Dglut/Modelos3D/porsche.obj");
	player->loadModel();
	Game::list1->RenderModel(player);
	camera = new Camera(this);
}


Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//Translate Player Positions
	if (Keyboard::getKeyPressed(KEY_D))
	{
		rotationAngle += 1 * deltaTime;
		transform->Rotate(rotationAngle);
	}
	if (Keyboard::getKeyPressed(KEY_A))
	{
		rotationAngle -= 1 * deltaTime;
		transform->Rotate(rotationAngle);
	}
	if (Keyboard::getKeyPressed(KEY_S)) {
		transform->body->atrt = 0.96f;
	}
	if (Keyboard::getKeyPressed(KEY_W))
	{
		transform->body->atrt = 0.995f;
		transform->Move(12000);
	}
	transform->update(Game::deltaTime);
	camera->Update(deltaTime);
}

void Player::Draw() const
{
	camera->Draw();
	glPushMatrix();
	{
		glTranslatef(transform->getPosition().x, transform->getPosition().y, transform->getPosition().z);
		glRotatef(180 - rotationAngle * 180 / 3.14, 0.0, 1.0, 0.0);
		glRotatef(transform->linearRot.x, 1.0, 0.0, 0.0);
		glRotatef(transform->linearRot.y, 0.0, 1.0, 0.0);
		glRotatef(transform->linearRot.z, 0.0, 0.0, 1.0);
		glCallList(Game::list1->getList(1));
	}
	glPopMatrix();
}
