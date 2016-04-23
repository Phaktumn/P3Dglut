#include "Keyboard.h"

float Keyboard::KEYS[256];

void Keyboard::keydoardCallback(unsigned char KEY, int x, int y)
{
	KEYS[KEY] = true; 
}

void Keyboard::keyboardUpCallback(unsigned char KEY, int x, int y)
{
	KEYS[KEY] = false; 
}

bool Keyboard::getKeyPressed(unsigned char KEY)
{
	return KEYS[KEY];
}

//NOT WORKING
char Keyboard::keyPressed()
{
	for (unsigned int i = 0; i < 256; i++){
		if (KEYS[i] == true) {
			return KEYS[i];
		}
	}
	return NULL;
}
