#ifndef _PLAYER_H_
#include "player.h"
#endif

#include <string>
#include "idrawable.h"
#include "vector3.h"

using std:: string;

Player::Player()
{
	bool _human = false;
	bool _canDraw = false;

	string _name = "";

	Deck _pairsDeck = Deck();
	Vector3 _center = Vector3();

	int _pairsFound = 0;
	int _drawPriority = 0;	
}

void Player::init(bool isHuman)
{
	if(isHuman)
	{

	}
}

int Player::getPairsFound()
{

}

Deck Player::getPairsDeck()
{

}

void Player::addPair(Card* card)
{

}

void Player::name(string newName)
{

}

Card* selectedCard(Vector3 position)
{

}

void Player::destroy()
{

}

void Player::enable()
{

}

void Player::disable()
{

}

bool Player::isEnabled()
{

}

int Player::getPriority()
{

}

void Player::setPriotity()
{

}

void Player::draw()
{

}