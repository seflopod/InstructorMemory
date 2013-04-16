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
#include <queue>
#include <time.h>
#include "idrawable.h"
#include "iupdatable.h"

using std::vector;
using std::priority_queue;

//forward declarations to avoid compiler issues
class Board;
class Deck;
class Card;
class Player;

class Game
{
public:
	static const int WINDOW_WIDTH;
	static const int WINDOW_HEIGHT;
	static const int HBOUND;
	static const int VBOUND;
	static const int FPS;
	
	static Game* instance();
	static void display();
	static void update(int value);

	void init(int difficulty);
	void registerDrawable(IDrawable* newDrawable);
	void registerUpdatable(IUpdatable* newUpdatable);
	Board* getBoard();
	Player* getPlayer(int number);

	
	void destroy();
private:
	static Game* _instance;

	Game();
	
	void loadAndBindTextures(int pairs);
	//use this for when we can actually prompt for user info
	//void createPlayers();
	clock_t _currentTime;
	clock_t _lastCurrentTime;
	
	priority_queue<IDrawable*> _drawables;
	vector<IUpdatable*> _updatables;
	GLuint* _cardFaceTexIds;
	GLuint _cardBackTexId;
	GLuint _boardTexId;
	GLuint _playerTexId;
	
	Board* _board;
	Player* _players[2];
	Deck* _deck;
};
#endif
