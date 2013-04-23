#ifndef _TITLEBUTTON_H_
#define _TITLEBUTTON_H_

#include <GL/freeglut.h>
#include <string>
#include "idrawable.h"
#include "vector3.h"

using std::string;

class TitleButton : public IDrawable
{
public:
	TitleButton();

	void init(string text, Vector3 position, float height, float width);

	Vector3 getPosition();
	void setPosition(Vector3 newPosition);

	float getHeight();
	void setHeight(float height);

	float getWidth();
	void setWidth(float width);

	bool collidesWithPoint(float x, float y);

	//IDrawable implementation
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual int getPriority();
	virtual void setPriority(int);
	virtual void draw();
private:
	bool _canDraw;
	int _drawPriority;
	//GLuint _texId;
	string _text;
	Vector3 _position;
	float _height;
	float _width;
};
#endif