/*game.h
 * Peter Bartosch and Ross Greenman
 * created: 4/13/2013
 * last updated: 4/15/2013
 * IS346 - InstructorMemory
 * Kahn
 *
 * defines class: Game
 * Game is a singleton that holds all information for running the game.  It
 * contains static methods for registering both display and update.
 * It does other things too, trust me.
 *
 */
#ifndef _GAME_H_
#define _GAME_H_

//forward declarations to avoid compiler issues
class Board;
class Deck;
class Card;
class Player;

class Game
{
public:
	static Game* instance();

	Board* getBoard();
};
#endif