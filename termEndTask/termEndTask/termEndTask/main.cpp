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
	readFileName(FileName);//�t�@�C�����ǂݍ���
	CSV2Array(FileName);//�t�@�C���ǂݍ���

	outPutFile();

	//�O���t�`�擙
	putNcurses();
	

    return 0;
}


	

	