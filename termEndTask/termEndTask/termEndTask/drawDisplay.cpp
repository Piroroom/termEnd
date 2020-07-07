#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "drawDisplay.h"

int key ='2';

int putNcurses() {
	char str[BUFFLENGTH];
	// ������
	if (initscr() == NULL) {
		return 1;
	}
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	erase();
	
	
	while (key!=KEY_DC)
	{
		
		switch (key)
		{
		case '1':
			modeOne();
			if (key == '2') {
				continue;
			}
			break;
		case '2':
			modeTwo();
			break;
		default:
			//key = getch();
			break;
		}
		key = getch();
	}
	//endwin();
}

void modeOne() {
	clear();
	int x, y, w, h;
	getmaxyx(stdscr, h, w);
	y = h / 4;
	x = w / 6;
	h = 21;
	w = 40;




	int i = 1;
	int isEnd = 0;
	

	while (previousYear != NULL) {
		while (previousMon != NULL)
		{
			while (previousDay != NULL) {
				erase();

				mvprintw(i, i, "%d�N:���ϋC��%lf��,���g�����ł��傫����%d��", previousYear->year, previousYear->yearAve, previousYear->maxDiffMonth->month);
				mvprintw(i + 2, i, "%d��:���ϋC��%lf�x,���ϊ��g��%lf�x", previousMon->month, previousMon->monthAve, previousMon->monthDifference, previousYear->maxDiffMonth->month);
				mvprintw(i + 3, i, "%d��%d��:�ō��C��%0.1f�x,�Œ�C��%0.1f,���x%d%%,���g��%0.1f�x,�s���w��%0.1f", previousMon->month, previousDay->day, previousDay->maxTemp, previousDay->minTemp, previousDay->humidity, previousDay->dayDifference, previousDay->discomfortIndex);
				drawGraph(y, x, h, w);



				key = getch();

				switch (key)
				{
				case KEY_DOWN:
					previousDay = previousDay->nextDay;
					refresh();
					break;

				case KEY_RIGHT:
					previousMon = previousMon->nextMonth;
					if (previousMon != NULL) {
						previousDay = previousMon->firstDay;
					}
					else {
						previousDay = NULL;
					}
					refresh();
					break;

				case KEY_UP:
					previousYear = previousYear->nextYear;
					if (previousYear != NULL) {
						previousMon = previousYear->firstMonth;
						previousDay = previousMon->firstDay;
					}
					else {
						previousDay = NULL;
						previousMon = NULL;
					}
					refresh();
					break;

				case '2':
					previousDay = NULL;
					previousMon = NULL;
					previousYear = NULL;
					isEnd = 1;
					break;

				
				default:
					break;
				}
			}
			if (previousMon != NULL) {
				previousMon = previousMon->nextMonth;
				previousDay = previousMon->firstDay;
			}
		}
		if (isEnd != 1) {
			previousYear = previousYear->nextYear;
		}
		if (previousYear != NULL) {
			previousMon = previousYear->firstMonth;
			previousDay = previousMon->firstDay;
		}
	}
	//�|�C���^���ŏ��̃f�[�^�ɃZ�b�g
	previousYear = firstYear;
	previousMon = previousYear->firstMonth;
	previousDay = previousMon->firstDay;
	
	//endwin();
}

void modeTwo() {
	char str[BUFFLENGTH];
	double n;
	int k;
	int y, x;
	
	clear();
	mvprintw(5, 5, "�s���w���v�Z���[�h");
	mvprintw(7, 5, "�C���������œ���(50���܂�):");
	refresh();
	getyx(curscr, y, x);

	while (1) {
		if (scanw("%lf", &n) != 1) {
			continue;
		}
		if (n > 50) {
			move(y, x);
			beep();
			printw("�l���傫�����܂�");
		}
		else {
			erase();
			move(y, x);
			mvprintw(5, 5, "�s���w���v�Z���[�h");
			mvprintw(7, 5, "�C���������œ���:");
			printw("�C��%0.1f�x", n);
			refresh();
			getyx(curscr, y, x);
			break;
		}
	}

	mvprintw(8, 5, "���x�𐮐��œ���:");
	getyx(curscr, y, x);

	while (1) {
		if (scanw("%d", &k) != 1) {
			continue;
		}
		if (k >100) {
			move(y, x);
			beep();
			printw("�l���傫�����܂�");
		}
		else {
			erase();
			mvprintw(5, 5, "�s���w���v�Z���[�h");
			mvprintw(7, 5, "�C���������œ���:");
			printw("�C��%0.1f�x", n);
			mvprintw(8, 5, "���x�𐮐��œ���:");
			getyx(curscr, y, x);
			move(y, x);
			printw("���x%d%%", k);
			refresh();
			getyx(curscr, y, x);
			break;
		}
	}


	sprintf_s(str, "�s���w��%0.1f", computeDiscomfortIndex(n, k));
	mvprintw(9, 5,str);

	mvprintw(11, 5, "'1'�ŃO���t���[�h");
	mvprintw(12, 5, "'2'�Ń��Z�b�g");
	refresh();
}

void drawGraph(int y, int x, int h, int w) {
	MONTH *preMon = NULL;
	preMon = previousMon;
	int tempPos;
	char str[BUFFLENGTH];
	int cnt = 0;
	int put = 0;

	start_color();
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

	attrset(COLOR_PAIR(3));
	attron(A_BOLD);
	sprintf_s(str, "%d�N���g���O���t", previousYear->year);
	mvaddstr(y - 1, x + (x / 2), str);
	attroff(A_BOLD);

	attrset(COLOR_PAIR(2));
	for (int j = y; j<(y + h); j++) {
		mvaddstr(j, x, "|");
		tempPos = j;
	}
	mvaddstr(y, x - 6, "(��)");
	for (int j = x + 1; j <x + w; j++) {
		mvaddstr(tempPos, j, "_");
	}

	for (int j = y; cnt < 11; j += 2) {
		sprintf_s(str, "%d", 15 - cnt);
		mvaddstr(j, x - strlen(str), str);
		cnt++;
	}

	previousMon = previousYear->firstMonth;
	for (int j = x; previousMon != NULL; j += 3) {
		attrset(COLOR_PAIR(2));
		sprintf_s(str, "%d", previousMon->month);
		mvaddstr(tempPos + 1, j + 3, str);

		attrset(COLOR_PAIR(1));
		attron(A_BOLD);
		put = roundOff((previousMon->monthDifference - 5) * 2);
		mvaddstr(tempPos - put, j + 3, "--");
		attroff(A_BOLD);
		previousMon = previousMon->nextMonth;
	}
	attrset(COLOR_PAIR(2));
	mvaddstr(tempPos + 1, x + w, "(��)");
	previousMon = preMon;

	refresh();
}

