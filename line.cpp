// line.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#define NUMBER_OF_SHOOTS 10
#define NUMBER_OF_BOT 3

HANDLE hd = GetStdHandle(STD_OUTPUT_HANDLE);
typedef enum { LEFT,RIGHT,UP,DOWN } direct_t;
char map[25][85];

#include "bot.h"

Bot* bot;

#include "bullets.h"
#include "gamer.h"

void conveyorBullets()
{
	for (int index = 0; index < NUMBER_OF_SHOOTS; index++)
	{
		if (bullets[index])
		{
			if (bullets[index]->range > 1)
			{
				bullets[index]->step();
				bullets[index]->range--;
			}

			if (bullets[index] && bullets[index]->range == 1)
			{
				bullets[index]->lastClr();
				delete bullets[index];
				bullets[index] = NULL;
			}
		}
	}
}

void botServer()
{

}

void debugPrint(Gamer alex)
{
	COORD coord = {5,25};
	SetConsoleCursorPosition(hd, coord);

	coord = alex.getCoord();
	printf("X: %d Y: %d\r", coord.X, coord.Y);
}

int main()
{
	//загрузка карты
	int line = 0;
	FILE* map_df = fopen("001.map", "r");
	while (!feof(map_df))
		fgets(map[line++], 83, map_df);
	//вывод карты
	for(int i=0;i<line;i++)
		printf("%s", map[i]);

	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hd, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hd, &structCursorInfo);

	COORD coord;
	coord.X = 5;
	coord.Y = 5;

	Gamer alex(coord);

	coord.X = 30;
	coord.Y = 10;

	bot = new Bot(coord);


	do
	{
		/*coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(hd, coord);
		for (int i = 0; i < line; i++)
			printf("%s", map[i]);*/


		//игрок
		alex.action();

		//конвеер bullet
		conveyorBullets();
		
		//сервер ботов
		if(bot)
			bot->step();

		debugPrint(alex);
		Sleep(100);

	} while (GetKeyState(VK_ESCAPE) >= 0);

	exit(0);
}
