#include "Image.h"

#include <lodepng.h>

byte* LoadImage(const char* path, unsigned* width, unsigned* height, unsigned* error)
{
	byte* image;
	
	unsigned errorNum = lodepng_decode32_file(&image, width, height, path);
	if(error != NULL) *error = errorNum;
	
	return image;
}

unsigned WriteImage(const char* path, const byte* image, const unsigned width, const unsigned height)
{
	return lodepng_encode32_file(path, image, width, height);
}
