#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "calculate.h"



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