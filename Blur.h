#ifndef BOXBLUR_BLUR_H
#define BOXBLUR_BLUR_H

#include "Image.h"

typedef struct
{
	byte r, g, b, a;
}
Pixel;

void BoxBlur(const byte* image, unsigned width, unsigned height, Pixel* result, unsigned threadCount);

#endif