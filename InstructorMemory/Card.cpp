

#ifndef CLASS_H
#include "Card.h"
#endif

#include "idrawable.h"

using namespace std;

Card::Card()
{
	cardSize = 20;
	row = 0;
	column = 0;

	x = 0; //width
	y = 0; //height

	canDraw = false;
	isLit = false;
}

void Card::enable()
{
	canDraw = true;
}

void Card::disable()
{
	canDraw = false;
}

bool Card::isEnabled()
{
	return canDraw;
}

void Card::draw()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, backTex);
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	glBegin(GL_QUADS);
		//glColor3f(0,0,1);
		glTexCoord2f(0,1); glVertex2f(x - cardSize, y + cardSize);
		glTexCoord2f(0,0); glVertex2f(x - cardSize, y - cardSize);
		glTexCoord2f(1,0); glVertex2f(x + cardSize, y - cardSize);
		glTexCoord2f(1,1); glVertex2f(x + cardSize, y + cardSize);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

bool Card::collideWithCard(int x, int y)
{
	float left = this -> x - cardSize;
	float right = this -> x + cardSize;
	float top = this -> y + cardSize;
	float bottom = this -> y - cardSize;

	return (x >= left && x <= right && y >= bottom && y <= top);
}