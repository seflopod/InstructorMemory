#ifndef CLASS_H
#include "Card.h"
#endif

#include "game.h"
#include "player.h"
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
	_faceColor = Color4();
	_backColor = Color4();
}

void Card::init(Vector2 rowCol, GLuint faceTexId, GLuint backTexId)
{
	_rowCol = rowCol;
	_faceTex = faceTexId;
	_backTex = backTexId;

	//change variables that need changing from default ctor
	_drawPriority = 10;
	_center = Game::instance()->getBoard()->RCtoXY(_rowCol);
	_wPct = 1.0f;
	_flipSpeed = 0.1f;
	_flipping = false;
	Game::instance()->registerDrawable((IDrawable*)this);
	Game::instance()->registerUpdatable((IUpdatable*)this);
	_faceColor = ColorScheme::YELLOW;
	_backColor = ColorScheme::RED;
}

void Card::moveToRC(int row, int col)
{
	_rowCol.x = row;
	_rowCol.y = col;
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

GLuint Card::getFaceTextureId() const { return _faceTex; }
void Card::setFaceTextureId(GLuint faceTex) { _faceTex = faceTex; }
GLuint Card::getBackTextureId() const { return _backTex; }
void Card::setBackTextureId(GLuint backTex) { _backTex = backTex; }

Vector2& Card::getRowCol() { return _rowCol; }

//IUpdatable implementation
void Card::enableUpdates() { _canUpdate = true; }
void Card::disableUpdates() { _canUpdate = false; }
bool Card::canUpdate() { return _canUpdate; }
void Card::update(float dt)
{
	_wPct+=((_flipping)?-1:1)*_flipSpeed;
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
	Color4 myColor;

	if(_showFace)
	{
		glBindTexture(GL_TEXTURE_2D, _faceTex);
		//myColor = _faceColor;
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, _backTex);
		//myColor = _backColor;
	}

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glBegin(GL_QUADS);
		//glColor4fv(myColor.toArray());
		//Need to update the texture coordinates for when we know how
		//they're actually in here.
		glTexCoord2f(0,1);
		glVertex2f(pos.x - _wPct*Board::CARD_WIDTH/2.0f,
					pos.y + Board::CARD_HEIGHT/2.0f);
		glTexCoord2f(0,0);
		glVertex2f(pos.x - _wPct*Board::CARD_WIDTH/2.0f,
					pos.y - Board::CARD_HEIGHT/2.0f);
		glTexCoord2f(1,0);
		glVertex2f(pos.x + _wPct*Board::CARD_WIDTH/2.0f,
					pos.y - Board::CARD_HEIGHT/2.0f);
		glTexCoord2f(1,1);
		glVertex2f(pos.x + _wPct*Board::CARD_WIDTH/2.0f,
					pos.y + Board::CARD_HEIGHT/2.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


//Operator overloads
bool Card::operator==(const Card &rhs)
{
	return (this->_faceTex == rhs.getFaceTextureId() && this->_backTex==rhs.getBackTextureId());
}

bool Card::operator!=(const Card &rhs)
{
	return !(*this==rhs);
}