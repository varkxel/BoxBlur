#ifndef BOXBLUR_STRINGHANDLING_H
#define BOXBLUR_STRINGHANDLING_H

#include <stdbool.h>
#include <stddef.h>

bool ArgToLong64(const char* arg, long long* out);
bool ArgToLong(const char* arg, long* out);

size_t ConcatString(const char** strings, int count, char** outString);

bool PromptString_Buffer(const char* prompt, char** result, size_t bufferSize);
bool PromptString(const char* prompt, char** result);
char* PromptStringRepeat(const char* prompt);

#endif