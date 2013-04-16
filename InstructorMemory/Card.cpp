#ifndef CLASS_H
#include "Card.h"
#endif

#include "game.h"
#include "board.h"

Card::Card()
{
	_rowCol = Vector2();
	_canDraw = false;
	_drawPriority = -1;
	_center = Vector3();
	_showFace = false;
	_faceTex = -1; //this should be a very high unsigned int.
	_backTex = -1;
	_canUpdate = false;
	_wPct = 0.0f;
	_flipSpeed = 0.0f;
	_flipping = false;
}

void Card::init(Vector2 rowCol, GLuint faceTexId, GLuint backTexId)
{
	_rowCol = rowCol;
	_faceTex = faceTexId;
	_backTex = backTexId;

	//change variables that need changing from default ctor
	_drawPriority = 5;
	_center = Game::instance()->getBoard()->RCtoXY(_rowCol);
	_wPct = 1.0f;
	_flipSpeed = 0.1f;
	_flipping = false;
	Game::instance()->registerDrawable((IDrawable*)this);
	Game::instance()->registerUpdatable((IUpdatable*)this);
}

bool Card::collideWithCard(Vector3 position)
{
	Vector3 pos = Game::instance()->getBoard()->RCtoXY(_rowCol);
	float left = pos.x - Game::instance()->getBoard()->CARD_WIDTH;
	float right = pos.x + Game::instance()->getBoard()->CARD_WIDTH;
	float top = pos.y + Game::instance()->getBoard()->CARD_HEIGHT;
	float bottom = pos.y - Game::instance()->getBoard()->CARD_HEIGHT;

	return (position.x >= left && position.x <= right &&
			position.y >= bottom && position.y <= top);
}

bool Card::faceUp() { return _showFace; }

void Card::flip()
{
	_canUpdate = true;
	_flipping = true;
}

GLuint Card::getFaceTextureId() { return _faceTex; }
void Card::setFaceTextureId(GLuint faceTex) { _faceTex = faceTex; }
GLuint Card::getBackTextureId() { return _backTex; }
void Card::setBackTextureId(GLuint backTex) { _backTex = backTex; }

//IUpdatable implementation
void Card::enableUpdates() { _canUpdate = true; }
void Card::disableUpdates() { _canUpdate = false; }
bool Card::canUpdate() { return _canUpdate; }
void Card::update(float dt)
{
	_wPct+=((_flipping)-1:1)*_flipSpeed;
	if(_flipping && _wPct <= 0)
	{
		_wPct = 0.0f;
		_flipping = false;
		_showFace = !_showFace;
	}
	else if(!_flipping && _wPct >= 1.0f)
	{
		_wPct = 1.0f;
		_canUpdate = false;
	}
}

//IDrawable implementation
void Card::enable() { _canDraw = true; }
void Card::disable() { _canDraw = false; }
bool Card::isEnabled() { return _canDraw; }
int Card::getPriority() { return _drawPriority; }
void Card::setPriority(int newPriority) { _drawPriority = newPriority; }

void Card::draw()
{
	if(!_canDraw)
		return;

	Vector3 pos = Game::instance()->getBoard()->RCtoXY(_rowCol);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _backTex);
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glBegin(GL_QUADS);
		//Need to update the texture coordinates for when we know how
		//they're actuall in here.
		glTexCoord2f(0,1);
		glVertex2f(pos.x - Game::instance()->getBoard()->CARD_WIDTH,
					pos.y + Game::instance()->getBoard()->CARD_HEIGHT);
		glTexCoord2f(0,0);
		glVertex2f(pos.x - Game::instance()->getBoard()->CARD_WIDTH,
					pos.y - Game::instance()->getBoard()->CARD_HEIGHT);
		glTexCoord2f(1,0);
		glVertex2f(pos.x + Game::instance()->getBoard()->CARD_WIDTH,
					pos.y - Game::instance()->getBoard()->CARD_HEIGHT);
		glTexCoord2f(1,1);
		glVertex2f(pos.x + Game::instance()->getBoard()->CARD_WIDTH,
					pos.y + Game::instance()->getBoard()->CARD_HEIGHT);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}