
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
void dispHelp();

int windowWidth;
int windowHeight;

void initOpenGL()
{
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
	case 'h': dispHelp(); break;

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
			Game::instance()->leftClick(newX, newY);
			break;
		case RIGHT_MOUSE:
			break;
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

	//This should be just passed off, but for now I'm doing real work
	if(Game::state() == Game::GameState::Playing)
		if(Game::instance()->getCurrentPlayer()->isHuman())
			Game::instance()->getCurrentPlayer()->moveTo(newX, newY);
	//TODO: write code for functionality re: Player and Mouse class
	glutPostRedisplay();
}

void dispHelp()
{
	cerr << "	Help Menu\n" << endl;
	cerr << "Left click on a card to flip it." << endl;
	cerr << "After you flip a card try and match" << endl;
	cerr << "that card with another on the board." << endl;
	cerr << "You can do this by either guessing" << endl;
	cerr << "or remembering a card that you flipped" << endl;
	cerr << "earlier. The player with the most pairs" << endl;
	cerr << "matched wins." << endl;
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
	Game::instance()->init();

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