#ifndef _BOARD_H_
#include "board.h"
#endif

#include <iostream>
#include "game.h"
#include "Card.h"
#include "colorscheme.h"

using std::cerr;
using std::endl;
Board::Board()
{
	_center = Vector3();
	_rows = 0;
	_cols = 0;
	_canDraw = false;
	_drawPriority = -1;
	_cards = vector<Card*>();
	_flipAll = false;
	_flipTimer = -1.0f;
}

void Board::init(int rows, int cols)
{
	_rows = rows;
	_cols = cols;

	//Setup non-passed variables
	_center = Vector3(Game::WINDOW_WIDTH/2.0f, Game::WINDOW_HEIGHT/2.0f, 0.0f);
	_drawPriority = 2;
	Game::instance()->registerDrawable((IDrawable*)this);
	Game::instance()->registerUpdatable((IUpdatable*)this);
}

Vector2 Board::XYtoRC(Vector3& xy)
{
	float r = std::floor((xy.y - VERT_MARGIN) / (CARD_VMARGIN/2.0f+CARD_HEIGHT));
	float c = std::floor((xy.x - SIDE_MARGIN) / (CARD_HMARGIN+CARD_WIDTH));
	if(r<0)
		r = 0;
	if(r >= _rows)
		r = _rows;
	if(c<0)
		c = 0;
	if(c >= _cols)
		c = _cols;
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

void Board::placeCardOnBoard(int row, int col, Card* card)
{
	card->moveToRC(row, col);
	_cards.push_back(card);
}

void Board::removeCardFromBoard(Card* card)
{
	vector<Card*>::iterator it=_cards.begin();
	while(it!=_cards.end())
	{
		if((*it) == card)
		{
			it = _cards.erase(it);
			break; //should only get one match
		}
		++it;
	}
}

Card* Board::cardAtRowCol(int row, int col)
{
	vector<Card*>::iterator it;
	for(it=_cards.begin();it!=_cards.end();++it)
		if((*it)->getRowCol().x==(float)row && (*it)->getRowCol().y==(float)col)
			return (*it);
	return 0;
}

void Board::putAllCardsFaceDown()
{
	_flipAll = true;
	_flipTimer = 1000.0f; // in ms, I think
}

void Board::destroy()
{
	//Since no pointers I think we're okay here.
}

void Board::enableUpdates() { _canUpdate = true; }
void Board::disableUpdates() { _canUpdate = false; }
bool Board::canUpdate() { return _canUpdate; }

void Board::update(float dt)
{
	if(!_canUpdate)
		return;

	if(_flipAll)
	{
		if(_flipTimer > 0)
			_flipTimer-=dt;
		else
		{
			for(vector<Card*>::iterator it=_cards.begin();it!=_cards.end();++it)
			{
				if((*it)->faceUp())
					(*it)->flip();
			}
			_flipAll = false;
			
			//tell Game it's okay to switch players now
			//this prevents ambiguity when all cards are flipping
			Game::instance()->switchPlayers();
		}
	}
}

void Board::enable() { _canDraw = true; }
void Board::disable() { _canDraw = false; }
bool Board::isEnabled() { return _canDraw; }
int Board::getPriority() { return _drawPriority; }
void Board::setPriority(int newPriority) { _drawPriority = newPriority; }

void Board::draw()
{
	//doing this without textures just to make this work.
	//this should be chopped into squares for tiling the texture
	//or there's a gl function for doing so.  whatevs
	Color4 myColor = ColorScheme::GREEN;
	glBegin(GL_QUADS);
		glColor4fv(myColor.toArray());
		glVertex2f(_center.x - Game::HBOUND/2.0f, _center.y - Game::VBOUND/2.0f);
		glVertex2f(_center.x + Game::HBOUND/2.0f, _center.y - Game::VBOUND/2.0f);
		glVertex2f(_center.x + Game::HBOUND/2.0f, _center.y + Game::VBOUND/2.0f);
		glVertex2f(_center.x - Game::HBOUND/2.0f, _center.y + Game::VBOUND/2.0f);
	glEnd();
}