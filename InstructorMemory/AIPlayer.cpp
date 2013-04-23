#ifndef _AIPLAYER_H_
#include "AIPlayer.h"
#endif

#include <random>
#include "game.h"
#include "color4.h"
#include "Card.h"
#include "Board.h"

AIPlayer::AIPlayer()
{
	_cardBuffer = 0;
	_maxBufferSize = 0;
	_cardsRemembered = 0;
	_selectedOneCard = false;
	_canUpdate = false;
	_nextSelect = 0;
	_bufferIdx = 0;
	_selected = 0;
	_flipWait = 0.0f;
}

AIPlayer::AIPlayer(int difficulty)
{
	_maxBufferSize = 2*difficulty;
	_cardBuffer = new Card*[_maxBufferSize];
	_nextSelect = 0;
	_cardsRemembered = 0;
	_selectedOneCard = false;
	_canUpdate = false;
	_bufferIdx = 0;
	_selected = 0;
	_flipWait = 0.0f;
}

void AIPlayer::init(const Color4 cGrad[2])
{
	Player::init(cGrad);
	_human = false;
	_flipWait = 0.5f;
	Game::instance()->registerUpdatable((IUpdatable*)this);
}

Card* AIPlayer::selectCard()
{
	Card* ret;
	if(!_selectedOneCard) //beginning of turn
	{
		//first check to see if there are any pairs the player's missed
		//because Card does not have < or > operators, and because this is a
		//very simple implementation, this is a brute force approach.  Since the
		//difficulty should never be too high, I think we should be okay for
		//now.
		_nextSelect = 0;
		for(int i=0;i<_cardsRemembered-1;++i)
		{
			Card* tmp = _cardBuffer[i];
			for(int j=i+i;j<_cardsRemembered;++i)
			{
				if(*tmp == *_cardBuffer[j])
				{
					_nextSelect = _cardBuffer[j];
					_selectedOneCard = true;
					_flipTimer = 0.0f;
					_canUpdate = true;
					return tmp;
				}
			}
		}

		//if here, then we didn't catch a pair the player missed, so pick
		//a card at random that is NOT in the buffer
		ret = findCardToSelect();
	}
	else //have already selected a card
	{
		if(_nextSelect != 0) //might have a shortcut to a match
		{
			//verify that the card is still there
			Vector2 rc = _nextSelect->getRowCol();
			if(Game::instance()->getBoard()->cardAtRowCol(rc.x, rc.y) != 0)
				ret = _nextSelect;
			
			_nextSelect = 0; //regardless, we don't have a next selection
		}

		//since we do not have an easy match, that means we have to guess.
		ret = findCardToSelect();
	}

	_selectedOneCard = !_selectedOneCard;
	//move to the possible card's position
	//should really try to get this to force a draw while looking to get a cool
	//effect
	Vector2 rc = ret->getRowCol();
	Vector3 newPos = Game::instance()->getBoard()->RCtoXY(Vector2((float)rc.x, (float)rc.y));
	moveTo(newPos.x, newPos.y);
	
	return ret;
}

void AIPlayer::setBufferSize(int newSize)
{
	//we're not going to allow difficulty to change mid-game, so
	//first check for buffer already existing.
	if(_cardBuffer == 0)
	{
		_maxBufferSize = newSize;
		_cardBuffer = new Card*[_maxBufferSize];
	}
}

int AIPlayer::getBufferSize() { return _maxBufferSize; }

int AIPlayer::getCardsRemembered() { return _cardsRemembered; }

Card** AIPlayer::getCardBuffer() { return _cardBuffer; }

//IUpdatable implementation
void AIPlayer::enableUpdates() { _canUpdate = true; }
void AIPlayer::disableUpdates() { _canUpdate = false; }
bool AIPlayer::canUpdate() { return _canUpdate; }

void AIPlayer::update(float dt)
{
	if(!_canUpdate)
		return;

	_flipTimer+=dt;
	if(_flipTimer >= _flipWait)
	{
		//is this all that's needed?
		_canUpdate = false;
	}
}

Card* AIPlayer::findCardToSelect()
{
	Card* tmp = 0;
	bool goodSelect = false;
	while(!goodSelect)
	{
		//we'll get a good card this time!
		goodSelect = true;

		//using magic numbers here because of design flaws
		int row = rand()%4;
		int col = rand()%5;
		Card* tmp = Game::instance()->getBoard()->cardAtRowCol(row, col);
			
		//make sure the slot we select has a card in it
		while(tmp == 0)
		{
			row = rand()%4;
			col = rand()%5;
			tmp = Game::instance()->getBoard()->cardAtRowCol(row, col);
		}

		//move to the possible card's position
		//should really try to get this to force a draw
		Vector3 newPos = Game::instance()->getBoard()->RCtoXY(Vector2((float)row, (float)col));
		moveTo(newPos.x, newPos.y);

		//now that we have a possible card, check to see if it is in the buffer
		for(int i=0;i<_cardsRemembered;++i)
		{
			if(_cardBuffer[i] == tmp)
			{
				//already have this card in memory, let's find a new one
				goodSelect = false;
				break;
			}
				
			//is there an easy match for the card?
			//we only care if this is the first card for the turn
			if(!_selectedOneCard && *_cardBuffer[i] == *tmp)
			{
				//cool, easy match
				_nextSelect = _cardBuffer[i];
			}
		}
	}

	//card not in buffer, so must be good.  add it to the buffer
	if(_cardsRemembered < _maxBufferSize)
	{
		++_cardsRemembered;
	}
	else if(_bufferIdx >= _maxBufferSize)
	{
		_bufferIdx = 0;
	}
	_cardBuffer[_bufferIdx++] = tmp;

	_flipTimer = 0.0f;
	_canUpdate = true;

	return tmp;
}