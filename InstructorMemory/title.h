/*title.h
 * Peter Bartosch and Ross Greenman
 * created:
 * last modified: 4/23/2013
 * IS34? - Instructor Memory
 * Kahn
 *
 */
#ifndef _TITLE_H_
#define _TITLE_H_

#include <GL/freeglut.h>
#include <string>
#include "idrawable.h"

using std::string;

class TitleButton;

class Title : public IDrawable
{
public:
	Title();

	void init(GLuint bgTexture);

	void setMode(int mode);
	int getMode();

	void enableButtons();
	void disableButtons();

	void procClick(float x, float y);

	//IDrawable implementation
	virtual void enable();
	virtual void disable();
	virtual bool isEnabled();
	virtual int getPriority();
	virtual void setPriority(int);
	virtual void draw();
private:
	TitleButton** _msgButtons;

	bool _canDraw;
	int _drawPriority;
	GLuint _texId;
	int _mode;
};
#endif