#pragma once

struct DAY
{
	int day;
	double maxTemp;
	double minTemp;
	int humidity;
	
	double discomfortIndex;

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

extern YEAR *firstYear;


extern YEAR *previousYear;
extern MONTH *previousMon;
extern DAY *previousDay;



