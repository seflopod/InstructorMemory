#ifndef _GAME_H_
#include "game.h"
#endif

#include "player.h"
#include "deck.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int HBOUND = 800;
const int VBOUND = 600;
const int FPS = 27;

//ctor up here for courtesy, but remember it's private
Game::Game()
{
    _board = Board();
    _players[0] = Player();
    _players[1] = Player();
    _deck = Deck();
    _cardTexIds = 0;
    _drawables = priority_queue<IDrawable*>();
    _updatables = priority_queue<IUpdtable*>();
}

Game* Game::instance()
{
    if(_instance == 0)
        _instance = new Game();
    
    return _instance;
}

void Game::display()
{
    if(_drawables.size() > 0)
    {
        //access _instance through instance to make sure an instance exists
        //loop over _drawables
        //need to determine if I can use the underlying vector's [] function, otherwise
        //need to pop all eleemtns and then recreate pq
    }
}

void Game::update(int value)
{
    if(_updatables.size() > 0)
    {
        float dt = 0.05f;
        //actually calc dt
        vector<IUpdatable*>::iterator it;
        vector<Iupdatable*>* u = instance()->_updtables;
        for(it=u->begin();it!=u->end();;++it)
            it->update(dt);
    }
    glutTimerFunc(FPS, Game::update, 0);
    glutPostRedisplay();
}

void Game::init(int difficulty)
{
    int pairs = difficulty*2;
    loadAndBindTextures(pairs);
    
    //create the Board
    int rows = 4, cols = 5;
    _board = Board();
    _board.init(rows, cols);

    //create the Deck
    _deck = Deck();
    _deck.init(0,0,20); //init the deck with no cards for ease
    //since we didn't add cards in init, add them all here
    int cardTexIdx = 0;
    
    Card* tmpC;
    for(int i=0;i<10;++i)
    {
        tmpC = new Card();
        tmpC->init(Vector2(), _cardTexIds[cardTexIdx], _cardBackTexId);
        _deck.placeCardOnDeck(tmpC);
        
        tmpC = new Card();
        tmpC->init(Vector2(), _cardTexIds[cardTexIdx++], _cardBackTexId);
        _deck.placeCardOnDeck(tmpC);
    }
    tmpC = 0;
    _deck.shuffle();
    
    //place cards on Board
    for(int r=0;r<rows;++r)
    {
        for(int c=0;c<cols;++c)
            _board.placeCardOnBoard(r, c, _deck.dealCard());
    }
    
    //add Players
    //this will change significantly when we actually add ai
    _players[0] = Player();
    _players[1] = Player();
    for(int i=0;i<2;++i)
    {
        _players[i].init(true); //make both human for now.
    }
}

void Game::registerDrawable(IDrawable* newDrawable)
{
    _drawables.push(newDrawable);
}

void Gaem::registerUpdatable(IUpdatable* newUpdatable)
{
    _updatables.push_back(newUpdatable);
}

Board* Game::getBoard() { return &_board; }
Player* Game::getPlayer(int number)
{
    if(number >= 0 && number < 2)
        return &_players[number];
    else
        return 0;
}

void Game::destroy()
{
    _board.destroy();
    _deck.destroy();
    _players[0].destroy();
    _players[1].destroy();
}
