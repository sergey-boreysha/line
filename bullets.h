#pragma once

#include <windows.h>

class Bullet
{
public:

	int range = 20;

	Bullet(COORD coord, direct_t direction) : direction(LEFT), coord{ 0 }
	{
		this->coord = coord;
		this->direction = direction;

		this->coord.X++;

			SetConsoleCursorPosition(hd, this->coord);
			printf("-");
	};

	void step()
	{
			SetConsoleCursorPosition(hd, this->coord);
			printf(" ");

			this->coord.X++;

			if (map[coord.Y][coord.X] == 'B')
			{
				delete bot;
				bot = NULL;
			}

			if (map[coord.Y][coord.X] != ' ')
				map[coord.Y][coord.X] = ' ';

			SetConsoleCursorPosition(hd, this->coord);
			printf("-");
	}

	void lastClr()
	{
		SetConsoleCursorPosition(hd, this->coord);
		printf(" ");
	}

	direct_t getDirection()
	{
		return direction;
	}


private:
	COORD coord;
	direct_t direction;


};

Bullet* bullets[NUMBER_OF_SHOOTS];