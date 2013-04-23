
#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATHE_DEFINES
#include <math.h>
#include <time.h>
#include <string>
#include "Texture2D.h"
#include "Card.h"
#include "colorscheme.h"
#include "game.h"
#include "Board.h"
#include "Card.h"
#include "player.h"

using namespace std;

void keyboard(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mousePassive();
void reshape(int w, int h);
void initOpenGL();

int windowWidth;
int windowHeight;

void initOpenGL()
{
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,Game::HBOUND, 0,Game::VBOUND, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height)
{
	glutReshapeWindow(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	glViewport(0,0,Game::HBOUND, Game::VBOUND);

	windowWidth = Game::WINDOW_WIDTH;
	windowHeight = Game::WINDOW_HEIGHT;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,Game::HBOUND, 0,Game::VBOUND, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	//TODO: put in keyboard class if my goddamn bindings work
	switch(key)
	{
	
	case 27: glutLeaveMainLoop(); break;
	case ' ': 
	case 'r':

	default: break;
	}

	glutPostRedisplay();
}

void mouseButton(int button,int state,int x,int y)
{
	x = -1 * ((windowWidth / 2) - x - 1);
	y = ((windowHeight / 2) - y - 1);

	//convert local screen to glOrtho (the world coordinates we created)
	float newX = (x/(windowWidth/2.0f) * Game::HBOUND + Game::HBOUND)/2; //technically xBound
	float newY = (y/(windowHeight/2.0f) * Game::VBOUND + Game::VBOUND)/2; //technically yBound.
	button = (1 << button);
	
	//TODO: put in enum
	const int LEFT_MOUSE = 1;
	const int MIDDLE_MOUSE = 2;
	const int RIGHT_MOUSE = 4;

	//TODO: write code for functionality re: Player and Mouse class
	if(state == GLUT_DOWN)
	{
		switch(button)
		{
		case LEFT_MOUSE:
			{
				//make sure player location is under mouse
				Game::instance()->getCurrentPlayer()->moveTo(newX, newY);
				Game::instance()->leftClick();
			}
		case RIGHT_MOUSE:
			{

			}
		default: break;
		}
	}

	glutPostRedisplay();
}

void mousePassive(int x, int y)
{
	x = -1 * ((windowWidth / 2) - x - 1);
	y = ((windowHeight / 2) - y - 1);

	//convert local screen to glOrtho (the world coordinates we created)
	float newX = (x/(windowWidth/2.0f) * Game::HBOUND + Game::HBOUND)/2; //technically xBound
	float newY = (y/(windowHeight/2.0f) * Game::VBOUND + Game::VBOUND)/2; //technically yBound.
	//cerr << newX << ", " << newY << endl;
	Game::instance()->getCurrentPlayer()->moveTo(newX, newY);
	//TODO: write code for functionality re: Player and Mouse class
}

int main(int argc, char** argv)
{
	windowWidth = Game::WINDOW_WIDTH;
	windowHeight = Game::WINDOW_HEIGHT;
	glutInit(&argc, argv);
	glutInitWindowPosition(50, 10);
	glutInitWindowSize(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Instructor Memory - A Peter & Ross Joint");

	initOpenGL();
	//difficulty goes from 1 to 5, with 2*difficulty pairs of cards
	Game::instance()->init(5);

	glutDisplayFunc(Game::display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mousePassive);
	glutTimerFunc(Game::FPS, Game::update, 0);
	glutMainLoop();
	Game::instance()->destroy();
	return 0;
}


