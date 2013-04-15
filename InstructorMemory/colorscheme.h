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

class Color3;

class ColorScheme
{
public:
	static const Color3 WHITE;
	static const Color3 BLACK;
};
#endif