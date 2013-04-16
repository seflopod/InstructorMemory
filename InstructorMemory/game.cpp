#ifndef _GAME_H_
#include "game.h"
#endif

#include "player.h"
#include "deck.h"
#include "Board.h"
#include "Card.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int HBOUND = 800;
const int VBOUND = 600;
const int FPS = 27;

//ctor up here for courtesy, but remember it's private
Game::Game()
{
    _board = new Board();
    _players[0] = new Player();
    _players[1] = new Player();
    _deck = new Deck();
    _cardFaceTexIds = 0;
	_cardBackTexId = 0;
	_boardTexId = 0;
	_playerTexId = 0;
    _drawables = priority_queue<IDrawable*>();
    _updatables = vector<IUpdatable*>();
}

Game* Game::instance()
{
    if(_instance == 0)
        _instance = new Game();
    
    return _instance;
}

void Game::display()
{
    if(instance()->_drawables.size() > 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        //http://www.cplusplus.com/forum/general/26791/
        for(int i=0;i<instance()->_drawables.size();++i)
            (&(instance()->_drawables.top()))[i]->draw();

        glutSwapBuffers();
    }
}

void Game::update(int value)
{
    if(instance()->_updatables.size() > 0)
    {
		instance()->_lastCurrentTime = instance()->_currentTime;
        instance()->_currentTime = clock();
        float dt = difftime(instance()->_currentTime, instance()->_lastCurrentTime);
        
        vector<IUpdatable*>::iterator it;
        vector<IUpdatable*>* u = &(instance()->_updatables);
        for(it=u->begin();it!=u->end();++it)
            (*it)->update(dt);
    }
    glutTimerFunc(FPS, Game::update, 0);
    glutPostRedisplay();
}

//NOTE: no pointer checks are done, this is rather unsafe
void Game::init(int difficulty)
{
    int pairs = difficulty*2;
    loadAndBindTextures(pairs);
    
    //create the Board
    int rows = 4, cols = 5;
    _board->init(rows, cols);

    //init the Deck
    _deck->init(0,0,20); //init the deck with no cards for ease

    //since we didn't add cards in init, add them all here
    int cardTexIdx = 0;
    
    Card* tmpC;
    for(int i=0;i<10;++i)
    {
        tmpC = new Card();
        tmpC->init(Vector2(), _cardFaceTexIds[cardTexIdx], _cardBackTexId);
        _deck->placeCardOnDeck(tmpC);
        
        tmpC = new Card();
        tmpC->init(Vector2(), _cardFaceTexIds[cardTexIdx++], _cardBackTexId);
        _deck->placeCardOnDeck(tmpC);
    }
    tmpC = 0;
    _deck->shuffleDeck();
    
    //place cards on Board
    for(int r=0;r<rows;++r)
    {
        for(int c=0;c<cols;++c)
            _board->placeCardOnBoard(r, c, _deck->dealCard());
    }
    
    //add Players
    //this will change significantly when we actually add ai
    for(int i=0;i<2;++i)
    {
        _players[i]->init(true); //make both human for now.
    }
}

void Game::registerDrawable(IDrawable* newDrawable)
{
    _drawables.push(newDrawable);
}

void Game::registerUpdatable(IUpdatable* newUpdatable)
{
    _updatables.push_back(newUpdatable);
}

Board* Game::getBoard() { return _board; }
Player* Game::getPlayer(int number)
{
    if(number >= 0 && number < 2)
        return _players[number];
    else
        return 0;
}

void Game::destroy()
{
    _board->destroy();
    _deck->destroy();
    _players[0]->destroy();
    _players[1]->destroy();
}

void Game::loadAndBindTextures(int pairs)
{
	//TODO: code for actually loading textures when we have those.
}
