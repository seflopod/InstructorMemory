

#include <iostream>
#include <GL\freeglut.h>
#define _USE_MATHE_DEFINES
#include <math.h>
#include <time.h>

#include "Texture2D.h"
#include "Card.h"

using namespace std;

void display();
void keyboard(unsigned char key, int x, int y);
void mouseButton(int button, int state, int x, int y);
void mousePassive();
void reshape(int w, int h);
void initOpenGL();
void initGame();
void update(int value);

Card cards [4][5];

const int fps = 27;

clock_t currentTime;
clock_t lastCurrentTime;

int windowWidth = 800;
int windowHeight = 600;
int bound = 550;

Texture2D* boardT2D;
Texture2D* cardBackT2D;
Texture2D* cardFaceT2D;
GLuint boardTex;
GLuint backTex;
GLuint faceTex;

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
}

void initOpenGL()
{
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-bound,bound,-bound,bound,-bound,bound);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void initGame()
{	
	int xStart = -85;
	int yStart = 85;
	
	//this is the math for how the cards will draw
	for(int r = 0; r < 10; ++r) 
	{
		for(int c = 0; c < 10; ++c)
		{
			cards[r][c] = Card();
			cards[r][c].x = xStart;
			cards[r][c].y = yStart;
			xStart += cards[r][c].cardSize * 2 + 1;
		}
		xStart = -85;
		yStart -= cards[r][0].cardSize * 2 + 1;
	}

	//background = Card();
	//background.cardSize = 100;

	buildTextures();

	currentTime = clock();
	lastCurrentTime = currentTime;
}

void reshape(int width, int height)
{
	glutReshapeWindow(width,height);
	glViewport(0,0,width,height);

	windowWidth = width;
	windowHeight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-bound,bound,-bound,bound,-bound,bound);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	//this is where I draw my background
	//background.drawBackground(brickTexture);

	//this is where the cards are drawn
	for(int r = 0; r < 10; ++r)
	{
		for(int c = 0; c < 10; ++c)
		{
			cards[r][c].draw();
		}
	}
	
	glutSwapBuffers();
}

void update(int value)
{
	lastCurrentTime = currentTime;
	currentTime = clock();

	float deltaT = difftime(currentTime, lastCurrentTime) / 10000.0;
	float deltaTSqDiv2 = (deltaT * deltaT) * 0.5;

	glutTimerFunc(fps,update,0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

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

	x = (x / (windowWidth / 2.0)) * bound;
	y = (y / (windowHeight / 2.0)) * bound;
	button = (1 << button);
	
	const int LEFT_MOUSE = 1;
	const int MIDDLE_MOUSE = 2;
	const int RIGHT_MOUSE = 4;

	cerr << x << " " << y << endl;

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

	x = (x / (windowWidth / 2.0)) * bound;
	y = (y / (windowHeight / 2.0)) * bound;

	for(int r = 0; r < 10; ++r) 
	{
		for(int c = 0; c < 10; ++c)
		{
			if(cards[r][c].collideWithCard(x,y))
			{
				cards[r][c].isLit = true;
			}
			else
			{
				cards[r][c].isLit = false;
			}
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(1000,1000);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("A5");

	initOpenGL();
	initGame();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mousePassive);
	glutTimerFunc(fps, update, 0);
	glutMainLoop();

	return 0;
}