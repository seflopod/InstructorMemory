
#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATHE_DEFINES
#include <math.h>
#include <time.h>

#include "Texture2D.h"
#include "Card.h"
#include "colorscheme.h"
#include "game.h"

using namespace std;

void keyboard(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mousePassive();
void reshape(int w, int h);
void initOpenGL();

int windowWidth;
int windowHeight;

/*TODO: move this to Game when we are actually doing stuff with textures
void buildTextures()
{
	boardT2D = new Texture2D("Content\\board.bmp");

	glGenTextures(1, &boardTex);
	glBindTexture(GL_TEXTURE_2D, boardTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, boardT2D -> width, boardT2D -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, boardT2D -> pixels);

	cardBackT2D = new Texture2D("Content\\cardBack.bmp");

	glGenTextures(1, &backTex);
	glBindTexture(GL_TEXTURE_2D, backTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cardBackT2D -> width, cardBackT2D -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, cardBackT2D -> pixels);

	cardFaceT2D = new Texture2D("Content\\cardFace.bmp");

	glGenTextures(1, &faceTex);
	glBindTexture(GL_TEXTURE_2D, faceTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cardFaceT2D -> width, cardFaceT2D -> height, 0, GL_RGB, GL_UNSIGNED_BYTE, cardFaceT2D -> pixels);
}*/

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
	//no reshape for you!
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

	//TODO: rewrite so that 0,0 is at bottom left
	//x = (x / (windowWidth / 2.0)) * bound;
	//y = (y / (windowHeight / 2.0)) * bound;
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

	//TODO: rewrite so that 0,0 is at bottom left
	//x = (x / (windowWidth / 2.0)) * bound;
	//y = (y / (windowHeight / 2.0)) * bound;

	//TODO: write code for functionality re: Player and Mouse class
}

int main(int argc, char** argv)
{
	windowWidth = Game::WINDOW_WIDTH;
	windowHeight = Game::WINDOW_HEIGHT;
	glutInit(&argc, argv);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Instructor Memory - A Peter & Ross Joint");

	initOpenGL();
	Game::instance()->init(1);

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
