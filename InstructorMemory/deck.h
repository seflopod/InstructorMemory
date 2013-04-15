/*deck.h
 * Peter Bartosch and Ross Greenman
 * created: 4/15/2013
 * last modified: 4/15/2013
 * IS346 - Instructor Memory
 * Kahn
 *
 * defines class: Deck
 * A Deck is a stack-like container for Cards.  It implements IDrawable.  It is
 * constructed and then init'd with an array of Cards.  The deck can be
 * shuffled (the underlying array is shuffled), and Cards can be dealt (popped)
 * or added to (push on front or back) the deck.  More features could be added
 * to the class (the ability to put Cards on the bottom of the Deck, or the
 * ability to merge Decks, for instance), but unless those are needed they are
 * beyond the scope of the project and will not be added at this time.
 *
 * Card is forward-declared instead of included in this header due to division
 * of labour.
 *
 * TODO: Add methods for getting/setting texture or color for draw
 *		implementation along with necessary variables.
 */
#ifndef _DECK_H_
#define _DECK_H_

#include "idrawable.h"

class Card;

class Deck : public IDrawable
{
public:
	/*Deck()
	 * takes: nothing
	 * returns: nothing
	 *
	 * Default ctor that inits all class-variables to NULL (or equivilant).
	 *
	 */
	Deck();

	/*init(cardArray, nCards, maxCards)
	 * takes: an array of Cards, the number of cards passed and the maximum
	 *			number of cards allowed for the Deck.
	 * returns: nothing
	 *
	 * This initializes the Deck using the passed information.  The draw
	 * information is default to a priority of 1 with a center at the origin. 
	 * By default the Deck is NOT drawn.  If NULL is passed for the card array
	 * (or 0 for nCards), then the Deck is created with no Cards, but with a
	 * max number.  maxCards defaults to 52 (like a poker deck).
	 *
	 * This can also be used to reinitialize a Deck and will clean up before
	 * recreating the Deck.
	 *
	 */
	void init(Card* cardArray, int nCards, int maxCards=52);

	/*shuffleDeck()
	 * takes: nothing
	 * returns: nothing
	 *
	 * Shuffles the Card array to create put the Cards in random order.
	 *
	 */
	void shuffleDeck();

	/*dealCard()
	 * takes: nothing
	 * returns: a Card
	 *
	 * Removes one Card from the deck.  This will decrease the number of cards
	 * in the deck.  The effect is one of popping
	 *
	 * This should probably return a Card*, and this would require changing the
	 * underlying structure and too much effort at the moment.
	 *
	 */
	Card dealCard();

	/*dealCard(number)
	 * takes: the number of Cards to deal
	 * returns: a Card array of size number
	 *
	 * This is just a variant on dealCard that will deal more than one Card at
	 * a time.
	 *
	 */
	Card* dealCard(int number);

	/*placeCardOnDeck(toPlace)
	 * takes: a Card to place on top of the deck
	 * returns: nothing
	 *
	 * This will put a card on the top of the Deck (like pushing).
	 *
	 */
	void placeCardOnDeck(Card toPlace);

	/*placeCardsOnDeck(toPlace, nCards)
	 * takes: an array of Cards and its size
	 * returns: nothing
	 *
	 * A multi-card version of placeCardOnDeck.  The last element of the passed
	 * array is the last element added.
	 *
	 */
	void placeCardsOnDeck(Card* toPlace, int nCards);

	/*toArray()
	 * takes: nothing
	 * returns: the Deck as an array of Cards
	 *
	 * NOTE: this does not return the number of Cards, so to avoid out of bounds
	 * errors it is up to the user to first figure out how many cards are in the
	 * Deck.
	 *
	 */
	Card* toArray();

	/*deckSize()
	 * takes: nothing
	 * returns: the number of Cards currently in the Deck
	 *
	 */
	int deckSize();

	/*deckCapacity()
	* takes: nothing
	* returns: the number of Cards the Deck may hold
	*
	*/
	int deckCapacity();

	/*resizeDeck(newCapacity)
	 * takes: a new capacity for the Deck
	 * returns: nothing
	 *
	 * This will create a new array for holding Cards and then copy the current
	 * Deck to that.  If the new capacity is smaller than the current capacity,
	 * then Cards will be lost.
	 *
	 */
	void resizeDeck(int newCapacity);

	/*destroy()
	 * takes: nothing
	 * returns: nothing
	 *
	 * This is used to teardown and cleanup the deck prior to destruction.  This
	 * is an explicit dtor used in place of ~Deck().
	 *
	 */
	void destroy();

	//IDrawable implementation
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual int getPriority();
	virtual void setPriority(int);
	virtual void draw();

private:
	int _nCards;
	int _maxCards;
	Card* _cards;
	bool _canDraw;
	int _drawPriority;
	Vector3 _center;
};
#endif