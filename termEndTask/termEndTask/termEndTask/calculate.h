#pragma once
#include "structure.h" 

double aveDay(double, double);//���̕��ϋC��
double aveMonth(DAY *first);//���̕��ϋC��
double aveYear(MONTH *first);//�N�Ԃ̕��ϋC��

double differenceDay(double, double);//���̊��g��
double differenceMonth(DAY *first);//���̕��ϊ��g��
double differenceYear(MONTH *first);//�N�Ԃ̕��ϊ��g��

double computeDiscomfortIndex(double, double);

int roundUp(double);
int roundDown(double);
int roundOff(double);