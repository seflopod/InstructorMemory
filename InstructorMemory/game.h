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

#include <vector>
#include "idrawable.h"
#include "iupdatable.h"

using std::vector;

//forward declarations to avoid compiler issues
class Board;
class Deck;
class Card;
class Player;

class Game
{
public:
	static Game* instance();
	static void display();
	static void update(int value);

	void init();

	Board* getBoard();

	void destroy();
private:
	static Game* _instance;

	Game();

	Board _board;
	Player _players[2];
	Deck _deck;
	Card** 
};
#endif