#include "Blur.h"

#include <stdlib.h>

#include <pthread.h>
#include <unistd.h>

struct ThreadContext
{
	unsigned int threadCount, threadNumber;
	
	const byte* source;
	unsigned width;
	unsigned height;
	
	Pixel* result;
};

Pixel BlurPixel(const int x, const int y, const struct ThreadContext* context)
{
	unsigned int boxPixelCount = 0;
	unsigned int rTotal = 0, gTotal = 0, bTotal = 0, aTotal = 0;
	
	for(int yOffset = -1; yOffset <= 1; yOffset++)
	{
		const int pixelY = y + yOffset;
		
		// Check Y bounds, for performance this should be moved out of the loop in the future.
		if(pixelY < 0 || pixelY >= context->height) continue;
		
		for(int xOffset = -1; xOffset <= 1; xOffset++)
		{
			const int pixelX = x + xOffset;
			
			// Check X bounds, for performance this should be moved out of the loop in the future.
			if(pixelX < 0 || pixelX >= context->width) continue;
			
			const Pixel* boxPixel = (const Pixel*) &context->source[(x + (y * context->width)) * sizeof(Pixel)];
			rTotal += boxPixel->r;
			gTotal += boxPixel->g;
			bTotal += boxPixel->b;
			aTotal += boxPixel->a;
			
			boxPixelCount++;
		}
	}
	
	return (Pixel)
	{
		.r = rTotal / boxPixelCount,
		.g = gTotal / boxPixelCount,
		.b = bTotal / boxPixelCount,
		.a = aTotal / boxPixelCount
	};
}

volatile int activeThreads = 0;
pthread_mutex_t activeThreadsMutex = PTHREAD_MUTEX_INITIALIZER;

void* Thread(void* args)
{
	struct ThreadContext* context = (struct ThreadContext*) args;
	
	// Have each thread do a horizontal line
	for(int y = (signed) context->threadNumber; (unsigned) y < context->height; y += (signed) context->threadCount)
	{
		for(int x = 0; (unsigned) x < context->width; x++)
		{
			context->result[x + (y * context->width)] = BlurPixel(x, y, context);
		}
	}
	
	// Remove this thread as it's complete
	pthread_mutex_lock(&activeThreadsMutex);
	activeThreads--;
	pthread_mutex_unlock(&activeThreadsMutex);
	
	// Exit
	pthread_exit(NULL);
}

void BoxBlur(const byte* image, const unsigned width, const unsigned height, Pixel* result, const unsigned threadCount)
{
	const int initialThreads = activeThreads;
	
	pthread_t* threads = malloc(threadCount * sizeof(pthread_t));
	struct ThreadContext* contexts = malloc(threadCount * sizeof(struct ThreadContext));
	
	for(unsigned i = 0; i < threadCount; i++)
	{
		// Add to thread total
		pthread_mutex_lock(&activeThreadsMutex);
		activeThreads++;
		pthread_mutex_unlock(&activeThreadsMutex);
		
		// Initialise context data
		contexts[i].threadCount = threadCount;
		contexts[i].threadNumber = i;
		
		contexts[i].source = image;
		contexts[i].result = result;
		
		contexts[i].width = width;
		contexts[i].height = height;
		
		// Create thread
		pthread_create(&threads[i], NULL, Thread, &contexts[i]);
	}
	
	// Join all the threads.
	while(activeThreads > initialThreads) sleep(1);
	
	// Free thread array & context since all are complete.
	free(threads);
	free(contexts);
}
