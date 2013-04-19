#ifndef _GAME_H_
#include "game.h"
#endif

#include <iostream>
#include <string>
#include "player.h"
#include "deck.h"
#include "Board.h"
#include "Card.h"
#include "colorscheme.h"

using std::cerr;
using std::endl;

Game* Game::_instance = 0;

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
	_curPlayer = 0;
	_currentSelect = 0;
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
	srand(time(NULL));

	difficulty = (difficulty<1)?1:difficulty;
	difficulty = (difficulty>5)?5:difficulty;
    _cardPairs = difficulty*2;
    loadAndBindTextures();
    
    //create the Board
    int rows = 4, cols = 5;
    _board->init(rows, cols);
	_board->enable(); //allow board to draw
    //init the Deck
    _deck->init(0,0,20); //init the deck with no cards for ease

    //since we didn't add cards in init, add them all here
    int cardTexIdx = 0;
    
    Card* tmpC;
    for(int i=0;i<10;++i)
    {
        tmpC = new Card();
        tmpC->init(Vector2(), _cardFaceTexIds[cardTexIdx], _cardBackTexId);
		tmpC->enable(); //let this card draw
        _deck->placeCardOnDeck(tmpC);
        
        tmpC = new Card();
        tmpC->init(Vector2(), _cardFaceTexIds[cardTexIdx++], _cardBackTexId);
		tmpC->enable(); //let this card draw
        _deck->placeCardOnDeck(tmpC);

		//make sure we aren't adding garbage
		if(cardTexIdx >= _cardPairs)
			cardTexIdx = 0;
    }
    tmpC = 0;
    _deck->shuffleDeck();
    
    //place cards on Board
    for(int r=0;r<rows;++r)
    {
        for(int c=0;c<cols;++c)
            _board->placeCardOnBoard(r, c, _deck->dealCard());
    }
    
	//allow Board to update
	_board->enableUpdates();

    //add Players
    //this will change significantly when we actually add ai
	_curPlayer = 0;
	_players[0] = new Player();
	_players[0]->init(true, ColorScheme::HERZING_WHITE_GRAD);
	_players[0]->name("Player 1");
	_players[0]->enable();

	_players[1] = new Player();
	_players[1]->init(true, ColorScheme::HERZING_GOLD_GRAD);
	_players[1]->name("Player 2");
	_players[1]->disable();
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

Player* Game::getCurrentPlayer() { return _players[_curPlayer]; }
void Game::switchPlayers()
{
	_players[_curPlayer]->disable();
	_curPlayer = (_curPlayer==1)?0:1;
	_players[_curPlayer]->enable();
}

void Game::leftClick()
{
	Card* tmp = _players[_curPlayer]->selectCard();
	if(tmp != 0)
	{
		tmp->flip();
		if(_currentSelect == 0) //first selection
		{
			_currentSelect = tmp;
		}
		else
		{
			if(tmp != _currentSelect) //not the same Card object
			{
				if(*tmp == *_currentSelect)
				{
					tmp->disable();
					_currentSelect->disable();
					_board->removeCardFromBoard(_currentSelect);
					_players[_curPlayer]->addPair(_currentSelect);
					_board->removeCardFromBoard(tmp);
					cerr << _players[_curPlayer]->name() << ": " << _players[_curPlayer]->getPairsFound() << endl;
				}
				_board->putAllCardsFaceDown();
				_currentSelect = 0;
			}
		}
	}
}
void Game::destroy()
{
    _board->destroy();
    _deck->destroy();
    _players[0]->destroy();
    _players[1]->destroy();
	for(int i=0;i<_cardPairs;++i)
		_cardFaceT2D[i]->destroy();
	_cardBackT2D->destroy();
	_boardT2D->destroy();
}

void Game::loadAndBindTextures()
{
	//TODO: code for actually loading textures when we have those.

	//Here's where we load in all of the face textures used in the game.
	//Rather than learn to make an atlas/sprite sheet, we just loop over
	//an array and change the file name each time.
	_cardFaceT2D = new Texture2D*[_cardPairs];
	_cardFaceTexIds = new GLuint[_cardPairs];
	std::string faceBase = ".\\Content\\face";
	std::string ext = ".bmp";
	//we will not have more than 10 card face textures, so we'll take advantage
	//of that here.
	std::string fileNum = "00";
	int faceNum = 1;
	for(int i=0;i<_cardPairs;++i)
	{
		//generate file name
		if(i+1<10)
			fileNum[1] = (char)(i+49);
		else
			fileNum = "10";
		//load texture file
		//_cardFaceT2D[i] = new Texture2D(faceBase+fileNum+ext);
		_cardFaceT2D[i] = new Texture2D(faceBase+fileNum+ext);
		//bind the texture in GL
		glGenTextures(1, &_cardFaceTexIds[i]);
		glBindTexture(GL_TEXTURE_2D, _cardFaceTexIds[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (_cardFaceT2D[i])->width,
						(_cardFaceT2D[i])->height, 0, GL_RGB, GL_UNSIGNED_BYTE,
						(_cardFaceT2D[i])->pixels);
	}

	//This is less looping, but basically the same.  We'll load the back texure
	//of the cards now.
	_cardBackT2D = new Texture2D(".\\Content\\back.bmp");

	//bind the texture in GL
	glGenTextures(1, &_cardBackTexId);
	glBindTexture(GL_TEXTURE_2D, _cardBackTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _cardBackT2D->width,
					_cardBackT2D->height, 0, GL_RGB, GL_UNSIGNED_BYTE,
					_cardBackT2D->pixels);

	//load and bind the board texture, same process
	_boardT2D = new Texture2D(".\\Content\\board.bmp");

	//bind the texture in GL
	glGenTextures(1, &_boardTexId);
	glBindTexture(GL_TEXTURE_2D, _boardTexId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _boardT2D->width,
					_boardT2D->height, 0, GL_RGB, GL_UNSIGNED_BYTE,
					_boardT2D->pixels);
}