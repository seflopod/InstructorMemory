/*player.h
 * Peter Bartosch and Ross Greenman
 * created: 4/15/2013
 * last modified: 4/15/2013
 *
 * defines class: Player
 * The Player class defines methods and variables used by users interacting with
 * the game.  It has a Deck for holding a Card for each pair the Player finds,
 * a name, and a flag for the Player's humanity.  The Player can select a Card
 * that is drawn, this is done via the Player's position (the mouse position).
 * The Player implements IDrawable.
 *
 * NOTE: It may be better to have an AIPlayer class that inherits from this one
 * rather than adding it in to Player.
 *
 * TODO: Add varaibles and methods for texture/color for drawing.
 *
 */
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include "idrawable.h"
#include "vector3.h"

using std::string;

//Forward declaration of associated classes
class Deck;
class Card;

class Player : public IDrawable
{
public:
	/*Player()
	 * takes: nothing
	 * returns: nothing
	 *
	 * Default ctor for Player.  This will init all variables to NULL or its
	 * equivilent.
	 *
	 */
	Player();

	/*init(isHuman)
	 * takes: true if the Player is human; false otherwise
	 * returns: nothing
	 *
	 * This will initialize the Player with the humanity flag and any other
	 * needed inits.
	 *
	 */
	void init(bool isHuman);

	/*getPairsFound()
	 * takes: nothing
	 * returns: the number of pairs the Player has found.
	 *
	 */
	int getPairsFound();

	/*getPairsDeck()
	 * takes: nothing
	 * returns: the Deck made up of the pairs the Player has found
	 *
	 */
	Deck* getPairsDeck();

	/*addPair(card)
	 * takes: a pointer to a Card representing the pair the Player has found
	 * returns: nothing
	 *
	 * Notice how this takes a pointer.  It might be best to go back and edit
	 * Deck to use pointers as well.
	 *
	 */
	void addPair(Card* card);

	/*isHuman()
	 * takes: nothing
	 * returns: true if the Player is human; false otherwise.
	 *
	 */
	bool isHuman();

	/*name()
	 * takes: nothing
	 * returns: a string of the Player's name
	 *
	 */
	string name();

	/*name(newName)
	 * takes: a string representing the Player's new name.
	 * returns: nothing
	 *
	 */
	void name(string newName);

	/*selectCard(position)
	 * takes: a Vector3 for the position the Player is selecting a card from.
	 * returns: a pointer to the selected Card.
	 *
	 * If no Card exists at the passed position, NULL is returned.
	 *
	 */
	Card* selectCard();

	void moveTo(float x, float y);

	/*destroy()
	 * takes: nothing
	 * returns: nothing
	 *
	 * This is used to teardown and cleanup the Player prior to destruction.
	 * This is an explicit dtor used in place of ~Player().
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
	bool _human;
	string _name;
	Deck* _pairsDeck;
	int _pairsFound;
	bool _canDraw;
	int _drawPriority;
	Vector3 _center;
	Color4 _color;
};
#endif