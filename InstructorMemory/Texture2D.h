#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

class Texture2D
{
public:
	int width;
	int height;
	BYTE* pixels;

	Texture2D();
	Texture2D(string fn);
	void destroy();
};

#endif