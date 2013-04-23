#ifndef _SCOREBOARD_H_
#include "scoreboard.h"
#endif

#include <string>
#include <sstream>

#include "game.h"
#include "Board.h"
#include "colorscheme.h"
#include "player.h"

Scoreboard::Scoreboard()
{
	_canDraw = false;
	_drawPriority = 0;
}

void Scoreboard::init()
{
	_drawPriority = 20;
	Game::instance()->registerDrawable((IDrawable*)this);
}

void Scoreboard::enable() { _canDraw = true; }
void Scoreboard::disable() { _canDraw = false; }
bool Scoreboard::isEnabled() { return _canDraw; }
int Scoreboard::getPriority() { return _drawPriority; }
void Scoreboard::setPriority(int drawPriority) { _drawPriority = drawPriority; }

void Scoreboard::draw()
{
	if(!_canDraw)
		return;

	Color4 myColor = ColorScheme::WHITE;
	glColor3fv(myColor.toArray());
	ostringstream nConvert;

	float x = Board::CARD_WIDTH*6 + Board::CARD_HMARGIN*5;
	float y = Game::VBOUND-4*Board::VERT_MARGIN;
	nConvert << Game::instance()->getPlayer(0)->name() << ": " <<
				Game::instance()->getPlayer(0)->getPairsFound() << endl <<
				endl <<	Game::instance()->getPlayer(1)->name() << ": " <<
				Game::instance()->getPlayer(1)->getPairsFound();
	string disp = nConvert.str();
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)disp.c_str());
}