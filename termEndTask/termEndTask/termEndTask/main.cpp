#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "structure.h"
#include "calculate.h"
#include "Setting.h"
#include "readFile.h"
#include "drawDisplay.h"
#include "outPut.h"


int main()
{
	char FileName[BUFFLENGTH] = "inputFileName";
	readFileName(FileName);//ファイル名読み込み
	CSV2Array(FileName);//ファイル読み込み

	outPutFile();

	//グラフ描画等
	putNcurses();
	

    return 0;
}


	

	