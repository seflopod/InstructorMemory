#ifndef TEXTURE2D_H
#include "Texture2D.h"
#endif

#include <Windows.h>
#include <stdio.h>

Texture2D::Texture2D()
{
	width = 0;
	height = 0;
	pixels = 0;
}

Texture2D::Texture2D(string fn)
{
	try
	{
		FILE* file = fopen(fn.c_str(), "rb");
		BITMAPFILEHEADER bmpH;
		fread(&bmpH, sizeof(BITMAPFILEHEADER), 1, file);

		BITMAPINFOHEADER dibH;
		fread(&dibH, sizeof(BITMAPINFOHEADER), 1, file);

		int size = bmpH.bfSize - bmpH.bfOffBits;
		BYTE* tempPixelData = new BYTE[size];
		if(tempPixelData == NULL)
		{
			fclose(file);
			throw exception("No Data in Pixels");
		}
		else
			fread(tempPixelData, sizeof(BYTE), size, file);

		width = dibH.biWidth;
		height = dibH.biHeight;
		pixels = new BYTE[size];

		//pixel data was reversed, need to flip
		int pos = 0;
		while(pos + 3 < size)
		{
			swap(tempPixelData[pos], tempPixelData[pos + 2]);
			pos += 3;
		}

		memcpy(pixels, tempPixelData, sizeof(BYTE) * size); 

		delete[] tempPixelData;

		fclose(file);
	}
	catch(...)
	{
		cerr << "Couldn't Open File" << endl;
	}
}


void Texture2D::destroy()
{
	delete[] pixels;
}