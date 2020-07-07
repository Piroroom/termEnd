#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "calculate.h"

double allDataAveMon[2][12];

double aveDay(double max, double min) {
	return (max + min) / 2;
}

double aveMonth(DAY *first) {
	DAY *preDay = NULL;//アドレス記憶用
	preDay = first;
	double temp = 0;
	int cnt = 0;
	while (first != NULL) {
		cnt++;
		temp += first->dayAve;
		first = first->nextDay;
	}
	first = preDay;
	return temp / cnt;
}


double aveYear(MONTH *first) {
	MONTH *preMon = NULL;//アドレス記憶用
	preMon = first;
	double temp = 0;
	int cnt = 0;

	while (first != NULL) {
		cnt++;
		temp += first->monthAve;
		first = first->nextMonth;
	}
	first = preMon;
	return temp / cnt;

}

double computeDiscomfortIndex(double temp, double humidity) {
	double discomfortIndex;
	discomfortIndex = 0.81*temp + 0.01*humidity*(0.99*temp - 14.3) + 46.3;
	return discomfortIndex;
}

double differenceDay(double max, double min) {
	return (max - min);
}

double differenceMonth(DAY *first) {
	DAY *preDay = NULL;//アドレス記憶用
	preDay = first;
	double temp = 0;
	int cnt = 0;
	while (first != NULL) {
		cnt++;
		temp += first->dayDifference;
		first = first->nextDay;
	}
	first = preDay;
	return temp / cnt;
}

double differenceYear(MONTH *first) {
	MONTH *preMon = NULL;//アドレス記憶用
	preMon = first;
	double temp = 0;
	double temp2 = 0;
	int cnt = 0;

	while (first != NULL) {
		cnt++;
		if (first->monthDifference > temp2) {
			temp2 = first->monthDifference;
			previousYear->maxDiffMonth = first;
		}
		temp += first->monthDifference;
		first = first->nextMonth;
	}
	first = preMon;
	return temp / cnt;
}


double rainFallMonth(DAY *first) {
	DAY *preDay = NULL;//アドレス記憶用
	preDay = first;
	double temp = 0;

	while (first != NULL) {
		temp += first->dayRainFall;
		first = first->nextDay;

	}
	first = preDay;
	return temp;
}



void computeALLData(YEAR *first) {
	YEAR *preYear = NULL;//アドレス記憶用
	preYear = first;

	int cnt = 0;
	int yearCnt = 0;
	MONTH *preMon = preYear->firstMonth;

	while (first!=NULL)
	{
		yearCnt++;
		while (preMon!=NULL)
		{
			allDataAveMon[0][cnt] += preMon->monthAve;
			allDataAveMon[1][cnt] += preMon->monthRainFall;
			preMon = preMon->nextMonth;
			cnt++;
		}
		first = first->nextYear;
		if (first != NULL) {
			preMon = first->firstMonth;
		}
		cnt = 0;
	}
	first = preYear;
	fprintf_s(stdout, "%d年分\n", yearCnt);
	for (int i = 0; i < 12; i++) {
		allDataAveMon[0][i] /= yearCnt;
		allDataAveMon[1][i] /= yearCnt;
		fprintf_s(stdout, "%d月:気温%0.1f,降水量%0.1f\n", i+1, allDataAveMon[0][i], allDataAveMon[1][i]);
	}
}




int roundOff(double n) {
	double decimal = 0;

	decimal = n - (int)n;

	if (decimal >= 0.5 || decimal <= -0.5) {
		return roundUp(n);
	}
	else {
		return roundDown(n);
	}
}

//切り上げ
int roundUp(double n) {
	if (n >= 0) {
		return (int)n + 1;
	}
	else {
		return (int)n - 1;
	}
}

//切り捨て
int roundDown(double n) {
	return (int)n;
}