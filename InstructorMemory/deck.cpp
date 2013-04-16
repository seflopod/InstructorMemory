#ifndef _DECK_H_
#include "deck.h"
#endif

#include <stdlib.h>
#include "game.h"
#include "Card.h"

using std::rand;

Deck::Deck()
{
	_nCards = 0;
	_maxCards = 0;
	_cards = 0;
	_canDraw = false;
	_drawPriority = -1;
	_center = Vector3();
}

void Deck::init(Card** cardArray, int nCards, int maxCards=52)
{
	_cards = cardArray;
	_nCards = nCards;
	_maxCards = maxCards;

	if(_cards==0)
		_cards = new Card*[maxCards];

	//set other variables
	_drawPriority = 5;
	Game::instance()->registerDrawable((IDrawable*)this);
}

void Deck::shuffleDeck()
{
	if(_cards==0 || _nCards==0)
		return;

	Card* tmp;
	int idx1;
	int idx2;
	for(int i=0;i<_nCards/4+1;++i)
	{
		for(int j=0;j<_nCards/2;++j)
		{
			idx1 = rand()%_nCards;
			idx2 = rand()%_nCards;
			tmp = _cards[idx1];
			_cards[idx1] = _cards[idx2];
			_cards[idx2] = tmp;
		}
	}
}

Card* Deck::dealCard()
{
	if(_nCards>0)
		return _cards[--_nCards];
	else
		return 0;
}

Card** Deck::dealCard(int number)
{
	if(number<0)
		return 0;

	if(number>_nCards)
		number = _nCards;
	
	Card** ret = new Card*[number];
	for(int i=0;i<number;++i)
		ret[i] = dealCard();

	return ret;
}

void Deck::placeCardOnDeck(Card* toPlace)
{
	if(_nCards < _maxCards)
		_cards[_nCards++] = toPlace;
}

Card** Deck::toArray()
{
	Card** ret = new Card*[_nCards];
	for(int i=0;i<_nCards;++i)
		ret[i] = _cards[i];
	return ret;
}

int Deck::deckSize() { return _nCards; }
int Deck::deckCapacity() { return _maxCards; }

void Deck::destroy()
{
	//this does not destroy the Cards
	delete[] _cards;
}

void Deck::enable() { _canDraw = true; }
void Deck::disable() { _canDraw = false; }
bool Deck::isEnabled() { return _canDraw; }
int Deck::getPriority() { return _drawPriority; }
void Deck::setPriority(int newPriority) { _drawPriority = newPriority;}

void Deck::draw()
{
	//TODO figure out how decks are drawn.
}