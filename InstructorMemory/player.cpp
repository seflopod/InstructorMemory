#ifndef _PLAYER_H_
#include "player.h"
#endif

#include <iostream>
#include <string>
#include "idrawable.h"
#include "game.h"
#include "Board.h"
#include "vector3.h"
#include "deck.h"
#include "Card.h"
#include "colorscheme.h"

using std::string;
using std::cerr;
using std::endl;

Player::Player()
{
	_human = false;
	_name = "";
	_pairsDeck = 0;
	_pairsFound = 0;
	_canDraw = false;
	_drawPriority = 0;
	Vector3 _center = Vector3();
	_color1 = ColorScheme::RED;
	_color2 = ColorScheme::BLACK;
}

//right now not dealing with humanity, trying to figure out best way
void Player::init(bool isHuman, const Color4 cGrad[2])
{
	_color1 = cGrad[0];
	_color2 = cGrad[1];
	//other inits
	_drawPriority = 12;
	Game::instance()->registerDrawable((IDrawable*)this);
	_pairsDeck = new Deck();
	_pairsDeck->init(0,0,20);
}

int Player::getPairsFound() { return _pairsFound; }
Deck* Player::getPairsDeck() { return _pairsDeck; }

void Player::addPair(Card* card)
{
	_pairsDeck->placeCardOnDeck(card);
	++_pairsFound;
}

string Player::name() { return _name; }
void Player::name(string newName) { _name = newName; }

Card* Player::selectCard()
{
	Vector2 rc = Game::instance()->getBoard()->XYtoRC(_center);
	return (Game::instance()->getBoard()->cardAtRowCol((int)rc.x, (int)rc.y));
}

void Player::moveTo(float x, float y)
{
	Vector2 rc = Game::instance()->getBoard()->XYtoRC(Vector3(x, y, 0.0f));
	Vector3 potC = Game::instance()->getBoard()->RCtoXY(rc);
	if(potC != _center)
		_center = potC;
}

void Player::destroy()
{
	if(_pairsDeck != 0)
	{
		_pairsDeck->destroy();
		delete _pairsDeck;
		_pairsDeck = 0;
	}
}

//IDrawable
void Player::enable() { _canDraw = true; }
void Player::disable() { _canDraw = false; }
bool Player::isEnabled() { return _canDraw; }
int Player::getPriority() { return _drawPriority; }
void Player::setPriority(int newPriority) { _drawPriority = newPriority; }

void Player::draw()
{
	if(_canDraw)
	{
		_center = Game::instance()->getBoard()->RCtoXY(Game::instance()->getBoard()->XYtoRC(_center));
		glLineWidth(5.0f);
		glBegin(GL_LINE_LOOP);
			glColor4fv(_color1.toArray());
			glVertex2f(_center.x - Board::CARD_WIDTH/2.0f, _center.y + Board::CARD_HEIGHT/2.0f);
			glColor4fv(_color2.toArray());
			glVertex2f(_center.x - Board::CARD_WIDTH/2.0f, _center.y - Board::CARD_HEIGHT/2.0f);
			glVertex2f(_center.x + Board::CARD_WIDTH/2.0f, _center.y - Board::CARD_HEIGHT/2.0f);
			glColor4fv(_color1.toArray());
			glVertex2f(_center.x + Board::CARD_WIDTH/2.0f, _center.y + Board::CARD_HEIGHT/2.0f);
		glEnd();
	}
}