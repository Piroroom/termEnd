#pragma once
#include "structure.h"
#include "calculate.h"
#include "Setting.h"


#define BUFFLENGTH 128
#define BUFFSIZE 1024

void readFileName(char temp[BUFFLENGTH]);//ファイル名読み込み
void CSV2Array(const char *fileName);
