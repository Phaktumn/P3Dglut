#include "Keyboard.h"

float Keyboard::KEYS[156];
void Keyboard::keydoardCallback(unsigned char KEY, int x, int y){ KEYS[KEY] = true; }
void Keyboard::keyboardUpCallback(unsigned char KEY, int x, int y){ KEYS[KEY] = false; }
bool Keyboard::getKeyPressed(unsigned char KEY){ return KEYS[KEY]; }
