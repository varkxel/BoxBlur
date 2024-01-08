#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <StringHandling.h>

#include "Image.h"
#include "Blur.h"

int main(int argc, char** argv)
{
	// Get thread count
	long threads = 1;
	if(argc >= 2)
	{
		bool success = ArgToLong(argv[1], &threads);
		if(threads <= 0 || !success)
		{
			fprintf(stderr, "Thread count \"%li\" is not valid, setting to default value.\n", threads);
			threads = 1;
		}
	}
	
	// Get the path to the file
	char* path;
	if(argc >= 3) ConcatString((const char**) &argv[1], argc - 1, &path);
	else path = PromptStringRepeat("Enter path to image: ");
	
	unsigned int width, height;
	byte* source = LoadImage(path, &width, &height, NULL);
	
	Pixel* result = malloc(width * height * sizeof(Pixel));
	BoxBlur(source, width, height, result, (unsigned int) threads);
	free(source);
	
	char outPath[256];
	snprintf(outPath, 256, "%s_blurred.png", path);
	WriteImage(outPath, (const byte*) result, width, height);
	free(result);
}
