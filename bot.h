#pragma once

#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>

class Bot
{
public:
	Bot(COORD coord) : direction(UP), coord{ 0 }
	{
		this->coord.X = coord.X;
		this->coord.Y = coord.Y;

		map[coord.Y][coord.X] = 'B';

		SetConsoleCursorPosition(hd, coord);
		printf("B");
	};

	void step() 
	{
		if (speed_step++ > 3)
		{

			COORD coord = this->coord;

			if (direction == UP)
				coord.Y--;
			else
				coord.Y++;

			if (map[coord.Y][coord.X] != ' ')
			{
				if (direction == UP)
				{
					direction = DOWN;
					coord.Y += 2;
				}
				else
				{
					direction = UP;
					coord.Y -= 2;
				}
			}

			map[this->coord.Y][this->coord.X] = ' ';
			SetConsoleCursorPosition(hd, this->coord);
			printf(" ");

			this->coord.X = coord.X;
			this->coord.Y = coord.Y;

			map[this->coord.Y][this->coord.X] = 'B';

			SetConsoleCursorPosition(hd, this->coord);
			printf("B");

			speed_step = 0;

		}
	};

private:
	COORD coord;
	direct_t direction;

	int speed_step = 0;
};