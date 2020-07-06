#pragma once
#define BUFFLENGTH 128

int readInt(const char *secton, const char *keyword, int defaultValue, const char *flePath);
bool readChar(const char *secton, const char *keyword, const char *defaultValue, char *returnValue, const char *flePath);
double readDouble(const char *secton, const char *keyword, double defaultValue, const char *flePath);
void getCurrentDirectory(char *currentDirectory);
bool writeChar(const char *secton, const char *keyword, const char *returnValue, const char *flePath);
bool writeInt(const char *secton, const char *keyword, int returnValue, const char *flePath);
bool writeDouble(const char *secton, const char *keyword, double returnValue, const char *flePath);
