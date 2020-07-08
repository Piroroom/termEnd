#pragma once

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "outPut.h"

void outPutFile() {
	char outPut[BUFFLENGTH] = "outputFileName";
	readFileName(outPut);//�o�̓t�@�C�����ǂݍ���
	errno_t error;
	FILE *fp;

	error = fopen_s(&fp, outPut, "w");

	if (error != 0) {
		fprintf_s(stderr, "failed toopen");
	}
	else {
		while (previousYear != NULL) {
			sprintf_s(outPut, "%d,%d��\n", previousYear->year, previousYear->maxDiffMonth->month);
			fputs(outPut, fp);
			if (previousYear->isEnd == 1) {
				break;
			}
			previousYear = previousYear->nextYear;
		}
		//�|�C���^���ŏ��̃f�[�^�ɃZ�b�g
		if (firstYear != NULL) {
			previousYear = firstYear;
			previousMon = previousYear->firstMonth;
			previousDay = previousMon->firstDay;
		}

		fprintf_s(stdout, "success");
		fclose(fp);
	}
}