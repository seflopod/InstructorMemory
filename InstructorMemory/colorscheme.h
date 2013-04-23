/*colorscheme.h
 * Peter Bartosch
 * created: 4/10/2013
 * last modified: 4/15/2013
 *
 * defines class: ColorScheme
 * ColorScheme is used to define a set of Color3s for use as static constants.
 * No methods are used, this is only a way collecting the colors used throughout
 * the project.
 *
 */
#ifndef _COLORSCHEME_H_
#define _COLORSCHEME_H_

class Color4;

class ColorScheme
{
public:
	static const Color4 WHITE;
	static const Color4 BLACK;
	static const Color4 BLUE_BALLS;
	static const Color4 GREEN;
	static const Color4 RED;
	static const Color4 YELLOW;
	static const Color4 HERZING_GOLD_GRAD[2];
	static const Color4 HERZING_WHITE_GRAD[2];
};
#endif