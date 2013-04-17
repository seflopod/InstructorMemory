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
	bool _human = false;
	bool _canDraw = false;

	string _name = "";

	Deck* _pairsDeck = new Deck();
	Vector3 _center = Vector3();

	int _pairsFound = 0;
	int _drawPriority = 0;
	_color1 = ColorScheme::HERZING_GOLD_GRAD[0];
	_color2 = ColorScheme::HERZING_GOLD_GRAD[1];
}

void Player::init(bool isHuman, const Color4 cGrad[2])
{
	_color1 = cGrad[0];
	_color2 = cGrad[1];
	_drawPriority = 12;
	Game::instance()->registerDrawable((IDrawable*)this);
	if(isHuman)
	{

	}
}

int Player::getPairsFound()
{
	return 0;
}

Deck* Player::getPairsDeck()
{
	return 0;
}

void Player::addPair(Card* card)
{

}

void Player::name(string newName)
{

}

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
	cerr << rc << "->" << _center << endl;
}

void Player::destroy()
{

}

void Player::enable()
{
	_canDraw = true;
}

void Player::disable()
{
	_canDraw = false;
}

bool Player::isEnabled()
{
	return _canDraw;
}

int Player::getPriority()
{
	return _drawPriority;
}

void Player::setPriority(int newPriority)
{
	_drawPriority = newPriority;
}

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