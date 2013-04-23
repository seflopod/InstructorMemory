#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include "idrawable.h"

class Scoreboard : public IDrawable
{
public:
	Scoreboard();

	void init();

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
};
#endif