#ifndef _BOARD_H_
#include "board.h"
#endif

#include "game.h"
#include "Card.h"

const float CARD_WIDTH = 90.0f;
const float CARD_HEIGHT = 140.0f;
//TODO: define this shit when we have layout.
const float SIDE_MARGIN;
const float CARD_HMARGIN;
const float VERT_MARGIN;
const float CARD_VMARGIN;

Board::Board()
{
	_center = Vector3();
	_rows = 0;
	_cols = 0;
	_canDraw = false;
	_drawPriority = -1;
}

void Board::init(int rows, int cols)
{
	_rows = rows;
	_cols = cols;

	//Setup non-passed variables
	_drawPriority = 2;
	Game::instance()->registerDrawable((IDrawable*)this);
}

Vector2 Board::XYtoRC(Vector3& xy)
{
	float r = (xy.y-VERT_MARGIN-CARD_HEIGHT/2) / (CARD_VMARGIN+CARD_HEIGHT);
	float c = (xy.x-SIDE_MARGIN-CARD_WIDTH/2) / (CARD_HMARGIN+CARD_WIDTH);
	return Vector2(r, c);
}

Vector3 Board::RCtoXY(Vector2& rc)
{
	float x = SIDE_MARGIN + CARD_WIDTH/2;
	float y = VERT_MARGIN + CARD_HEIGHT/2;
	x+=rc.y*(CARD_HMARGIN+CARD_WIDTH);
	y+=rc.x*(CARD_VMARGIN+CARD_HEIGHT);
	return Vector3(x, y, 0.0f);
}

void Board::enable() { _canDraw = true; }
void Board::disable() { _canDraw = false; }
bool Board::isEnabled() { return _canDraw; }
int Board::getPriority() { return _drawPriority; }
void Board::setPriority(int newPriority) { _drawPriority = newPriority; }

void Board::draw()
{
	//this is just a simple box with a texture
	//need to figure out if we want to tile or scale thought
	//and how to make that happen...
}