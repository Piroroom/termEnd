#pragma once
#include "structure.h"
#include "calculate.h"
#include "Setting.h"


#define BUFFLENGTH 128
#define BUFFSIZE 1024

void readFileName(char temp[BUFFLENGTH]);//ÉtÉ@ÉCÉãñºì«Ç›çûÇ›
void CSV2Array(const char *fileName);
