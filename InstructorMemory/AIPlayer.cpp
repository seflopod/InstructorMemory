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
}

AIPlayer::AIPlayer(int difficulty)
{
	_maxBufferSize = 2*difficulty;
	_cardBuffer = new Card*[_maxBufferSize];
	_nextSelect = 0;
	_cardsRemembered = 0;
	_selectedOneCard = false;
	_canUpdate = false;
}

void AIPlayer::init(const Color4 cGrad[2])
{
	Player::init(cGrad);
}

Card* AIPlayer::selectCard()
{
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
		bool goodSelect = false;
		while(!goodSelect)
		{
			//using magic numbers here because of design flaws
			int row = rand()%4;
			int col = rand()%5;
			Card* tmp = Game::instance()->getBoard()->cardAtRowCol(row, col);
			while(tmp == 0)
			{
				row = rand()%4;
				col = rand()%5;
				tmp = Game::instance()->getBoard()->cardAtRowCol(row, col);
			}

			//now that we have a possible card, check to see if it is in the buffer
			for(int i=0;i<_cardsRemembered;++i)
			{
				if(_cardBuffer[i] == tmp)
				{
					//already have this card in memory, let's find a new one
					break;
				}
				
				if(*_cardBuffer[i] == *tmp)
				{
					//cool, easy match
					_nextSelect = _cardBuffer[i];
					_selectedOneCard = true;
					_flipTimer = 0.0f;
					_canUpdate = true;
					return tmp;
				}
			}

			//card not in buffer, so must be good.  add it to the buffer
			if(_cardsRemembered < _maxBufferSize)
				_cardBuffer[_cardsRemembered++] = tmp;
			else
			{
				//do some other shit
			}
			return tmp;
		}
	}
	else //have already selected a card
	{
	}
}