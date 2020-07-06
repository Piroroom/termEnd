#pragma once

struct DAY
{
	int day;
	double maxTemp;
	double minTemp;

	double dayAve;
	double dayDifference;

	DAY *nextDay;
};

struct MONTH
{
	int month;

	double monthAve;
	double monthDifference;

	DAY *firstDay;
	MONTH *nextMonth;
};

struct YEAR
{
	int year;
	int isEnd;

	double yearAve;
	double yearDifference;

	MONTH *firstMonth;
	MONTH *maxDiffMonth;
	YEAR *nextYear;


};

YEAR *firstYear = NULL;


YEAR *previousYear = NULL;
MONTH *previousMon = NULL;
DAY *previousDay = NULL;

//ˆêŽž•ÛŠÇ—p
YEAR tempYear;
MONTH tempMon;
DAY	tempDay;