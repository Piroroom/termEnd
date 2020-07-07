#pragma once
#include "structure.h" 

double aveDay(double, double);//���̕��ϋC��
double aveMonth(DAY *first);//���̕��ϋC��
double aveYear(MONTH *first);//�N�Ԃ̕��ϋC��

double differenceDay(double, double);//���̊��g��
double differenceMonth(DAY *first);//���̕��ϊ��g��
double differenceYear(MONTH *first);//�N�Ԃ̕��ϊ��g��

double computeDiscomfortIndex(double, double);
void computeALLData(YEAR *first);

double rainFallMonth(DAY *first);

int roundUp(double);
int roundDown(double);
int roundOff(double);

extern double allDataAveMon[2][12];//1�C��,2�~����