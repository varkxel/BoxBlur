#include "Include/StringHandling.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

bool ArgToLong64(const char* arg, long long* out)
{
	// Cast to long long
	char* end;
	*out = strtoll(arg, &end, 10);
	
	// End pointer will be different if successful
	return end != arg;
}

bool ArgToLong(const char* arg, long* out)
{
	// Cast to double
	char* end;
	*out = strtol(arg, &end, 10);
	
	// End pointer will be different if successful
	return end != arg;
}

size_t ConcatString(const char** strings, const int count, char** outString)
{
	// Get new string length
	size_t length = 0;
	for(int i = 0; i < count; i++)
	{
		length += strlen(strings[i]) + 1;
	}
	length--;
	
	// Allocate new string
	*outString = malloc((length + 1) * sizeof(char));
	char* out = *outString;
	
	// Copy to new string
	size_t outIndex = 0;
	for(int i = 0; i < count; i++)
	{
		char currentChar;
		size_t strIndex = 0;
		
		// Copy while not end of string
		while((currentChar = strings[i][strIndex]) != '\0')
		{
			out[outIndex++] = currentChar;
			strIndex++;
		}
		
		// If hit end of string, replace null terminator with space.
		out[outIndex++] = ' ';
	}
	
	// Null terminate new string.
	out[length] = '\0';
	
	return length;
}

bool PromptString_Buffer(const char* prompt, char** result, const size_t bufferSize)
{
	// Allocate buffer
	*result = malloc(bufferSize);
	
	// Get string
	printf("%s", prompt);
	if(fgets(*result, (int) bufferSize, stdin) == NULL) return false;
	
	// Clean up input
	for(int i = 0; i < bufferSize; i++)
	{
		switch((*result)[i])
		{
			default: break;
			case '\n': (*result)[i] = '\0';
			case '\0': goto PromptString_EndCleanup;
		}
	}
	PromptString_EndCleanup: {};
	
	return true;
}

bool PromptString(const char* prompt, char** result)
{
	return PromptString_Buffer(prompt, result, 256);
}

char* PromptStringRepeat(const char* prompt)
{
	bool success = false;
	
	char* buffer = NULL;
	while(!success)
	{
		// Error check
		if(buffer != NULL)
		{
			fprintf(stderr, "Invalid path \"%s\".\n", buffer);
			free(buffer);
		}
		
		// Get string
		success = PromptString(prompt, &buffer);
		success &= access(buffer, F_OK) == 0;
	}
	
	return buffer;
}
