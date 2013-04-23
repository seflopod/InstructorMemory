#ifndef _TITLE_H_
#include "title.h"
#endif

#include "titlebutton.h"
#include "game.h"

Title::Title()
{
	_canDraw = false;
	_drawPriority = 0;
	_texId = -1;
	_mode = 0;
	_msgButtons = 0;
}

void Title::init(GLuint bgTexture)
{
	const string MSG_TABLE[2][3] = {
		{ "1 Player", "2 Players", "Exit" },
		{ "Easy", "Not so easy", "Back" }
	};

	_texId = bgTexture;
	_msgButtons = new TitleButton*[6];
	_drawPriority = 10;
	for(int i=0;i<2;++i)
	{
		for(int j=0;j<3;++j)
		{
			_msgButtons[3*i+j] = new TitleButton();
			_msgButtons[3*i+j]->init(MSG_TABLE[i][j], Vector3(595, 300-j*100, 0), 50, 225);
		}
	}
	Game::instance()->registerDrawable((IDrawable*)this);
}

int Title::getMode() { return _mode; }
void Title::setMode(int mode)
{
	if(mode < 0) mode = 0;
	if(mode > 1) mode = 1;
	disableButtons();
	_mode = mode;
	enableButtons();
}

void Title::enableButtons()
{
	for(int i=0;i<3;++i)
		_msgButtons[3*_mode+i]->enable();
}

void Title::disableButtons()
{
	for(int i=0;i<3;++i)
		_msgButtons[3*_mode+i]->disable();
}

void Title::procClick(float x, float y)
{
	int hit = -1;
	for(int i=0;i<3;++i)
	{
		if(_msgButtons[3*_mode+i]->collidesWithPoint(x, y))
		{
			hit = i;
			break;
		}
	}

	switch(_mode)
	{
	case 0:
		{
			switch(hit)
			{
			case 0:
				Game::instance()->setNumberOfHumans(1);
				setMode(1);
				break;
			case 1:
				Game::instance()->setNumberOfHumans(2);
				setMode(1);
				break;
			case 2: glutLeaveMainLoop(); break;
			default: break;
			}
			break;
		}
	case 1:
		{
			switch(hit)
			{
			case 0:
				Game::instance()->setDifficulty(2);
				Game::state(Game::GameState::Playing);
				disable();
				break;
			case 1:
				Game::instance()->setDifficulty(5);
				Game::state(Game::GameState::Playing);
				disable();
				break;
			case 2:
				setMode(0);
				break;
			default: break;
			}
			break;
		}
	default:
		break;
	}

}

void Title::enable()
{
	_canDraw = true;
	setMode(0);
}

void Title::disable()
{
	_canDraw = false;
	disableButtons();
}

bool Title::isEnabled() { return _canDraw; }
int Title::getPriority() { return _drawPriority; }
void Title::setPriority(int drawPriority) { _drawPriority = drawPriority; }

void Title::draw()
{
	if(!_canDraw)
		return;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _texId);
	
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glBegin(GL_QUADS);
		//glColor4fv(myColor.toArray());
		
		glTexCoord2f(0,1);
		glVertex2f(0, Game::VBOUND);
		glTexCoord2f(0,0);
		glVertex2f(0,0);
		glTexCoord2f(1,0);
		glVertex2f(Game::HBOUND, 0);
		glTexCoord2f(1,1);
		glVertex2f(Game::HBOUND, Game::VBOUND);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}