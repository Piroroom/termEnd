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


int main()
{
	char FileName[BUFFLENGTH] = "inputFileName";
	readFileName(FileName);//ファイル名読み込み
	CSV2Array(FileName);//ファイル読み込み


	errno_t error;
	FILE *fp;
	char outPut[BUFFSIZE] = "outputFileName";
	readFileName(outPut);//出力ファイル名読み込み


	error = fopen_s(&fp, outPut, "w");

	if (error != 0) {
		fprintf_s(stderr, "failed toopen");
	}
	else {
		while (previousYear != NULL) {
			sprintf_s(outPut, "%d,%d月\n", previousYear->year, previousYear->maxDiffMonth->month);
			fputs(outPut, fp);
			if (previousYear->isEnd == 1) {
				break;
			}
			previousYear = previousYear->nextYear;
		}
		//ポインタを最初のデータにセット
		if (firstYear != NULL) {
			previousYear = firstYear;
			previousMon = previousYear->firstMonth;
			previousDay = previousMon->firstDay;
		}

		fprintf_s(stdout, "success");
		fclose(fp);
	}

	//グラフ描画等
	putNcurses();
	

    return 0;
}


	

	