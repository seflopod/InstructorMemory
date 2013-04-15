/*color3.h
 * Peter Bartosch
 * created: 4/10/2013
 * last modified: 4/15/2013
 *
 * defines class: Color3
 * Color3 is a class for representing an RGB color.  It defines methods for
 * turning itself into a float array as well as equality operators.  Its
 * variables are all public.
 *
 */
#ifndef _COLOR3_H_
#define _COLOR3_H_

class Color3
{
public:
	float red;
	float green;
	float blue;
	
	Color3()
	{
		red = 0;
		green = 0;
		blue = 0;
	}
	
	Color3(float r, float g, float b)
	{
		red = r;
		green = g;
		blue = b;
	}
	
	virtual float* toArray()
	{
		float ret[3] = {red, green, blue};
		return ret;
	}

	bool operator==(const Color3 &other) const
	{
		return (red==other.red && green == other.green && blue == other.blue);
	}

	bool operator!=(const Color3 &other) const
	{
		return !(*this==other);
	}
};
#endif