#pragma once

#define KEY_W             'w'
#define KEY_A             'a'
#define KEY_B             'b'
#define KEY_C             'c'
#define KEY_D             'd'
#define KEY_E             'e'
#define KEY_F             'f'
#define KEY_G             'g'
#define KEY_H             'h'
#define KEY_I             'i'
#define KEY_J             'j'
#define KEY_K             'k'
#define KEY_L             'l'
#define KEY_M             'm'
#define KEY_N             'n'
#define KEY_O             'o'
#define KEY_P             'p'
#define KEY_Q             'q'
#define KEY_R             'r'
#define KEY_S             's'
#define KEY_T             't'
#define KEY_U             'u'
#define KEY_V             'v'
#define KEY_X             'x'
#define KEY_Y             'y'
#define KEY_Z             'z'
#define KEY_LEFT          GLUT_KEY_LEFT
#define KEY_RIGHT         GLUT_KEY_RIGHT
#define	KEY_UP            GLUT_KEY_UP
#define KEY_DOWN          GLUT_KEY_DOWN
#define KEY_F1            GLUT_KEY_F1					//F1 function key
#define KEY_F2            GLUT_KEY_F2					//F2 function key
#define KEY_F3            GLUT_KEY_F3		            //F3 function key
#define KEY_F4            GLUT_KEY_F4		            //F4 function key
#define KEY_F5            GLUT_KEY_F5		            //F5 function key
#define KEY_F6            GLUT_KEY_F6		            //F6 function key
#define KEY_F7            GLUT_KEY_F7		            //F7 function key
#define KEY_F8            GLUT_KEY_F8		            //F8 function key
#define KEY_F9            GLUT_KEY_F9		            //F9 function key
#define KEY_F10           GLUT_KEY_F10		            //F10 function key
#define KEY_F11           GLUT_KEY_F11		            //F11 function key
#define KEY_F12           GLUT_KEY_F12		            //F12 function key
#define KEY_PAGE_UP       GLUT_KEY_PAGE_UP	            //Page Up function key
#define KEY_PAGE_DOWN     GLUT_KEY_PAGE_DOWN            //Page Down function key
#define KEY_HOME          GLUT_KEY_HOME		            //Home function key
#define KEY_END           GLUT_KEY_END		            //End function key
#define KEY_INSERT        GLUT_KEY_INSERT	            //Insert function key

class Keyboard
{
public:
	static void keydoardCallback(unsigned char KEY, int x, int y);
	static void keyboardUpCallback(unsigned char KEY, int x, int y);
	static bool getKeyPressed(unsigned char KEY);

private:
	static float KEYS[];
};

