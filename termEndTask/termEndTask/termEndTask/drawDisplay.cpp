#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include "drawDisplay.h"

int key=0 ;

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
			if (key	!= '1') {
				continue;
			}
			break;
		case '2':
			modeTwo();
			break;

		case '3':
			modeThree();
			if (key != '3') {
				continue;
			}
			break;
		default:
			mvprintw(11, 5, "'1'�Ŋ��g���O���t���[�h");
			mvprintw(12, 5, "'2'�ŕs���w���v�Z���[�h");
			mvprintw(13, 5, "'3'�ō~���ʂƕ��ϋC���O���t���[�h");
			break;
		}
		key = getch();
	}
	endwin();
}

void modeOne() {
	clear();
	int x, y, w, h;
	getmaxyx(stdscr, h, w);
	y = h / 4;
	x = w /14;
	h = 21;
	w = 40;

	int i = 1;
	int isEnd = 0;
	

	while (previousYear != NULL) {
		while (previousMon != NULL)
		{
			while (previousDay != NULL) {
			
				drawGraphOne(y, x, h, w);
				
				
				mvprintw(i, i, "%d�N:���ϋC��%lf��,���g�����ł��傫����%d��", previousYear->year, previousYear->yearAve, previousYear->maxDiffMonth->month);
				mvprintw(i + 2, i, "%d��:���ϋC��%lf�x,���ϊ��g��%lf�x,���ԍ~����%0.1f", previousMon->month, previousMon->monthAve, previousMon->monthDifference,previousMon->monthRainFall);
				mvprintw(i + 3, i, "%d��%d��:�ō��C��%0.1f�x,�Œ�C��%0.1f,���x%d%%,�~����%0.1f,���g��%0.1f�x,�s���w��%0.1f", previousMon->month, previousDay->day, previousDay->maxTemp, previousDay->minTemp, previousDay->humidity, previousDay->dayRainFall, previousDay->dayDifference, previousDay->discomfortIndex);
				refresh();

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

				case '3':
					previousDay = NULL;
					previousMon = NULL;
					previousYear = NULL;
					isEnd = 1;
					break;

				case KEY_DC:
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

	mvprintw(11, 5, "'1'�Ŋ��g���O���t���[�h");
	mvprintw(12, 5, "'2'�Ń��Z�b�g");
	mvprintw(13, 5, "'3'�ō~���ʂƕ��ϋC���O���t���[�h");
	refresh();
}

void modeThree() {
	clear();
	int x, y, w, h;
	getmaxyx(stdscr, h, w);
	y = h / 4;
	x = w / 14;
	h = 21;
	w = 50;

	int i = 1;
	int isEnd = 0;


	while (previousYear != NULL) {
		while (previousMon != NULL)
		{
			while (previousDay != NULL) {
				drawGraphTwo(y, x, h, w);
				drawGraphTwo1(y, 66, h, w);
			

				mvprintw(i, i, "�~���ʃO���t�̏�̔��������͂��̌��̕��ϋC����\��");
				mvprintw(i + 2, i, "%d�N%d��:���ϋC��%lf�x,���ϊ��g��%lf�x,���ԍ~����%0.1f",previousYear->year, previousMon->month, previousMon->monthAve, previousMon->monthDifference, previousMon->monthRainFall);
				refresh();

				key = getch();

				switch (key)
				{
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

				case '1':
					previousDay = NULL;
					previousMon = NULL;
					previousYear = NULL;
					isEnd = 1;

				case KEY_DC:
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
}


void drawGraphOne(int y, int x, int h, int w) {
	clear();
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
		for (int i = tempPos; i > tempPos - put; i--) {
			mvaddstr(i, j + 3, "��");
		}
		mvaddstr(tempPos - put, j + 3, "--");
		attroff(A_BOLD);
		previousMon = previousMon->nextMonth;
	}
	attrset(COLOR_PAIR(2));
	mvaddstr(tempPos + 1, x + w, "(��)");
	previousMon = preMon;

	refresh();
}

void drawGraphTwo(int y, int x, int h, int w) {
	clear();
	int tempPos;
	char str[BUFFLENGTH];
	int cnt = 0;
	int put = 0;

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

	attrset(COLOR_PAIR(3));
	attron(A_BOLD);
	sprintf_s(str, "�S�N�̕��ϋC���ƍ~����");
	mvaddstr(y - 1, x + (x / 2), str);
	attroff(A_BOLD);

	attrset(COLOR_PAIR(2));
	for (int j = y; j<(y + h); j++) {
		mvaddstr(j, x, "|");
		tempPos = j;
	}
	mvaddstr(y, x - 7, "(mm)");
	for (int j = x + 1; j <x + w; j++) {
		mvaddstr(tempPos, j, "_");
	}

	for (int j = y; cnt < 11; j += 2) {
		sprintf_s(str, "%d", 330 - cnt*30);
		mvaddstr(j, x - strlen(str), str);
		cnt++;
	}
	cnt = 0;
	for (int j = x; cnt<12; j += 4) {
		attrset(COLOR_PAIR(2));
		sprintf_s(str, "%d", cnt+1);
		mvaddstr(tempPos + 1, j + 4, str);

		attrset(COLOR_PAIR(1));
		attron(A_BOLD);
		put = roundOff((allDataAveMon[1][cnt] -30)/15);
		for (int i = tempPos; i > tempPos-put;i--) {
			mvaddstr(i, j + 4, "��");
		}
		sprintf_s(str, "%0.1f", allDataAveMon[0][cnt]);
		if (allDataAveMon[1][cnt] > 30) {
			mvaddstr(tempPos - put, j + 4, "--");
			attrset(COLOR_PAIR(2));
			mvaddstr(tempPos - put-1, j + 4, str);
		}
		else {
			attrset(COLOR_PAIR(2));
			mvaddstr(tempPos- 1, j + 3, str);
		}
		attroff(A_BOLD);
		cnt++;
	}

	attrset(COLOR_PAIR(2));
	mvaddstr(tempPos + 1, x + w, "(��)");

	refresh();
}

void drawGraphTwo1(int y, int x, int h, int w) {
	//clear();
	MONTH *preMon = NULL;
	preMon = previousMon;
	int tempPos;
	char str[BUFFLENGTH];
	int cnt = 0;
	int put = 0;

	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);

	attrset(COLOR_PAIR(3));
	attron(A_BOLD);
	sprintf_s(str, "%d�N�̕��ϋC���ƍ~����", previousYear->year);
	mvaddstr(y - 1, x + (x / 10), str);
	attroff(A_BOLD);

	attrset(COLOR_PAIR(2));
	for (int j = y; j<(y + h); j++) {
		mvaddstr(j, x, "|");
		tempPos = j;
	}
	mvaddstr(y, x - 7, "(mm)");
	for (int j = x + 1; j <x + w; j++) {
		mvaddstr(tempPos, j, "_");
	}

	for (int j = y; cnt < 11; j += 2) {
		sprintf_s(str, "%d", 330 - cnt * 30);
		mvaddstr(j, x - strlen(str), str);
		cnt++;
	}
	cnt = 0;
	previousMon = previousYear->firstMonth;
	for (int j = x; previousMon != NULL; j += 4) {
		attrset(COLOR_PAIR(2));
		sprintf_s(str, "%d", previousMon->month);
		mvaddstr(tempPos + 1, j + 4, str);

		attrset(COLOR_PAIR(1));
		attron(A_BOLD);
		put = roundOff((previousMon->monthRainFall - 30) / 15);
		for (int i = tempPos; i > tempPos - put; i--) {
			mvaddstr(i, j + 4, "��");
		}
		sprintf_s(str, "%0.1f", previousMon->monthAve);
		if (previousMon->monthRainFall > 30) {
			mvaddstr(tempPos - put, j + 4, "--");
			attrset(COLOR_PAIR(2));
			mvaddstr(tempPos - put - 1, j + 4, str);
		}
		else {
			attrset(COLOR_PAIR(2));
			mvaddstr(tempPos - 1, j + 3, str);
		}
		attroff(A_BOLD);
		previousMon = previousMon->nextMonth;
	}

	attrset(COLOR_PAIR(2));
	mvaddstr(tempPos + 1, x + w, "(��)");
	previousMon = preMon;

	refresh();
}




