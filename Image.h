#ifndef BOXBLUR_IMAGE_H
#define BOXBLUR_IMAGE_H

typedef unsigned char byte;

byte* LoadImage(const char* path, unsigned* width, unsigned* height, unsigned* error);
unsigned WriteImage(const char* path, const byte* image, unsigned width, unsigned height);

#endif