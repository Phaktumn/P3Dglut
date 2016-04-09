#include "Keyboard.h"

void Keyboard::keydoardCallback(unsigned char KEY, int x, int y)
{ hhb_vkey_list[KEY].pressed = true; }

void Keyboard::keyboardUpCallback(unsigned char KEY, int x, int y)
{ hhb_vkey_list[KEY].pressed = false; }

bool Keyboard::getKeyPressed(unsigned char KEY)
{ return hhb_vkey_list[KEY].pressed; }

//NOT WORKING
char Keyboard::keyPressed()
{
	for (unsigned int i = 0; i < 177; i++){
		if (hhb_vkey_list[i].pressed == true)
			return hhb_vkey_list[i].vkey;
	}
	return NULL;
}
