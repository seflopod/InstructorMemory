

#ifndef CARD_H
#define CARD_H

#include <GL\freeglut.h>
#include <iostream>
#include <stdlib.h>
#include "idrawable.h"

class Card: public IDrawable
{
public:
	Card();
	Card(int rowX, int columnY);

	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual void draw();

	bool collideWithCard(int x, int y);
	bool isLit;

	int x;
	int y;

	float cardSize;

private:
	bool canDraw;

	GLuint faceTex;
	GLuint backTex;

	int row;
	int column;
};
#endif