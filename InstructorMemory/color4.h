#ifndef _COLOR4_H_
#define _COLOR4_H_

#include "color3.h"

class Color4 : public Color3
{
public:
	Color4()
		: Color3()
	{
		alpha = 1.0f;
	}

	Color4(float r, float g, float b, float a)
		: Color3(r,g,b)
	{
		alpha = a;
	}

	float alpha;

	virtual float* toArray()
	{
		float ret[] = {red, green, blue, alpha};
		return ret;
	}
};

#endif