#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "readFile.h"

YEAR *firstYear = NULL;

YEAR *previousYear = NULL;
MONTH *previousMon = NULL;
DAY *previousDay = NULL;

YEAR tempYear;
MONTH tempMon;
DAY	tempDay;

void readFileName(char temp[BUFFLENGTH]) {

	char currentDirectory[BUFFLENGTH];
	getCurrentDirectory(currentDirectory);

	char section[BUFFLENGTH];
	sprintf_s(section, "section1");

	char keyWord[BUFFLENGTH];
	sprintf_s(keyWord, temp);

	char settingFile[BUFFLENGTH];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);

	if (readChar(section, keyWord, 0, temp, settingFile) == false) {
		fprintf_s(stdout, "�t�@�C�������擾�ł��܂���ł���\n");
	}
}


void CSV2Array(const char *fileName) {
	char s[BUFFSIZE];
	FILE *fp;
	errno_t error;
	error = fopen_s(&fp, fileName, "r");

	if (error != 0) {
		fprintf_s(stderr, "failed toopen");
	}
	else {
		int cnt = 0;
		int beforeMon = 0;
		int beforeYear = 0;

		while (fgets(s, sizeof(s), fp) != 0) {

			int status = sscanf_s(s, "%d/%d/%d,%lf,%lf,%d", &tempYear.year, &tempMon.month, &tempDay.day, &tempDay.maxTemp, &tempDay.minTemp,&tempDay.humidity);
			if (status != 6)continue;


			DAY *tmpD = new DAY();
			tmpD->day = tempDay.day;
			tmpD->maxTemp = tempDay.maxTemp;
			tmpD->minTemp = tempDay.minTemp;
			tmpD->humidity = tempDay.humidity;
			tmpD->dayAve = aveDay(tmpD->maxTemp, tmpD->minTemp);//���̕��ϋC��
			tmpD->dayDifference = differenceDay(tmpD->maxTemp, tmpD->minTemp);//���g��
			tmpD->discomfortIndex = computeDiscomfortIndex(tmpD->dayAve, tmpD->humidity);//�s���w��
			tmpD->nextDay = NULL;


			if (tempMon.month != beforeMon) {
				if (previousMon != NULL) {
					previousMon->monthAve = aveMonth(previousMon->firstDay);//���̕���
					previousMon->monthDifference = differenceMonth(previousMon->firstDay);//�����g���̕���
				}

				MONTH *tmpM = new MONTH();
				tmpM->month = tempMon.month;
				tmpM->firstDay = tmpD;
				tmpM->nextMonth = NULL;


				if (tempYear.year != beforeYear) {
					if (previousYear != NULL) {
						previousYear->yearAve = aveYear(previousYear->firstMonth);//�N����
						previousYear->yearDifference = differenceYear(previousYear->firstMonth);//�N���g������
					}
					YEAR *tmpY = new YEAR();
					tmpY->year = tempYear.year;
					tmpY->firstMonth = tmpM;
					tmpY->nextYear = NULL;

					if (cnt == 0) {
						firstYear = tmpY;
						firstYear->isEnd = 0;
						firstYear->firstMonth = tmpM;
						cnt++;
					}
					else {
						previousYear->isEnd = 0;
						previousYear->nextYear = tmpY;
					}
					previousYear = tmpY;
					beforeYear = tempYear.year;

				}
				else {
					previousMon->monthAve = aveMonth(previousMon->firstDay);//���̕���
					previousMon->monthDifference = differenceMonth(previousMon->firstDay);//���̊��g������
					previousMon->nextMonth = tmpM;
				}
				beforeYear = tempYear.year;
				beforeMon = tempMon.month;
				previousMon = tmpM;
			}
			else {
				previousDay->nextDay = tmpD;
			}
			previousDay = tmpD;
			beforeMon = tempMon.month;
		}
		previousMon->monthAve = aveMonth(previousMon->firstDay);//�Ō�̌�����
		previousMon->monthDifference = differenceMonth(previousMon->firstDay);//�Ō�̌����g������

		previousYear->yearAve = aveYear(previousYear->firstMonth);//�Ō�̔N����
		previousYear->yearDifference = differenceYear(previousYear->firstMonth);//�Ō�̔N���g������

		previousYear->isEnd = 1;
		previousYear->nextYear = firstYear;//���X�g�����

		//�|�C���^���ŏ��̃f�[�^�ɃZ�b�g
		previousYear = firstYear;
		previousMon = previousYear->firstMonth;
		previousDay = previousMon->firstDay;
		fclose(fp);
	}
}