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
#include "idrawablecompare.h"
#include "iupdatable.h"
#include "Texture2D.h"

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
	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 1000;
	static const int HBOUND = 1280;
	static const int VBOUND = 1000;
	static const int FPS = 27;
	
	static Game* instance();
	static void display();
	static void update(int value);

	void init(int difficulty);
	void registerDrawable(IDrawable* newDrawable);
	void registerUpdatable(IUpdatable* newUpdatable);
	Board* getBoard();
	Player* getPlayer(int number);
	Player* getCurrentPlayer();
	void switchPlayers();
	void leftClick();
	
	void destroy();
private:
	static Game* _instance;

	Game();
	
	void loadAndBindTextures();
	//use this for when we can actually prompt for user info
	//void createPlayers();
	clock_t _currentTime;
	clock_t _lastCurrentTime;
	
	priority_queue<IDrawable*, vector<IDrawable*>, IDrawableCompare> _drawables;
	vector<IUpdatable*> _updatables;

	int _cardPairs;
	Texture2D** _cardFaceT2D;
	Texture2D* _cardBackT2D;
	Texture2D* _boardT2D;
	GLuint* _cardFaceTexIds;
	GLuint _cardBackTexId;
	GLuint _boardTexId;
	GLuint _playerTexId;
	
	Board* _board;
	Player* _players[2];
	Deck* _deck;
	
	int _curPlayer;
	Card* _currentSelect;
};
#endif
