#ifndef _TITLEBUTTON_H_
#include "titlebutton.h"
#endif

#include "game.h"

TitleButton::TitleButton()
{
	_canDraw = false;
	_drawPriority = 0;
	//_texId = -1;
	_text = "";
	_position = Vector3();
	_height = 0.0f;
	_width = 0.0f;
}

void TitleButton::init(string text, Vector3 position, float height, float width)
{
	_text = text;
	_position = position;
	_height = height;
	_width = width;
	_drawPriority = 12;
	Game::instance()->registerDrawable((IDrawable*)this);
}

Vector3 TitleButton::getPosition() { return _position; }
void TitleButton::setPosition(Vector3 newPosition) { _position = newPosition; }

float TitleButton::getHeight() { return _height; }
void TitleButton::setHeight(float height) { _height = height; } //note no check for positive

float TitleButton::getWidth() { return _width; }
void TitleButton::setWidth(float width) { _width = width; }

bool TitleButton::collidesWithPoint(float x, float y)
{
	float left = _position.x - _width;
	float right = _position.x + _width;
	float top = _position.y + _height;
	float bottom = _position.y - _height;

	return (x >= left && x <= right &&
			y >= bottom && y <= top);
}

void TitleButton::enable() { _canDraw = true; }
void TitleButton::disable() { _canDraw = false; }
bool TitleButton::isEnabled() { return _canDraw; }
int TitleButton::getPriority() { return _drawPriority; }
void TitleButton::setPriority(int drawPriority) { _drawPriority = drawPriority; }

void TitleButton::draw()
{
	if(!_canDraw)
		return;

	glRasterPos2f(_position.x, _position.y);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)_text.c_str());
}