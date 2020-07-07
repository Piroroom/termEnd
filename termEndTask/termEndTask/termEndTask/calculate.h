#pragma once
#include "structure.h" 

double aveDay(double, double);//日の平均気温
double aveMonth(DAY *first);//月の平均気温
double aveYear(MONTH *first);//年間の平均気温

double differenceDay(double, double);//日の寒暖差
double differenceMonth(DAY *first);//月の平均寒暖差
double differenceYear(MONTH *first);//年間の平均寒暖差

double computeDiscomfortIndex(double, double);

int roundUp(double);
int roundDown(double);
int roundOff(double);