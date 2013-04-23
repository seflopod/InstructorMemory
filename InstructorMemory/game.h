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
class Title;

class Game
{
public:
	
	enum GameState
	{
		TitleState = 0x01,
		Playing = 0x02,
		GameOver = 0x04
	};

	static const int WINDOW_WIDTH = 1280;
	static const int WINDOW_HEIGHT = 880;
	static const int HBOUND = 1280;
	static const int VBOUND = 880;
	static const int FPS = 27;
	
	static Game* instance();
	static void display();
	static void update(int value);
	static GameState state();
	static void state(GameState newState);

	void init();
	void registerDrawable(IDrawable* newDrawable);
	void registerUpdatable(IUpdatable* newUpdatable);
	Board* getBoard();

	int getNumberOfHumans();
	void setNumberOfHumans(int nHumans);
	Player* getPlayer(int number);
	Player* getCurrentPlayer();
	void switchPlayers();

	int getDifficulty();
	void setDifficulty(int difficulty);

	
	void leftClick(float x, float y);
	
	void destroy();
private:
	static Game* _instance;

	Game();
	
	void titleInit();
	void playingInit();

	void loadAndBindTextures();
	void titleLeftClick(float x, float y);
	void playingLeftClick(float x, float y);

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
	Texture2D* _titleT2D;
	GLuint* _cardFaceTexIds;
	GLuint _cardBackTexId;
	GLuint _boardTexId;
	GLuint _playerTexId;
	GLuint _titleTexId;
	
	Board* _board;
	Player* _players[2];
	Deck* _deck;
	
	int _curPlayer;
	Card* _currentSelect;

	GameState _state;
	Title* _title;
	int _difficulty;
	int _nHumans;
};
#endif
